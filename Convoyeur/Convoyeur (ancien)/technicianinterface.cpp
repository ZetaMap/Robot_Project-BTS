#include "technicianinterface.h"
#include "ui_technicianinterface.h"
#include "modbusutil.h"

//#include "worker.h"
#include <QDebug>
#include <QTimer>
#include <QThread>

TechnicianInterface::TechnicianInterface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TechnicianInterface)
{

    ui->setupUi(this);

    connect(ui->pushButton_quitter, &QPushButton::clicked, this, &TechnicianInterface::close);
    connect(ui->pushButton_connexion,&QPushButton::clicked, this, &TechnicianInterface::connexion);
    connect(ui->pushButton_deconnexion,&QPushButton::clicked, this,&TechnicianInterface::deconnexion);
    connect(ui->pushButton_Marche_avant,&QPushButton::clicked,this,&TechnicianInterface::marcheAvant);
    connect(ui->pushButton_Marche_arriere,&QPushButton::clicked,this,&TechnicianInterface::marcheArrière);
    connect(ui->pushButton_marche,&QPushButton::clicked,this,&TechnicianInterface::marche);
    connect(ui->pushButton_Stop,&QPushButton::clicked, this,&TechnicianInterface::arret);
    connect(ui->pushButton_read,&QPushButton::clicked,this,&TechnicianInterface::boucleCapteurs);
    connect(ui->pushButton_auto,&QPushButton::clicked,this,&TechnicianInterface::boucleAuto);
    connect(ui->pushButton_vert,&QPushButton::clicked,this,&TechnicianInterface::voyantVert);
    connect(ui->pushButton_rouge,&QPushButton::clicked,this,&TechnicianInterface::voyantRouge);
    connect (ui->pushButton_manuel,&QPushButton::clicked,this,&TechnicianInterface::manuel);
    ui->lineEdit_IP->setText("192.168.1.122");
    ui->lineEdit_Port->setText("502");

    convoyeur = new Convoyeur();

    Style_default();
}


TechnicianInterface::~TechnicianInterface() {
    delete convoyeur;
    delete ui;
}

void TechnicianInterface::connexion()
{
    if (!convoyeur->connexion(ui->lineEdit_IP->text(), ui->lineEdit_Port->text().toInt())) {
        qDebug() << "Erreur de connexion Modbus:";
        qDebug() << "   - Code d'erreur:" << (ModbusUtil::hasError() ? ModbusUtil::getLastError() : "Unknown error");
    } else {
        qDebug() << "Connexion Modbus réussie:";
        qDebug() << "   - Adresse IP:" << ui->lineEdit_IP->text();
        qDebug() << "   - Port:" << ui->lineEdit_Port->text();
    }

    ui->pushButton_deconnexion->setEnabled(true);
    ui->pushButton_connexion->setEnabled(false);
    ui->lineEdit_IP->setEnabled(false);
    ui->lineEdit_Port->setEnabled(false);

}
void TechnicianInterface::deconnexion()
{
    convoyeur->deconnexion();

    if (!convoyeur->estConnecte()) {
        qDebug() << "Déconnexion Modbus réussie:";
        qDebug() << "   - Adresse IP:" << ui->lineEdit_IP->text();
        qDebug() << "   - Port:" << ui->lineEdit_Port->text();
    } else {
        qDebug() << "Erreur lors de la déconnexion Modbus:";
        qDebug() << "   - :" << (ModbusUtil::hasError() ? ModbusUtil::getLastError() : "Unknown error");
    }

    ui->pushButton_deconnexion->setEnabled(false);
    ui->pushButton_connexion->setEnabled(true);
    ui->lineEdit_IP->setEnabled(true);
    ui->lineEdit_Port->setEnabled(false);

}

void TechnicianInterface::marcheAvant()
{
    if (!convoyeur->marcheAvant())
        statusBar()->showMessage(ModbusUtil::hasError() ? ModbusUtil::getLastError() : "Unknown error");
}


void TechnicianInterface::marcheArrière(){
    if (!convoyeur->marcheArrière())
        statusBar()->showMessage(ModbusUtil::hasError() ? ModbusUtil::getLastError() : "Unknown error");
}

void TechnicianInterface::Style_default(){
    ui->pushButton_auto->setEnabled(true);
    ui->pushButton_manuel->setEnabled(true);
    ui->pushButton_marche->setEnabled(false);
    ui->pushButton_Stop->setEnabled(false);
    ui->pushButton_Marche_arriere->setEnabled(false);
    ui->pushButton_Marche_avant->setEnabled(false);
}
void TechnicianInterface::Style_marche(){

    ui->pushButton_auto->setEnabled(true);
    ui->pushButton_manuel->setEnabled(false);
    ui->pushButton_marche->setEnabled(false);
    ui->pushButton_Stop->setEnabled(true);
    ui->pushButton_Marche_arriere->setEnabled(true);
    ui->pushButton_Marche_avant->setEnabled(true);
}
void TechnicianInterface::Style_manuel(){

    ui->pushButton_auto->setEnabled(true);
    ui->pushButton_manuel->setEnabled(false);
    ui->pushButton_marche->setEnabled(true);
    ui->pushButton_Stop->setEnabled(false);
    ui->pushButton_Marche_arriere->setEnabled(false);
    ui->pushButton_Marche_avant->setEnabled(false);
}
void TechnicianInterface::manuel(){
    Style_manuel();
}
void TechnicianInterface::marche(){

    Style_marche();

    if (!convoyeur->marche())
        statusBar()->showMessage(ModbusUtil::hasError() ? ModbusUtil::getLastError() : "Unknown error");

}
void TechnicianInterface::voyantVert(){
    if (!convoyeur->voyantV())
        statusBar()->showMessage(ModbusUtil::hasError() ? ModbusUtil::getLastError() : "Unknown error");

}

void TechnicianInterface::voyantRouge(){
    if (!convoyeur->voyantR())
        statusBar()->showMessage(ModbusUtil::hasError() ? ModbusUtil::getLastError() : "Unknown error");

}

void TechnicianInterface::Style_arret(){

    ui->pushButton_auto->setEnabled(false);
    ui->pushButton_manuel->setEnabled(false);
    ui->pushButton_marche->setEnabled(true);
    ui->pushButton_Stop->setEnabled(false);
    ui->pushButton_Marche_arriere->setEnabled(false);
    ui->pushButton_Marche_avant->setEnabled(false);
}

void TechnicianInterface::arret(){

    Style_arret();

    if (!convoyeur->arret())
        statusBar()->showMessage(ModbusUtil::hasError() ? ModbusUtil::getLastError() : "Unknown error");
}

void TechnicianInterface::boucleCapteurs() {
    ui->pushButton_read->setEnabled(false);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TechnicianInterface::lireCapteurs);
    timer->start(50);
}

void TechnicianInterface::boucleAuto() {
    ui->pushButton_auto->setEnabled(false);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TechnicianInterface::lireCapteurs);
    connect(timer, &QTimer::timeout, convoyeur, &Convoyeur::autoMode);
    timer->start(100);
}


void TechnicianInterface::lireCapteurs(){
    bool ok = convoyeur->RequestLireCapteurs();

    if (!ok) {
        statusBar()->showMessage(ModbusUtil::hasError() ? ModbusUtil::getLastError() : "Unknown error");
        return;
    }

    ui->textEdit->clear();

    ui->textEdit->append(convoyeur->capteur1_etat ? "pièce détecté" : "RAS");
    ui->textEdit->append(convoyeur->capteur2_etat ? "pièce détecté" : "RAS");
}


