#ifndef NIRYOCONTROLLER_H
#define NIRYOCONTROLLER_H

#include "Niryo_global.h"
#include <QModbusDataUnit>
#include "niryoqmodbusbase.h"
#include "poseniryo.h"
#include "trajectoirniryo.h"

enum resultatDerniereCmd
{
    nonRecuperer = -1,
    pasEncoreDeReslutat = 0,
    succes = 1,
    cmdRejeter = 2,
    cmdAbandonner = 3,
    cmdAnnuler = 4,
    errInattendu = 5,
    delaiDepasser = 6,
    errInterne = 7,
    cmdDejaEnCour = 8,
    colision = 9,
};

class NIRYO_EXPORT NiryoController
{
public:
    NiryoController();
    ~NiryoController();
    bool connecterRobot(const QString& IP1,quint16 port1,const QString &IP2 , quint16 port2);
    bool connecterRobot(QString _IPetPort1,QString _IPetPort2);
    void deconnecterRobot();
    int temperatureRaspBerry();// fonction de test va etre supprimer

    //recuperation d'informations (pour NiryoInfo)
    QList<float> recupererAxes(bool &ok);
    QList<int> recupererPosition(bool &ok);
    QList<float> recupererOrientation(bool &ok);
    int recupererOutil(bool &ok);
    QList<bool> recupererAprentissage(bool &ok);// mode appretissage du robot de base
    QList<quint16> recupererInfoDiverse(bool &ok);//pas terminer



    //mouvements
    bool lancerMovement(QList<float> _axes, bool _estEnDegree);
    bool lancerMovement(PoseNiryo pose);
    bool lancerCalibration();
    bool detectionOutil();
    bool verifierEtatDuRobot();
    bool verifierConnection();
    bool stopperRobot();

    QString resultatDerniereCmdEnQStr();

    //trajectoirs
    bool recupererTrajectoirEnCour(bool &ok);
    int recupererNbTrajectoire(bool &ok);
    bool recupererMApprentissageDeTrajectoir(bool &ok);// mode apprentissage ajouter au robot
    QList<TrajectoirNiryo> indexerLesTrajecoirs(bool &ok);

    //
    bool lancerTrajectoir(TrajectoirNiryo _trajecoir);

    //accesseurs

    QString getLastError();


    //debug
    void debugDump();
    void trajectoirDebugDump(QList<TrajectoirNiryo> list);


private:
    //selectionde dtrajectoire(interne)
    bool selectionnerTrajectoire(int _index);
    bool deselectionnerTrajectoire();
    //conversions(interne)
    float convertirAxesEnRadiant(quint16 _axerobot);
    quint16 convertirRadiantEnAxe(float _val);

    NiryoQModBusBase *niryobase;

    bool colision;                      // address 301 fnct 4

    bool serverConnected[2] = {false};
    bool cmdEnCourRobot;                // address 150 fnct 3
    int resultatDerniereCmd;            // address 151 fnct 3
    int resultatDerniereCmdData;            // address 152 fnct 3
    QString lastError;
    int nbDeTrajectoires;
    bool apprentisageDeTrajectoire;
    bool trajectoirEnCour;
};

#endif // NIRYOCONTROLLER_H
