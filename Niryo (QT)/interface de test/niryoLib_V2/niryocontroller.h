#ifndef NIRYOCONTROLLER_H
#define NIRYOCONTROLLER_H

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

class NiryoController : public QObject
{
/*
    Q_OBJECT
signals:
    void tseste();

    emit tseste();
*/
public:
    NiryoController();
    ~NiryoController();
    bool connecterRobot(const QString& IP1,quint16 port1,const QString &IP2 , quint16 port2);
    bool connecterRobot(QString _IPetPort1,QString _IPetPort2);
    void deconnecterRobot();
    int temperatureRaspBerry();// fonction de test va etre supprimer
    static bool quint16ToBool(quint16 q);

    //recuperation d'informations (pour NiryoInfo)
    QList<float> recupererAxes(bool &ok);
    QList<int> recupererPosition(bool &ok);
    QList<float> recupererOrientation(bool &ok);
    int recupererOutil(bool &ok);
    QList<bool> recupererAprentissage(bool &ok);// mode appretissage du robot de base
    QList<quint16> recupererInfoDiverse(bool &ok);



    //mouvements
    bool lancerMovement(QList<float> _axes, bool _estEnDegree);
    bool lancerMovement(PoseNiryo pose);
    bool actionnerOutil(bool _attraperLacher); // true = ouvert false = fermer
    bool lancerCalibration();
    bool detectionOutil();// a faire
    bool recupererDerniereCmd();
    bool recupererCalibrationEnCour();

    //verification avant de demander au robot
    bool verifierEtatDuRobot(bool fnctApprentissageTrj);//a continuer
    bool verifierConnection();

    //fonction d'arrret d'urgence
    bool stopperRobot();



    //trajectoirs

    bool recuperertrajectoireEnCour(bool &ok);
    int recupererNbTrajectoire(bool &ok);
    bool recupererMApprentissageDeTrajectoir(bool &ok);// mode apprentissage ajouter au robot
    QList<TrajectoireNiryo> indexerLesTrajecoirs(bool &ok);
    bool recupererErreurTrajecoire(bool &ok);

    //actions sur les tajectoires
    bool lancerTrajectoir(TrajectoireNiryo _trajecoir);
    TrajectoireNiryo choisirTrajectoireParID(int _ID, bool &ok);

    //mode apprentissage
    bool lancerApprentissage();
    bool lancerDrapeau();
    bool enregistrerAprentissage(PoseNiryo _pose);
    bool annulerAprentissage();
    bool terminerApprentissage(TrajectoireNiryo _trajectoire,int choix);
    //bool supprimerTrajectoire(TrajectoirNiryo _trajectoire);

    //accesseurs
    int getResultatDerniereCmd();
    QString getResultatDerniereCmdEnQStr();
    QString getLastError();


    //debug
    void debugDump();
    void trajectoirDebugDump(QList<TrajectoireNiryo> list);


private:
    //selectionde dtrajectoire(interne)
    bool selectionnerTrajectoire(int _index);
    bool deselectionnerTrajectoire();
    //conversions(interne)
    float convertirAxesEnRadiant(quint16 _axerobot);
    quint16 convertirRadiantEnAxe(float _val);
    //actionner outils(interne)
    bool actionnerViaServN(int _outil,bool _attraperLacher);
    bool actionnerPourTrajecoire(bool _attraperLacher);
    //ecriture du nom dans la trajectoire
    bool ecrireNomTrj(QList<quint16> _nom);

    NiryoQModBusBase *niryobase;

    bool colision;                      // address 301 fnct 4
    bool serverConnected[2] = {false};  //etat des connections
    bool cmdEnCourRobot;                // address 150 fnct 3
    int resultatDerniereCmd;            // address 151 fnct 3
    int resultatDerniereCmdData;        // address 152 fnct 3
    QString lastError;                  //contient le dernier message d'erreur
    int nbDeTrajectoires;               // address 50 fnct 4 srv custom
    bool apprentisageDeTrajectoire;     // address 0 fnct 4 srv custom
    bool trajectoireEnCour;              // address 42 fnct 4 srv custom
    bool calibrationEnCour;             // address 402 fnct 4
    bool apprentissageNormal;
    QList<TrajectoireNiryo> listeDeTrj;

};

#endif // NIRYOCONTROLLER_H
