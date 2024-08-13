#include "piloterobotmi10.h"
#include "ui_piloterobotmi10.h"

PiloteRobotMi10::PiloteRobotMi10(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PiloteRobotMi10)
{
    ui->setupUi(this);

    ui->spinBox->setMinimum(1);
    ui->spinBox->setMaximum(8);
    ui->spinBox->setValue(8);

    //robotMi10 = new EsclaveModbusTCP("172.20.81.100",35);
    robotMi10 = new EsclaveModbusTCP("192.168.1.11");

    afficherMotsDI();
    timerLire.setInterval(800);
    //timerLire.start();

    connect(ui->pushButton_quitter,&QPushButton::clicked, this, &PiloteRobotMi10::close);

    connect(&timerLire, &QTimer::timeout, this,  &PiloteRobotMi10::lireUOP);
    ui->pushButton_stopLecture->setCheckable(true);
    ui->pushButton_stopLecture->toggle();

    connect(ui->pushButton_stopLecture, &QPushButton::toggled, this, &PiloteRobotMi10::startStopLireUOP);

    connect(ui->pushButton_resetUOP, &QPushButton::clicked, this, &PiloteRobotMi10::resetUOP);
    connect(ui->pushButton_initUOP, &QPushButton::clicked, this, &PiloteRobotMi10::ecrireUOPinit);
    connect(ui->pushButton_faultReset, &QPushButton::clicked, this, &PiloteRobotMi10::ecrireFaultReset);
    connect(ui->pushButton_RSR, &QPushButton::clicked, this, &PiloteRobotMi10::ecrireRSR);

    ui->pushButton_appliquerDI1->setCheckable(true);
    connect(ui->pushButton_appliquerDI1, &QPushButton::toggled, this, &PiloteRobotMi10::ecrireDI1);
    ui->pushButton_appliquerDI2->setCheckable(true);
    connect(ui->pushButton_appliquerDI2, &QPushButton::toggled, this, &PiloteRobotMi10::ecrireDI2);

    connect(ui->pushButton_START,&QPushButton::clicked, this, &PiloteRobotMi10::ecrireSTART );

    ui->pushButton_HOLD->setCheckable(true);
    connect(ui->pushButton_HOLD, &QPushButton::toggled, this, &PiloteRobotMi10::ecrireHOLD);

    connect(ui->pushButton_CSTOPI, &QPushButton::clicked, this, &PiloteRobotMi10::ecrireCSTOPI);
}

PiloteRobotMi10::~PiloteRobotMi10()
{
    delete robotMi10;
    delete ui;
}

void PiloteRobotMi10::afficherStatutModbus()
{
    ui->label_statusModbusLecture->setText(QString::number(statutModbusLecture));
    ui->label_statusModbusEcriture->setText(QString::number(statutModbusEcriture));
}

void PiloteRobotMi10::afficherMotsDI()
{
    QString svaleur;
    svaleur = QString::number(motsDI[0], 16);
    ui->label_mot0hex->setText(svaleur.toUpper());

    svaleur = QString::number(motsDI[0], 2);
    ui->label_mot0bin->setText(svaleur);

    svaleur = QString::number(motsDI[1], 16);
    ui->label_mot1hex->setText(svaleur.toUpper());

    svaleur = QString::number(motsDI[1], 2);
    ui->label_mot1bin->setText(svaleur);
}

void PiloteRobotMi10::ecrireDI(int num, bool etat)
{
    // DI115=bit2 du mot 0x1
    quint16 bitDI=1<<(num-113);
    if(etat==true) {
        motsDI[1]=motsDI[1] | bitDI;
    } else {
        bitDI =~bitDI;
        motsDI[1]=motsDI[1] & bitDI;
    }
    afficherMotsDI();
    statutModbusEcriture = robotMi10->ecrireNMots(0,2,motsDI);
    afficherStatutModbus();
}

void PiloteRobotMi10::lireUOP()
{
    quint16 mots[2]={0, 0};
    QString svaleur;

    //statutModbusLecture = robotMi10->lireNMots(100, 1, mots);
    statutModbusLecture = robotMi10->lireNMots(10000, 2, mots);
    afficherStatutModbus();

    svaleur = QString::number(mots[0], 16);
    ui->label_mot10000hex->setText(svaleur.toUpper());

    svaleur = QString::number(mots[0], 2);
    ui->label_mot10000bin->setText(svaleur);

    svaleur="";
    for(int i=0; i<16; i++){
        if( (mots[0]& (1<<i)) != 0)
            svaleur=svaleur + labelDO0[i] +" - ";
    }
    ui->label_mot10000label->setText(svaleur);

    svaleur = QString::number(mots[1], 16);
    ui->label_mot10001hex->setText(svaleur.toUpper());

    svaleur = QString::number(mots[1], 2);
    ui->label_mot10001bin->setText(svaleur);

    svaleur="";
    for(int i=0; i<16; i++){
        if( (mots[1]& (1<<i)) != 0)
            svaleur=svaleur + labelDO1[i] +" - ";
    }
    ui->label_mot10001label->setText(svaleur);
}

void PiloteRobotMi10::startStopLireUOP(bool etat)
{
 if(etat==true) timerLire.stop();
 else timerLire.start();
}

void PiloteRobotMi10::resetUOP()
{
    motsDI[0] = 0;
    motsDI[1] = 0;

    afficherMotsDI();
    //statutModbusEcriture = robotMi10->ecrireNMots(100,1,motsDI);
    statutModbusEcriture = robotMi10->ecrireNMots(0,2,motsDI);
    afficherStatutModbus();
}

void PiloteRobotMi10::ecrireUOPinit()
{
    //IMST+HOLD+SFSPD+ENBL
    quint16 initUOP=0x0087;
    motsDI[0] = motsDI[0] | initUOP;

    afficherMotsDI();
    //statutModbusEcriture = robotMi10->ecrireNMots(100,1, motsDI);
    statutModbusEcriture = robotMi10->ecrireNMots(0, 2, motsDI);
    afficherStatutModbus();
}

void PiloteRobotMi10::ecrireFaultReset()
{
    // FaultReset
    quint16 faultResetUOP=0x0010;
    motsDI[0] = motsDI[0] | faultResetUOP;
    afficherMotsDI();

    //statutModbusEcriture = robotMi10->ecrireNMots(100,1, motsDI);
    statutModbusEcriture = robotMi10->ecrireNMots(0, 2, motsDI);
    afficherStatutModbus();

    QThread::sleep(1);

    faultResetUOP=~faultResetUOP;           // Complément à 1
    motsDI[0] = motsDI[0] & faultResetUOP;
    afficherMotsDI();
    statutModbusEcriture = robotMi10->ecrireNMots(0, 2, motsDI);
    afficherStatutModbus();

}

void PiloteRobotMi10::ecrireSTART()
{
    //quint16 bitStart=0x1<<5;
    quint16 bitStart=0x0020;
    motsDI[0] = motsDI[0] | bitStart;
    afficherMotsDI();
    statutModbusEcriture = robotMi10->ecrireNMots(0,2,motsDI);
    afficherStatutModbus();

    QThread::sleep(1);
    bitStart =~ bitStart;
    motsDI[0] = motsDI[0] & bitStart;
    afficherMotsDI();
    statutModbusEcriture = robotMi10->ecrireNMots(0, 2, motsDI);
    afficherStatutModbus();
}

void PiloteRobotMi10::ecrireHOLD(bool etat)
{
    quint16 bitHOLD = 0x0002;

    // true = HOLD à ON
    if (etat==true){
        motsDI[0] = motsDI[0] | bitHOLD;
    } else {
        motsDI[0] = motsDI[0] & (~bitHOLD);
    }
    afficherMotsDI();
    statutModbusEcriture = robotMi10->ecrireNMots(0, 2, motsDI);
    afficherStatutModbus();
}

void PiloteRobotMi10::ecrireRSR()
{
    //RSR
    int numRSR = ui->spinBox-> value();
    quint16 initUOP=0x1<<(numRSR+7);
    motsDI[0] = (motsDI[0] & 0x00FF) | initUOP;

    afficherMotsDI();
    //statutModbusEcriture = robotMi10->ecrireNMots(100,1, motsDI);
    statutModbusEcriture = robotMi10->ecrireNMots(0, 2, motsDI);
    afficherStatutModbus();

    QThread::sleep(1);
    motsDI[0] = motsDI[0] & 0x00FF;
    afficherMotsDI();
    statutModbusEcriture = robotMi10->ecrireNMots(0, 2, motsDI);
    afficherStatutModbus();
}

void PiloteRobotMi10::ecrireDI1(bool etat)
{
    int numDI=ui->spinBox_DI1->value();
    ecrireDI(numDI, etat);
}

void PiloteRobotMi10::ecrireDI2(bool etat)
{
    int numDI=ui->spinBox_DI2->value();
    ecrireDI(numDI, etat);
}

void PiloteRobotMi10::ecrireCSTOPI()
{
    quint16 bitCSTOPI=0x0008;
    motsDI[0] = motsDI[0] | bitCSTOPI;

    afficherMotsDI();
    statutModbusEcriture = robotMi10->ecrireNMots(0, 2, motsDI);
    afficherStatutModbus();

    QThread::sleep(1);
    motsDI[0] = motsDI[0] & (~bitCSTOPI);
    afficherMotsDI();
    statutModbusEcriture = robotMi10->ecrireNMots(0, 2, motsDI);
    afficherStatutModbus();
}

