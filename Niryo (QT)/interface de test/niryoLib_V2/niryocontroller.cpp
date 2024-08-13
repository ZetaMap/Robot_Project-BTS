#include "niryocontroller.h"

NiryoController::NiryoController() {

    niryobase = new NiryoQModBusBase();

    this->lastError = "";
    this->colision = false;
    for (int i = 0; i < 2; ++i) {
        this->serverConnected[i] = false;
    }
    this->cmdEnCourRobot = false;
    this->resultatDerniereCmd = resultatDerniereCmd::nonRecuperer;
    this->resultatDerniereCmdData = 0;
    this->nbDeTrajectoires = 0;
    this->apprentisageDeTrajectoire = false;
    this->trajectoireEnCour = false;
}

NiryoController::~NiryoController()
{
    delete niryobase;
}

bool NiryoController::connecterRobot(const QString &IP1,quint16 port1,const QString &IP2 , quint16 port2)
{
    return niryobase->connecterNiryo(IP1,port1,IP2,port2);
}

bool NiryoController::connecterRobot(QString _IPetPort1, QString _IPetPort2)
{
    QString _IP1,_IP2;
    quint16 port1,port2;
    QList<QString> liste1;
    QList<QString> liste2;
    bool ok = false;
    liste1 = _IPetPort1.split(u':',Qt::SkipEmptyParts);

    if(liste1.length() != 2){
        this->lastError = "erreur conversion des adress/port";
        return false;
    }

    _IP1 = liste1.value(0);
    port1 = liste1.value(1).toInt(&ok,10);
    if(!ok){
        this->lastError = "erreur conversion des adress/port";
        return false;
    }

    liste2 = _IPetPort2.split(u':',Qt::SkipEmptyParts);

    if(liste1.length() != 2){
        this->lastError = "erreur conversion des adress/port";
        return false;
    }

    _IP2 = liste2.value(0);
    port2 = liste2.value(1).toInt(&ok,10);

    if(!ok){
        this->lastError = "erreur conversion des adress/port";
        return false;
    }

    return connecterRobot(_IP1,port1,_IP2,port2);
}

void NiryoController::deconnecterRobot()
{
    niryobase->deconnecterNiryo();
}

int NiryoController::temperatureRaspBerry()
{
    bool ok = false;
    QList<quint16> resultat;
    QModbusDataUnit readcmd(QModbusDataUnit::RegisterType::InputRegisters,403,(quint16)1);
    resultat = niryobase->communication(serverID::ServerNormal,TypeDeCommunication::Read,readcmd,&ok);
    return resultat.value(0);
}

bool NiryoController::quint16ToBool(quint16 q)
{
    if(q == 0){
        return false;
    } else {
        return true;
    }
}


QList<float> NiryoController::recupererAxes(bool &ok)
{
    ok = false;
    QList<quint16> reponse;
    QList<float> resultat;

    QModbusDataUnit readcmd(QModbusDataUnit::RegisterType::InputRegisters,0,6);

    reponse = niryobase->communication(serverID::ServerNormal,TypeDeCommunication::Read,readcmd,&ok);// axes

    if(ok){
        for(int i = 0; i < 6 ; i++){
            resultat.append(convertirAxesEnRadiant(reponse.value(i)));
        }
    } else {
        this->lastError = "erreur de demande axes";
        return QList<float>();
    }

    return resultat;
}

QList<int> NiryoController::recupererPosition(bool &ok)
{
    ok = false;
    QList<quint16> reponse;
    QList<int> resultat;

    QModbusDataUnit readcmd(QModbusDataUnit::RegisterType::InputRegisters,10,3);

    reponse = niryobase->communication(serverID::ServerNormal,TypeDeCommunication::Read,readcmd,&ok);// pos

    if(ok){
        for(int i = 0; i < 3 ; i++){
            resultat.append(reponse.value(i));
        }
    } else {
        this->lastError = "erreur de demande position";
        return QList<int>();
    }

    return resultat;
}

QList<float> NiryoController::recupererOrientation(bool &ok)
{
    ok = false;
    QList<quint16> reponse;
    QList<float> resultat;

    QModbusDataUnit readcmd(QModbusDataUnit::RegisterType::InputRegisters,13,3);

    reponse = niryobase->communication(serverID::ServerNormal,TypeDeCommunication::Read,readcmd,&ok);// orientation
    if(ok){
        for(int i = 0; i < 3 ; i++){
            resultat.append(convertirAxesEnRadiant(reponse.value(i)));
        }
    } else {
        this->lastError = "erreur de demande orientation";
        return QList<float>();
    }
    return resultat;
}

int NiryoController::recupererOutil(bool &ok)
{
    ok = false;
    QList<quint16> reponse;
    float resultat;

    QModbusDataUnit readcmd(QModbusDataUnit::RegisterType::InputRegisters,200,1);

    reponse = niryobase->communication(serverID::ServerNormal,TypeDeCommunication::Read,readcmd,&ok);// id outil

    if(!ok){
        this->lastError = "erreur de demande outil";
        return -1;
    }
    resultat = reponse.value(0);

    return resultat;
}

QList<bool> NiryoController::recupererAprentissage(bool &ok)
{
    ok = false;
    QList<quint16> reponse;
    QList<bool> resultat;

    QModbusDataUnit readcmd(QModbusDataUnit::RegisterType::InputRegisters,300,2);

    reponse = niryobase->communication(serverID::ServerNormal,TypeDeCommunication::Read,readcmd,&ok);// mode apprentissage + colision
    if(!ok){
        return QList<bool>();
    }
    resultat.append(quint16ToBool(reponse.value(0)));// learning mode
    apprentissageNormal = quint16ToBool(reponse.value(0));
    resultat.append(quint16ToBool(reponse.value(1)));// colision
    return resultat;
}

QList<quint16> NiryoController::recupererInfoDiverse(bool &ok)
{
    QList<quint16> reponse;
    QModbusDataUnit readcmd5(QModbusDataUnit::RegisterType::InputRegisters,400,10);
    ok = true;

    reponse = niryobase->communication(serverID::ServerNormal,TypeDeCommunication::Read,readcmd5,&ok);
    if(!ok){
        return QList<quint16>();
    } else {
        return reponse;
    }
}

bool NiryoController::lancerMovement(QList<float> _axes, bool _estEnDegree)
{
    PoseNiryo _pose;
    if(!_pose.setPose(_axes,_estEnDegree)){
        return false;
    }
    return lancerMovement(_pose);
}

bool NiryoController::lancerMovement(PoseNiryo pose)
{
    QList<quint16> axes;

    pose.appliquerLimites();//verification des limites

    axes = pose.getAxesQuint16(); // recuperation des axes

    if(!verifierEtatDuRobot(true)){
        return false;
    }


    QModbusDataUnit writecmd[6]; //tableau des demandes d'écriture

    QList<quint16> listDeDonne ;// varial de cache

    bool ok[6] = {false};// recuperation d'erreur
    if(!niryobase->isConnected(serverID::ServerNormal)){
        this->lastError = "Robot non connecter";
        return false;
    }

    for (int i = 0; i < 6; ++i) {// creation des requetes
        writecmd[i].setRegisterType(QModbusDataUnit::RegisterType::HoldingRegisters);
        writecmd[i].setStartAddress(i);
        listDeDonne.append(axes.value(i));
        writecmd[i].setValues(listDeDonne);
        listDeDonne.clear();

        niryobase->communication(serverID::ServerNormal,TypeDeCommunication::Write,writecmd[i],&ok[i]);
    }
    if(!ok[0]&&!ok[1]&&!ok[2]&&!ok[3]&&!ok[4]&&!ok[5]){
        this->lastError = " erreur lors de l'envoie des axes";// 2 write  0  6 axes related
        return false;
    }

    if(!recupererDerniereCmd()){
        return false;
    }

    if(!cmdEnCourRobot){
        QList<quint16> signal;
        signal.append(0xffff);
        bool ok2 = false;
        QModbusDataUnit writeCmd100(QModbusDataUnit::RegisterType::HoldingRegisters,100,signal);
        niryobase->communication(serverID::ServerNormal,TypeDeCommunication::Write,writeCmd100,&ok2);
        if(!ok2){return false;}
    }
    return true;
}

bool NiryoController::actionnerOutil(bool _attraperLacher)
{
    QList<quint16> signal;
    signal.append(0xffff);
    bool ok;
    int outil;

    if(!verifierEtatDuRobot(true)){
        return false;
    }

    outil = recupererOutil(ok);
    if(!ok){
        return false;
    }


    if(apprentisageDeTrajectoire){
        if(!actionnerPourTrajecoire(_attraperLacher)){
            this->lastError = "echec de la demande actionner outil normal";
            return false;
        }
    } else {
        if(!actionnerViaServN(outil,_attraperLacher)){
            this->lastError = "echec de la demande actionner outil pour trajecoire";
            return false;
        }
    }

    return true;

}

bool NiryoController::lancerCalibration()
{
    bool ok = false;
    bool ok2 = false;
    QList<quint16> signal;
    signal.append(0xffff);

    QModbusDataUnit writeCmdCalibReq(QModbusDataUnit::RegisterType::HoldingRegisters,310,signal);
    QModbusDataUnit writeCmdCalibLancer(QModbusDataUnit::RegisterType::HoldingRegisters,311,signal);

    if(!verifierEtatDuRobot(false)){
        return false;
    }

    niryobase->communication(serverID::ServerNormal,TypeDeCommunication::Write,writeCmdCalibReq,&ok);
    niryobase->communication(serverID::ServerNormal,TypeDeCommunication::Write,writeCmdCalibLancer,&ok2);

    if(!ok || !ok2){
        return false;
    }

    return true;
}

bool NiryoController::detectionOutil()
{
    bool ok = false;
    QList<quint16> signal;
    signal.append(0xffff);

    QModbusDataUnit writeDetectTool(QModbusDataUnit::RegisterType::HoldingRegisters,500,signal);

    if(!verifierEtatDuRobot(false)){
        return false;
    }

    niryobase->communication(serverID::ServerNormal,TypeDeCommunication::Write,writeDetectTool,&ok);

    if(!ok){
        return false;
    }
    return true;
}

bool NiryoController::recupererDerniereCmd()
{
    bool ok = false;
    QModbusDataUnit readcmd150(QModbusDataUnit::RegisterType::HoldingRegisters,150,3);
    QList<quint16> reponse;
    reponse = niryobase->communication(serverID::ServerNormal,TypeDeCommunication::Read,readcmd150,&ok);
    if(!ok){
        this->lastError = "erreur lors de la demande pour cmd en cours";
    } else {
        this->cmdEnCourRobot = quint16ToBool(reponse.value(0));
        qDebug() << cmdEnCourRobot;
        this->resultatDerniereCmd = reponse.value(1);
        this->resultatDerniereCmdData = reponse.value(2);
    }
    return ok;
}

bool NiryoController::recupererCalibrationEnCour()
{
    bool ok;
    QList<quint16> reponse;
    QModbusDataUnit readCalibrationEnCour(QModbusDataUnit::RegisterType::InputRegisters,402,1);

    reponse = niryobase->communication(serverID::ServerCustom,TypeDeCommunication::Read,readCalibrationEnCour,&ok);
    if(!ok){
        this->lastError = "echec de recuperation trajectoireEnCour";
        return false;
    }

    this->calibrationEnCour = quint16ToBool(reponse.value(0));

    return ok;
}

bool NiryoController::verifierEtatDuRobot(bool fnctApprentissageTrj)
{
    if(!verifierConnection()){
        this->lastError = "Robot non connecter";
        return false;
    }

    bool ok[5] = {false};

    ok[0] = recupererDerniereCmd();//cmd en cour
    recuperertrajectoireEnCour(ok[1]);//trajecoire en cour
    recupererMApprentissageDeTrajectoir(ok[2]);//apprentissage serv custom
    recupererAprentissage(ok[3]);//colision
    ok[4] = recupererCalibrationEnCour();//calibration


    for (int i = 0; i < 5; ++i) {
        if(!ok[i]){
            this->lastError = "Erreur de demande d'information";
            return false;
        }
    }

    if(colision){
        this->lastError = "Colision détecter";
        return false;
    }

    if(cmdEnCourRobot){
        this->lastError = "commande en cour";
        return false;
    }

    if(calibrationEnCour){
        this->lastError = "calibration en cour";
        return false;
    }

    if(apprentisageDeTrajectoire && !fnctApprentissageTrj){
        this->lastError = "apprentissage de trajectoire en cour";
       return false;
    }

    if(apprentissageNormal){
        this->lastError = "apprentisaage interne en cour";
        return false;
    }

    qDebug() << calibrationEnCour << cmdEnCourRobot << colision;
    return true;
}

bool NiryoController::verifierConnection()
{
    this->serverConnected[0] = niryobase->isConnected(serverID::ServerNormal);
    this->serverConnected[1] = niryobase->isConnected(serverID::ServerCustom);

    if(!niryobase->isConnected(serverID::ServerNormal) && !niryobase->isConnected(serverID::ServerCustom)){
        return false;
    } else {
        return true;
    }
}

bool NiryoController::stopperRobot()
{
    QList<quint16> signal;
    signal.append(0xffff);
    QList<quint16> reponse;
    bool ok = false;
    bool ok2 = false;
    bool ok3 = false;
    bool bypass = false;
    QModbusDataUnit writeStopMvmt(QModbusDataUnit::RegisterType::HoldingRegisters,110,signal);
    QModbusDataUnit writeStopTrajectoire(QModbusDataUnit::RegisterType::HoldingRegisters,43,signal);
    QModbusDataUnit readStopMvmt(QModbusDataUnit::RegisterType::HoldingRegisters,110,1);
    QModbusDataUnit readStopTrajectoire(QModbusDataUnit::RegisterType::HoldingRegisters,43,1);

    recuperertrajectoireEnCour(ok3);
    if(!ok3){
        bypass = true;
        this->lastError = "arret ecrit mais echec de la recuperation trajectoireEnCour";
    }


    if(niryobase->isConnected(serverID::ServerNormal)){
        niryobase->communication(serverID::ServerNormal,TypeDeCommunication::Write,writeStopMvmt,&ok);
    }

    if(ok){
        reponse = niryobase->communication(serverID::ServerNormal,TypeDeCommunication::Read,readStopMvmt,&ok);
        if(reponse.value(0) !=0){
            ok = true;
        } else {
            ok = false;
            this->lastError = "arret ecrit mais lecture incorrect 1";
        }
    }

    if(trajectoireEnCour || bypass){
        if(niryobase->isConnected(serverID::ServerCustom)){
            niryobase->communication(serverID::ServerCustom,TypeDeCommunication::Write,writeStopTrajectoire,&ok2);
        }

        if(ok2){
            reponse = niryobase->communication(serverID::ServerCustom,TypeDeCommunication::Read,readStopTrajectoire,&ok2);
            if(reponse.value(0) !=0){
                ok2 = true;
            } else {
                ok2 = false;
                this->lastError = "arret ecrit mais lecture incorrect 2";
            }
        }
    }



    bool resultat = false;
    if(ok && ok2 && ok3){
        resultat = true;
    }

    return resultat;
}

bool NiryoController::recuperertrajectoireEnCour(bool &ok)
{
    bool resultat;
    QList<quint16> reponse;
    QModbusDataUnit readTrjEnCour(QModbusDataUnit::RegisterType::HoldingRegisters,42,1);

    reponse = niryobase->communication(serverID::ServerCustom,TypeDeCommunication::Read,readTrjEnCour,&ok);
    if(!ok){
        this->lastError = "echec de recuperation trajectoireEnCour";
        return false;
    }

    this->trajectoireEnCour = quint16ToBool(reponse.value(0));
    resultat = quint16ToBool(reponse.value(0));

    return resultat;
}

int NiryoController::recupererNbTrajectoire(bool &ok)
{
    QList<quint16> reponse;
    int resultat = 0;

    QModbusDataUnit readNbTrajectoire(QModbusDataUnit::RegisterType::HoldingRegisters,50,1);//lecture nb trajectoire

    reponse = niryobase->communication(serverID::ServerCustom,TypeDeCommunication::Read,readNbTrajectoire,&ok);
    if(!ok){
        this->lastError = "echec de la demande du nb de trajectoires ";
        ok = false;
        return -1;
    }
    resultat = reponse.value(0);
    this->nbDeTrajectoires = resultat;
    return resultat;
}

bool NiryoController::recupererMApprentissageDeTrajectoir(bool &ok)
{
    bool resultat;
    QList<quint16> reponse;

    QModbusDataUnit readApprentissage(QModbusDataUnit::RegisterType::HoldingRegisters,0,1);//lecture si apprentissage


    reponse = niryobase->communication(serverID::ServerCustom,TypeDeCommunication::Read,readApprentissage,&ok);
    if(!ok){
        this->lastError = "echec de verification de l'apprentissage";
        return false;
    }

    this->apprentisageDeTrajectoire = quint16ToBool(reponse.value(0));
    resultat = quint16ToBool(reponse.value(0));

    return resultat;
}

QList<TrajectoireNiryo> NiryoController::indexerLesTrajecoirs(bool &ok)
{
    ok =true;
    bool ok2 = false;

    QList<quint16> reponse;
    QList<TrajectoireNiryo> resultat;

    QModbusDataUnit readInfoTrjSlct(QModbusDataUnit::RegisterType::HoldingRegisters,10,22);//recuperation des infos de la trajectoir

    recupererNbTrajectoire(ok2);
    if(!ok2){
        ok = false;
        return QList<TrajectoireNiryo>();
    }

    recupererMApprentissageDeTrajectoir(ok2);
    if(!ok2){
        ok = false;
        return QList<TrajectoireNiryo>();
    }

    if(apprentisageDeTrajectoire){
        this->lastError = "apprentissage en cour";
        ok = false;
        return QList<TrajectoireNiryo>();
    }

    if(nbDeTrajectoires > 1000 || nbDeTrajectoires < 0){
        this->lastError = "nombre de trajecoir trop haut ou bas";
        ok = false;
        return QList<TrajectoireNiryo>();
    }

    qDebug() << nbDeTrajectoires;

    bool oklist[nbDeTrajectoires];
    bool oklist2[nbDeTrajectoires];
    for (int i = 0; i < nbDeTrajectoires; ++i) {//boucle d'indexation

        oklist[i] = selectionnerTrajectoire(i);// selection de la trajectoire sur le server cutom

        reponse = niryobase->communication(serverID::ServerCustom,TypeDeCommunication::Read,readInfoTrjSlct,&oklist2[i]);

        QList<quint16> nomtemp;
        for (int j = 0; j < 20; ++j) {// mise des valeurs correspondant au nom (0 a 19) dans une nouvelle liste
            nomtemp.append(reponse.value(j));
        }

        TrajectoireNiryo trj(reponse.value(21),nomtemp,i);//reponse 21 = ID, nomtemp = nom, i = index
        resultat.append(trj);// ajout de la trajectoire dans resultat
    }

    for (int i = 0; i < nbDeTrajectoires; i++) {// verification des erreurs
        if(!oklist[i] || !oklist2[i]){
            this->lastError = "echec lors de la boucle a i = " + QString::number(i);
            ok = false;
            return QList<TrajectoireNiryo>();
        }
    }

    if(!deselectionnerTrajectoire()){
        ok = false;
        this->lastError = "echec lors de la deselection";
    }

    this->listeDeTrj = resultat;

    return resultat;
}

bool NiryoController::recupererErreurTrajecoire(bool &ok)
{
    bool resultat = false;
    QList<quint16> reponse;

    QModbusDataUnit readErrorTrj(QModbusDataUnit::RegisterType::HoldingRegisters,100,1);

    reponse = niryobase->communication(serverID::ServerCustom,TypeDeCommunication::Read,readErrorTrj,&ok);

    if(!ok){
        this->lastError = "echec de la recuperation des erreurs trajectoires";
        return false;
    }
    resultat = quint16ToBool(reponse.value(0));
    return resultat;
}

bool NiryoController::lancerTrajectoir(TrajectoireNiryo _trajecoir)
{
    bool ok = false;
    QList<quint16> signal;
    signal.append(0x1);

    if(!verifierEtatDuRobot(false)){
        return false;
    }

    if(!_trajecoir.getExist()){
        return false;
    }

    if(!selectionnerTrajectoire(_trajecoir.getIndex())){
        return false;
    }

    QModbusDataUnit writeLancerTrj(QModbusDataUnit::RegisterType::HoldingRegisters,42,signal);
    niryobase->communication(serverID::ServerCustom,TypeDeCommunication::Write,writeLancerTrj,&ok);

    return ok;
}

TrajectoireNiryo NiryoController::choisirTrajectoireParID(int _ID,bool &ok)
{
    if(listeDeTrj.length()<1){
        ok = false;
        return TrajectoireNiryo();
    }
    int index = -1;
    for (int i = 0; i < listeDeTrj.length(); ++i) {
        if(listeDeTrj.value(i).getID() == _ID){
            index = i;
        }
    }
    if(index == -1){
        ok = false;
        return TrajectoireNiryo();
    }
    ok = true;
    return listeDeTrj.value(index);
}

bool NiryoController::lancerApprentissage()
{
    bool ok = false;
    QList<quint16> signal;
    signal.append(0x1);

    QModbusDataUnit writeLancerApprentissage(QModbusDataUnit::RegisterType::HoldingRegisters,0,signal);

    if(!verifierEtatDuRobot(true)){
        return false;
    }

    deselectionnerTrajectoire();

    if(apprentisageDeTrajectoire){
        return true;
    }

    niryobase->communication(serverID::ServerCustom,TypeDeCommunication::Write,writeLancerApprentissage,&ok);
    if(!ok){
        this->lastError = "echec demande d'activation du mode apprentissage";
        return false;
    }


    return true;
}

bool NiryoController::lancerDrapeau()
{
    bool ok = false;
    QList<quint16> signal;
    signal.append(0x1);

    QModbusDataUnit writeLancerDrapeau(QModbusDataUnit::RegisterType::HoldingRegisters,1,signal);

    if(!verifierEtatDuRobot(true)){
        return false;
    }


    niryobase->communication(serverID::ServerCustom,TypeDeCommunication::Write,writeLancerDrapeau,&ok);
    if(!ok){
        this->lastError = "echec demande de marquage de drapeau";
        return false;
    }
    return true;
}

bool NiryoController::enregistrerAprentissage(PoseNiryo _pose)
{
    bool ok = false;
    QList<quint16> signal;
    signal.append(0x0000);

    QModbusDataUnit writeFinApprentissage(QModbusDataUnit::RegisterType::HoldingRegisters,0,signal);
    signal[0]= 0x0001;
    QModbusDataUnit writeFinRien(QModbusDataUnit::RegisterType::HoldingRegisters,40,signal);

    if(!verifierEtatDuRobot(true)){
        return false;
    }
    niryobase->communication(serverID::ServerCustom,TypeDeCommunication::Write,writeFinApprentissage,&ok);
    if(!ok){
        this->lastError = "echec demande de fin d'apprentissage";
        return false;
    }

}

bool NiryoController::annulerAprentissage()
{
    bool ok = false;
    QList<quint16> signal;
    signal.append(0x0000);

    QModbusDataUnit writeFinApprentissage(QModbusDataUnit::RegisterType::HoldingRegisters,0,signal);
    QModbusDataUnit writeFinRien(QModbusDataUnit::RegisterType::HoldingRegisters,40,signal);

    if(!verifierEtatDuRobot(true)){
        return false;
    }

    niryobase->communication(serverID::ServerCustom,TypeDeCommunication::Write,writeFinApprentissage,&ok);
    if(!ok){
        this->lastError = "echec demande de fin d'apprentissage";
        return false;
    }
    qDebug() << "flag4";
    niryobase->communication(serverID::ServerCustom,TypeDeCommunication::Write,writeFinRien,&ok);
    if(!ok){
        this->lastError = "echec demande de fin d'apprentissage avec option 0 rien";
        return false;
    }
    return true;
}

bool NiryoController::terminerApprentissage(TrajectoireNiryo _trajectoire, int choix)
{
    bool ok = false;
    QList<quint16> signal;
    signal.append(0x0000);

    QModbusDataUnit writeFinApprentissage(QModbusDataUnit::RegisterType::HoldingRegisters,0,signal);
    signal[0] = choix;
    QModbusDataUnit writeFinChoix(QModbusDataUnit::RegisterType::HoldingRegisters,40,signal);

    if(!verifierEtatDuRobot(true)){
        return false;
    }

    QList<quint16> nom = _trajectoire.getNomQuint16();

    if(!ecrireNomTrj(nom)){
        return false;
    }

    niryobase->communication(serverID::ServerCustom,TypeDeCommunication::Write,writeFinApprentissage,&ok);
    if(!ok){
        this->lastError = "echec demande de fin d'apprentissage";
        return false;
    }

    niryobase->communication(serverID::ServerCustom,TypeDeCommunication::Write,writeFinChoix,&ok);
    if(!ok){
        this->lastError = "echec demande de fin d'apprentissage avec option "+ QString::number(choix) +" ";
        return false;
    }
    return true;
}

int NiryoController::getResultatDerniereCmd()
{
    return resultatDerniereCmd;
}

QString NiryoController::getResultatDerniereCmdEnQStr()
{
    switch (resultatDerniereCmd) {
    case resultatDerniereCmd::nonRecuperer:
        return "valeur non recupérer";
        break;
    case resultatDerniereCmd::succes:
        return "succes";
        break;
    case resultatDerniereCmd::pasEncoreDeReslutat:
        return "pas encore de resultat";
        break;
    case resultatDerniereCmd::cmdRejeter:
        return "commande rejeter";
        break;
    case resultatDerniereCmd::cmdAbandonner:
        return "commande abandonner";
        break;
    case resultatDerniereCmd::cmdAnnuler:
        return "commande annuler";
        break;
    case resultatDerniereCmd::errInattendu:
        return "erreur inattendu";
        break;
    case resultatDerniereCmd::delaiDepasser:
        return "delai dépasser";
        break;
    case resultatDerniereCmd::errInterne:
        return "erreur interne";
        break;
    case resultatDerniereCmd::cmdDejaEnCour:
        return "commande deja en cour d'exécution";
        break;
    case resultatDerniereCmd::colision:
        return "colision détecter";
        break;
    default:
        return "valeur inconnue";
        break;
    }
}

QString NiryoController::getLastError()
{
    QString error = lastError;
    lastError = "";
    return error;
}

void NiryoController::debugDump()
{
    qDebug() << "colision: " << colision ;
    for (int i = 0; i < 2; ++i) {
        qDebug() << "sever conneced[" << i << "]: " << serverConnected[i];
    }
    qDebug() << "cmdEnCourRobot: " << cmdEnCourRobot << "\nresultat derniere cmd: " << resultatDerniereCmd << getResultatDerniereCmdEnQStr();
    qDebug() << "resultat cmd data: " << resultatDerniereCmdData << "\nlast error: " << lastError << "\nnb de trajectoires: " << nbDeTrajectoires;
    qDebug() << "apprentissage de trajectoire: " << apprentisageDeTrajectoire << "\ntrajectoir en cour: " << trajectoireEnCour << "\ncalibration: " << calibrationEnCour << "\napprentissage interne: " << apprentissageNormal;
}

void NiryoController::trajectoirDebugDump(QList<TrajectoireNiryo> list)
{
    qDebug() << list.length();
    for (int i = 0; i < list.length(); ++i) {
        qDebug() << "exist : " << list.value(i).getExist() << " ID : " << list.value(i).getID() << " nom : " << list.value(i).getNom() << " index : " << list.value(i).getIndex();
    }
}

bool NiryoController::selectionnerTrajectoire(int _index)
{
    QList<quint16> index;
    index.append(_index);
    QList<quint16> reponse;

    bool ok = false;

    QModbusDataUnit writeSlct(QModbusDataUnit::RegisterType::HoldingRegisters,41,index);

    QModbusDataUnit readTrjSlct(QModbusDataUnit::RegisterType::HoldingRegisters,51,1);// verification de selection

    if(!niryobase->isConnected(serverID::ServerCustom)){
        return false;
    }

    niryobase->communication(serverID::ServerCustom,TypeDeCommunication::Write,writeSlct,&ok);
    if(!ok){
        this->lastError = "echec de selection";
        return false;
    }
    int loopcount = 0;
    do{
        bool okloop = false;
        reponse = niryobase->communication(serverID::ServerCustom,TypeDeCommunication::Read,readTrjSlct,&okloop);
        if(!okloop){
            this->lastError = "echec de la verif de selection!";
            return false;
        }
        loopcount++;
    } while (reponse.value(0)==0 && loopcount < 5 );

    if(loopcount > 5){
        this->lastError = "trop de demande de verif de selection";
        return false;
    }
    return true;
}

bool NiryoController::deselectionnerTrajectoire()
{
    QList<quint16> signal;
    signal.append(0x0000);
    bool ok = false;

    QModbusDataUnit writeTrjSlct(QModbusDataUnit::RegisterType::HoldingRegisters,51,signal);// verification de selection

    if(!niryobase->isConnected(serverID::ServerCustom)){
        return false;
    }

    niryobase->communication(serverID::ServerCustom,TypeDeCommunication::Write,writeTrjSlct,&ok);

    return ok;
}

float NiryoController::convertirAxesEnRadiant(quint16 _axerobot)
{
    float resulta = -1;
    if ((_axerobot >> 15) == 1){
        resulta = 0-(float)(_axerobot & 0x7fff);
    } else {
        resulta = (float)(_axerobot & 0x7fff);
    }
    resulta = resulta / 1000;
    return resulta;
}

quint16 NiryoController::convertirRadiantEnAxe(float _val)
{
    quint16 resultat = 0;
    _val = _val*1000;
    if(_val < 0){
        resultat = (1 << 15) + (((quint16)-_val) & 0x7fff);
    } else {
        resultat = (((quint16)_val) & 0x7fff);
    }
    return resultat;
}

bool NiryoController::actionnerViaServN(int _outil,bool _attraperLacher)
{
    QList<quint16> signal;
    signal.append(0xffff);
    bool ok = false;

    QModbusDataUnit writeActionnerOutil(QModbusDataUnit::RegisterType::HoldingRegisters,512,signal);
    int offset = 0;
    if(!_attraperLacher){
        offset =1;
    }

    if(_outil == 31){
        writeActionnerOutil.setStartAddress(512+offset);
        niryobase->communication(serverID::ServerNormal,TypeDeCommunication::Write,writeActionnerOutil,&ok);
    } else if(_outil == 11 || _outil == 12 || _outil == 13){
        writeActionnerOutil.setStartAddress(511-offset);
        niryobase->communication(serverID::ServerNormal,TypeDeCommunication::Write,writeActionnerOutil,&ok);
    } else {
        return false;
    }
    return ok;
}

bool NiryoController::actionnerPourTrajecoire(bool _attraperLacher)
{
    QList<quint16> signal;
    if(_attraperLacher){
        signal.append(0xffff);
    } else {
        signal.append(0x0000);
    }

    bool ok = false;

    QModbusDataUnit writeActionnerOutil(QModbusDataUnit::RegisterType::HoldingRegisters,2,signal);

    niryobase->communication(serverID::ServerCustom,TypeDeCommunication::Write,writeActionnerOutil,&ok);


    return false;
}

bool NiryoController::ecrireNomTrj(QList<quint16> _nom)
{
    bool ok[20] = {false};
    QList<quint16> character;
    QModbusDataUnit writeNom(QModbusDataUnit::RegisterType::HoldingRegisters,10,character);
    while (_nom.length() < 20) {
        _nom.append(0x0000);
    }
    if(_nom.length() != 20){
        return false;
    }

    for (int i = 0; i < 20; ++i) {
        character[0] = _nom.value(i);
        writeNom.setValues(character);
        niryobase->communication(serverID::ServerCustom,TypeDeCommunication::Write,writeNom,&ok[i]);
    }
    for (int i = 0; i < 20; ++i) {
        if(!ok[i]){
            return false;
        }
    }
    return true;

}


