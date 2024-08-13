#include "convoyeur.h"


bool Convoyeur::connexion(QString ip, int port) {
    return modbusClient->connectDevice(ip, port);
}

void Convoyeur::deconnexion() {
    modbusClient->disconnectDevice();
}

bool Convoyeur::estConnecte() {
    return modbusClient->isConnected();
}


bool Convoyeur::envoieRequeteEcriture(uint adresse, int valeur) {
    // Ignore if not connected
    if (!estConnecte()) return false;

    QModbusDataUnit writeUnit = modbusClient->coilsRequest(adresse);
    writeUnit.setValue(0, valeur);
    QModbusReply *reply = modbusClient->sendWriteRequest(writeUnit);

    bool ok = reply != NULL;
    if (!ok) return false;
    reply->deleteLater();
    return ok;
}

bool Convoyeur::envoiePulse(uint adresse){
    if (!envoieRequeteEcriture(adresse, 1)) return false;
    QThread::msleep(CONVOYEUR_PULSE_DELAY);
    return envoieRequeteEcriture(adresse, 0);
}


bool Convoyeur::marcheAvant(){
    if (!marche()) return false;
    return envoiePulse(CMavant);
}

bool Convoyeur::marcheArriere(){
    if (!marche()) return false;
    return envoiePulse(CMarriere);
}

bool Convoyeur::marche(){
    return envoieRequeteEcriture(CMmarche, 1);
}

bool Convoyeur::arret(){
    return envoieRequeteEcriture(CMmarche, 0);
}

bool Convoyeur::eteindreVoyants() {
    if (!envoieRequeteEcriture(Vvert, 0)) return false;
    return envoieRequeteEcriture(Vrouge, 0);
}

bool Convoyeur::voyantV(){
    return envoieRequeteEcriture(Vvert, 1);
}

bool Convoyeur::voyantR(){
    return envoieRequeteEcriture(Vrouge, 1);
}


void Convoyeur::lireCapteurs(){
    QModbusDataUnit unit = modbusClient->discreteInputsRequest(0, NbCapteurs);
    QModbusReply *reply = modbusClient->sendReadRequest(unit);

    _erreurLecture = reply == NULL;
    if (_erreurLecture) return;

    unit = reply->result();
    _capteurEntree = unit.value(Cpt1) != 0;
    _capteurSortie = unit.value(Cpt2) != 0;

    reply->deleteLater();

    emit capteursLus(); // run callback
}

void Convoyeur::retirerErreurs() {
    _erreurLecture = false;
    _erreurProduction = false;
}

void Convoyeur::lancerBoucleCapteurs() {
    // Check if connected, first
    if (!estConnecte()) return;
    // Avoid to run another time
    if (boucleCapteursLancee()) return;

    if (timerCapteurs == NULL) {
        timerCapteurs = new QTimer();
        connect(timerCapteurs, &QTimer::timeout, this, &Convoyeur::lireCapteurs);
    }

    timerCapteurs->start(CONVOYEUR_LOOP_DELAY);
    lireCapteurs(); // fait une première lecture
    emit boucleCapteursStatus();
}

void Convoyeur::stopperBoucleCapteurs() {
    if (!boucleCapteursLancee()) return;

    // Stop the timer
    timerCapteurs->stop();
    // Wait a little if still active
    if (timerCapteurs->isActive()) QThread::msleep(100);

    emit boucleCapteursStatus();
}

void Convoyeur::lancerBoucleAuto() {
    // Check if connected, first
    if (!estConnecte()) return;
    // Avoid to run another time the auto mode
    if (boucleAutoLancee()) return;

    // Start the sensor loop before
    lancerBoucleCapteurs();

    if (timerProduction == NULL) {
        timerProduction = new QTimer();
        connect(timerProduction, &QTimer::timeout, this, &Convoyeur::programmeAutoMode);
    }

    timerProduction->start(CONVOYEUR_LOOP_DELAY);
    programmeAutoMode();
    emit boucleAutoStatut();
}

void Convoyeur::stopperBoucleAuto() {
    if (!boucleAutoLancee()) return;

    // Stop the timer
    timerProduction->stop();
    // Wait a little if still active
    if (timerProduction->isActive()) QThread::msleep(100);

    emit boucleAutoStatut();
}

bool Convoyeur::attendreProductionFini(long timeout) {
    QEventLoop *loop = new QEventLoop();
    QTimer *timer = new QTimer();

    connect(timer, &QTimer::timeout, [&timeout, loop]() {
        timeout = -1;
        loop->quit();
    });
    connect(this, &Convoyeur::boucleAutoLoop, [this, loop, timer]() {
        if (statutProduction()) {
            timer->stop();
            loop->quit();
        }
    });

    timer->setSingleShot(true);
    timer->start(timeout);
    loop->exec();

    return timeout != -1;
}

void Convoyeur::programmeAutoMode() {
    // Erreur de lecture ou production, on ignore
    if (erreurLecture() || erreurProduction()) return;
    // Boucle capteurs non lancé, on stoppe le mode auto
    if (!boucleCapteursLancee()) {
        stopperBoucleAuto();
        return;
    }

    if (statutProduction() && capteurEntree() && !capteurSortie()) {
        marcheAvant();
        eteindreVoyants();
        _statutProduction = false;
        _erreurProduction = false;

    } else if (!statutProduction() && !capteurEntree() && capteurSortie()) {
        arret();
        eteindreVoyants();
        voyantV();
        _statutProduction = true;
        _erreurProduction = false;

    } else if (!statutProduction() && capteurEntree() && capteurSortie()) {
        arret();
        eteindreVoyants();
        voyantR();
        _statutProduction = true;
        _erreurProduction = true;
    }

    emit boucleAutoLoop(); // run callback
}
