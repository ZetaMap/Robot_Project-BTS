#ifndef CONVOYEUR_H
#define CONVOYEUR_H

#include "Convoyeur_global.h"

#include <modbusutil.h>
#include <QTimer>


// adresses à utiliser
#define CMmarche  0x00
#define CMarriere 0x01
#define CMavant   0x02
#define Cpt1      0x10
#define Cpt2      0x11
#define Vvert     0xc
#define Vrouge    0xd

#define NbCapteurs 0x11
#define CONVOYEUR_LOOP_DELAY  100 //ms
#define CONVOYEUR_PULSE_DELAY 200 //ms


class CONVOYEUR_EXPORT Convoyeur : public QObject
{
    Q_OBJECT

private:
    QTimer *timerProduction = NULL, *timerCapteurs = NULL;

    bool _capteurEntree = false, _capteurSortie = false, _statutProduction = true,
        _erreurProduction = false, _erreurLecture = false;

protected:
    // fonctions d'envoie de requêtes
    bool envoieRequeteEcriture(uint adresse, int valeur);
    bool envoiePulse(uint adresse);

public:
    // public car utilisé pour connecter un event à l'IHM
    ModbusUtil *modbusClient = NULL;

    Convoyeur() { modbusClient = new ModbusUtil(); }
    ~Convoyeur() {
        stopperBoucleAuto();
        stopperBoucleCapteurs();
        deconnexion();
        delete modbusClient;
        delete timerProduction;
        delete timerCapteurs;
    }

    // fonctions de connexion
    bool connexion(QString ip, int port);
    void deconnexion();
    bool estConnecte();

    // fonctions pour les mouvements du convoyeur
    bool marcheAvant();
    bool marcheArriere();
    bool marche();
    bool arret();

    // fonctions pour les voyans
    bool eteindreVoyants();
    bool voyantV();
    bool voyantR();

    // fonctions pour le mode automatique
    void programmeAutoMode();
    void lireCapteurs();
    void retirerErreurs();

    void lancerBoucleCapteurs();
    void stopperBoucleCapteurs();
    void lancerBoucleAuto();
    void stopperBoucleAuto();

    bool attendreProductionFini(long timeout=10000); //ms

    // fonctions d'accesseurs
    bool capteurEntree() { return _capteurEntree; }
    bool capteurSortie() { return _capteurSortie; }
    bool statutProduction() { return _statutProduction; }
    bool erreurProduction() { return _erreurProduction; }
    bool erreurLecture() { return _erreurLecture; }
    bool boucleCapteursLancee() { return timerCapteurs != NULL && timerCapteurs->isActive(); }
    bool boucleAutoLancee() { return timerProduction != NULL && timerProduction->isActive(); }

signals:
    // Signaux, utilisable avec connect() pour être notifié d'évènements
    void capteursLus();
    void boucleAutoLoop();
    void boucleCapteursStatus();
    void boucleAutoStatut();
};

#endif // CONVOYEUR_H
