#include "testinterface2.h"
#include "ui_testinterface2.h"

TestInterface2::TestInterface2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TestInterface2)
{
    ui->setupUi(this);

    ControllerNiryo = new NiryoController();

    InfoNiryo = new NiryoInfo(ControllerNiryo);

    //connect(ui->horizontalSlider_axe1,&QAbstractSlider::)


    connect(ui->pushButton_fermer,&QPushButton::clicked,this, &TestInterface2::close);
    connect(ui->pushButton_Connecter,&QPushButton::clicked,this, &TestInterface2::connecterRobot);
    connect(ui->pushButton_Deconnecter,&QPushButton::clicked,this, &TestInterface2::deconnecterRobot);
    connect(ui->pushButton_Calibration,&QPushButton::clicked,this, &TestInterface2::lancerCalibration);
    connect(ui->pushButton_lPosZero,&QPushButton::clicked,this, &TestInterface2::positionZero);
    connect(ui->pushButton_lPosRepo,&QPushButton::clicked,this, &TestInterface2::positionRepo);
    connect(ui->pushButton_LancerMouvement,&QPushButton::clicked,this, &TestInterface2::lancerMouvement);
    connect(ui->pushButton_verifierConnection,&QPushButton::clicked,this, &TestInterface2::verifierEtatConnection);
    connect(ui->pushButton_MetteAJour,&QPushButton::clicked,this, &TestInterface2::mettreAJourInfo);
    connect(ui->pushButton_IndexationTajectoire,&QPushButton::clicked,this, &TestInterface2::indexerTrajectoirs);
    connect(ui->pushButton_ArretUrgence,&QPushButton::clicked,this, &TestInterface2::stopperRobot);
    connect(ui->pushButton_LancerTrajectoir,&QPushButton::clicked,this, &TestInterface2::lancerTrajectoire);
    connect(ui->pushButton_attraper,&QPushButton::clicked,this, &TestInterface2::attaperObjet);
    connect(ui->pushButton_lacher,&QPushButton::clicked,this, &TestInterface2::lacherObjet);
    connect(ui->pushButton_modeApprentissage,&QPushButton::clicked,this, &TestInterface2::modeApprentissage);
    connect(ui->pushButton_drapeau,&QPushButton::clicked,this, &TestInterface2::drapeau);
    connect(ui->pushButton_annulerApprentissage,&QPushButton::clicked,this, &TestInterface2::annulerApprentissage);
}

TestInterface2::~TestInterface2()
{
    ControllerNiryo->deconnecterRobot();
    qDebug() << "deconnecter";
    delete ControllerNiryo;
    delete InfoNiryo;
    delete ui;
}

void TestInterface2::connecterRobot()
{
    if(ControllerNiryo->connecterRobot("192.168.1.10:5020","192.168.1.10:5022")){
        qDebug() << "connexion lancer";
    } else {
        qDebug() << "echec de connection";
    }
}

void TestInterface2::verifierEtatConnection()
{
    if(ControllerNiryo->verifierConnection()){
        qDebug() << "connexion bonne";
    } else {
        qDebug() << "connexion perdue";
    }
}

void TestInterface2::deconnecterRobot()
{
    ControllerNiryo->deconnecterRobot();
    qDebug() << "deconnecter";
}

void TestInterface2::lancerMouvement()
{
    QList<float> positionCible = {0.00,0.00,0.00,0.00,0.00,0.00};

    positionCible[0] = (float)(ui->horizontalSlider_axe1->value())/1000;
    positionCible[1] = (float)(ui->horizontalSlider_axe2->value())/1000;
    positionCible[2] = (float)(ui->horizontalSlider_axe3->value())/1000;
    positionCible[3] = (float)(ui->horizontalSlider_axe4->value())/1000;
    positionCible[4] = (float)(ui->horizontalSlider_axe5->value())/1000;
    positionCible[5] = (float)(ui->horizontalSlider_axe6->value())/1000;
    qDebug() << positionCible;
    if(ControllerNiryo->lancerMovement(positionCible,false)){
        qDebug() << " mvmt lancer ";
    } else {
        qDebug() << " erreur lors du mvmt ";
        qDebug() << " erreur : " << ControllerNiryo->getLastError();
    }
}

void TestInterface2::positionZero()
{
    QList<float> positionCible = {0.00,0.00,0.00,0.00,0.00,0.00};
    qDebug() << positionCible;
    if(ControllerNiryo->lancerMovement(positionCible,false)){
        qDebug() << " mvmt lancer ";
    } else {
        qDebug() << " erreur lors du mvmt ";
        qDebug() << " erreur : " << ControllerNiryo->getLastError();
    }
}

void TestInterface2::positionRepo()
{
    PoseNiryo repo(0.00,0.50,-1.25,0.00,0.00,0.00,false);
    if(ControllerNiryo->lancerMovement(repo)){
        qDebug() << " mvmt repo lancer ";
    } else {
        qDebug() << " erreur lors du mvmt ";
        qDebug() << " erreur : " << ControllerNiryo->getLastError();
    }
}

void TestInterface2::lancerCalibration()
{
    if(ControllerNiryo->lancerCalibration()){
        qDebug() << "calib lancer";
    } else {
        qDebug() << "calib bug";
        qDebug() << " erreur : " << ControllerNiryo->getLastError();
    }
}

void TestInterface2::mettreAJourInfo()
{
    if(InfoNiryo->actualiserInformations()){
        qDebug() << "actualisaton effectuer";
    } else {
        qDebug() << "actualisaton échouer";
    }

    InfoNiryo->debugDump();
    ControllerNiryo->debugDump();
}

void TestInterface2::indexerTrajectoirs()
{
    bool ok = false;

    trajectoirs = ControllerNiryo->indexerLesTrajecoirs(ok);
    if(!ok){
        qDebug() << "echec de l'indexation";
        qDebug() << " erreur : " << ControllerNiryo->getLastError();
    } else {
        qDebug() << "reussit de l'indexation";

    }
    ControllerNiryo->trajectoirDebugDump(trajectoirs);


}

void TestInterface2::stopperRobot()
{
    if(ControllerNiryo->stopperRobot()){
        qDebug() << "arret envoyer";
    } else {
        qDebug() << "arret echouer";
        qDebug() <<  ControllerNiryo->getLastError();
    }
}

void TestInterface2::lancerTrajectoire()
{
    if(ControllerNiryo->lancerTrajectoir(trajectoirs.value(ui->spinBox_trajectoire->value()))){
        qDebug() << "lancement de trajectoir reussi";
    } else {
        qDebug() << "lancement de trajectoir échoué";
        qDebug() << "erreur: " << ControllerNiryo->getLastError();
    }

}

void TestInterface2::attaperObjet()
{
    if(ControllerNiryo->actionnerOutil(true)){
        qDebug() << "outil actionner";
    } else {
        qDebug() << "erreur : " + ControllerNiryo->getLastError();
    }

}

void TestInterface2::lacherObjet()
{
    if(ControllerNiryo->actionnerOutil(false)){
        qDebug() << "outil actionner";
    } else {
        qDebug() << "erreur : " + ControllerNiryo->getLastError();
    }
}

void TestInterface2::modeApprentissage()
{
    if(ControllerNiryo->lancerApprentissage()){
        qDebug() << "mode apprentissage lancer";
    } else {
        qDebug() << "echec mode apprentissage";
        qDebug() << "erreur : " + ControllerNiryo->getLastError();
    }
}

void TestInterface2::drapeau()
{
    if(ControllerNiryo->lancerDrapeau()){
        qDebug() << "marquage de drapau reussi";
    } else {
        qDebug() << "marquage de drapau echouer";
        qDebug() << "erreur : " + ControllerNiryo->getLastError();
    }
}

void TestInterface2::annulerApprentissage()
{
    if(ControllerNiryo->annulerAprentissage()){
        qDebug() << "apprentissage annuler";
    } else {
        qDebug() << "echec d'annulation de l'apprentissage";
        qDebug() << "erreur : " + ControllerNiryo->getLastError();
    }
}

