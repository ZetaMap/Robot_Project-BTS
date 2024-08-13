#ifndef CONVOYEUR_H
#define CONVOYEUR_H

#include <QModbusTcpClient>
#include <QModbusDataUnit>
#include <QModbusTcpServer>
#include <QModbusReply>
#include <QTimer>


class Convoyeur : public QObject
{
private:
    QModbusTcpClient modbusClient;

public:
    Convoyeur(QObject *parent = nullptr) : QObject(parent) {}
    ~Convoyeur();

    //addr (Marche/AV/AR)
    const int CMavant = 0x02;
    const int CMarrière = 0x01;
    const int CMmarche = 0x00;

    //addr voyant
    const int Vvert = 0xc;
    const int Vrouge = 0xd;
    //addr capteur
    const int Cpt1 = 0x0010;
    const int Cpt2 = 0x0011;

    //function(button)
    bool marche();
    bool voyantV();
    bool voyantR();
    int lireCapteurs();
    bool connexion(QString ip, int port);
    void deconnexion();
    bool marcheAvant();
    bool marcheArrière();
    bool arret();
    void autoMode();
    void boucleAuto();
    bool estConnecte();

    //fonction capteurs
    bool capteur1_etat ;
    bool capteur2_etat ;
    void boucleCapteurs();


    bool marcheAvantExecute = false;
    bool arretExecute = false;
    bool voyantVertExecute = false;
    bool voyantRougeExecute = false;
    bool productionTermine = true;

    bool RequestLireCapteurs();



};

#endif // CONVOYEUR_H
