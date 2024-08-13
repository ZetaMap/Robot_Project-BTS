#include "convoyeur.h"
#include "modbusutil.h"


Convoyeur::~Convoyeur()
{
    deconnexion();
}

bool Convoyeur::connexion(QString ip, int port)
{

    // Configure les paramètres de connexion Modbus
    modbusClient.setConnectionParameter(QModbusDevice::NetworkPortParameter, port);
    modbusClient.setConnectionParameter(QModbusDevice::NetworkAddressParameter, ip);

    modbusClient.setTimeout(1000);
    modbusClient.setNumberOfRetries(3);

    return modbusClient.connectDevice();
}
void Convoyeur::deconnexion()
{
    modbusClient.disconnectDevice();
}

bool Convoyeur::marcheAvant()
{

    QModbusDataUnit writeUnit = ModbusUtil::writeRequest();

    writeUnit.setValue(CMmarche, 1);
    writeUnit.setValue(CMavant, 1);
    QModbusReply *reply = ModbusUtil::sendWriteRequest(modbusClient, writeUnit);
    bool ok = reply != 0;

    if (!ok) return false;

    QThread::sleep(1);

    writeUnit.setValue(CMavant, 0);
    reply = ModbusUtil::sendWriteRequest(modbusClient, writeUnit);
    ok = reply != 0;

    delete reply;
    return ok;
}


bool Convoyeur::marcheArrière(){

    QModbusDataUnit writeUnit = ModbusUtil::writeRequest();

    writeUnit.setValue(CMmarche, 1);
    writeUnit.setValue(CMarrière, 1);
    QModbusReply *reply = ModbusUtil::sendWriteRequest(modbusClient, writeUnit);
    bool ok = reply != 0;

    if (!ok) return false;

    QThread::sleep(1);

    writeUnit.setValue(CMarrière, 0);
    reply = ModbusUtil::sendWriteRequest(modbusClient, writeUnit);
    ok = reply != 0;

    delete reply;
    return ok;
}
bool Convoyeur::voyantV(){
    QModbusDataUnit writeUnit = ModbusUtil::writeRequest();

    writeUnit.setValue(Vvert, 1);
    QModbusReply *reply = ModbusUtil::sendWriteRequest(modbusClient, writeUnit);
    bool ok = reply != 0;

    if (!ok) return false;
    delete reply;
    return ok;
}
bool Convoyeur::voyantR(){
    QModbusDataUnit writeUnit = ModbusUtil::writeRequest();

    writeUnit.setValue(Vrouge, 1);
    QModbusReply *reply = ModbusUtil::sendWriteRequest(modbusClient, writeUnit);
    bool ok = reply != 0;

    if (!ok) return false;
    delete reply;
    return ok;
}

bool Convoyeur::marche(){
    QModbusDataUnit writeUnit = ModbusUtil::writeRequest();

    writeUnit.setValue(CMmarche, 1);
    QModbusReply *reply = ModbusUtil::sendWriteRequest(modbusClient, writeUnit);
    bool ok = reply != 0;

    delete reply;
    return ok;
}

bool Convoyeur::arret(){
    QModbusDataUnit writeUnit = ModbusUtil::writeRequest();

    writeUnit.setValue(CMmarche, 0);
    QModbusReply *reply = ModbusUtil::sendWriteRequest(modbusClient, writeUnit);
    bool ok = reply != 0;

    delete reply;
    return ok;
}
void Convoyeur::boucleCapteurs() {

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Convoyeur::lireCapteurs);
    timer->start(50);
}

void Convoyeur::boucleAuto() {

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Convoyeur::lireCapteurs);
    connect(timer, &QTimer::timeout, this, &Convoyeur::autoMode);
    timer->start(100);
}



bool Convoyeur::estConnecte()
{
    return modbusClient.state() == QModbusDevice::ConnectedState;
}


int Convoyeur::lireCapteurs(){
    QModbusDataUnit ReadUnit = ModbusUtil::readRequest();
    QModbusReply *reply = ModbusUtil::sendReadRequest(modbusClient, ReadUnit);

    if (!reply) return -1;
    int capteurs = ((reply->result().value(Cpt1) == 0)<<1)|((reply->result().value(Cpt2) == 0)<<0);
    delete reply;

    return capteurs;
}

bool Convoyeur::RequestLireCapteurs(){
    int capteurs = lireCapteurs();

    if (capteurs == -1) {
        return false;
    }


    capteur1_etat = !((capteurs >> 1) & 1);
    capteur2_etat = !((capteurs >> 0) & 1);

    return true;
}

void Convoyeur::autoMode() {
    if (capteur1_etat && !capteur2_etat) {
        marcheAvant();
        productionTermine = false;
    } else if (!productionTermine && !capteur1_etat && capteur2_etat) {
        arret();
        voyantV();
        productionTermine = true;
    } else if (!productionTermine && capteur1_etat && capteur2_etat) {
        arret();
        voyantR();
        productionTermine = true;
    }


}






