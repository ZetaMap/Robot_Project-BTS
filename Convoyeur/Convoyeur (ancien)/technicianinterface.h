#ifndef TECHNICIANINTERFACE_H
#define TECHNICIANINTERFACE_H

#include <QMainWindow>

#include <QDebug>
#include <QModbusTcpClient>
#include <QModbusDataUnit>
#include <QModbusTcpServer>
#include <QModbusReply>

#include "convoyeur.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class TechnicianInterface;
}
QT_END_NAMESPACE

class TechnicianInterface : public QMainWindow
{
    Q_OBJECT

public:

    TechnicianInterface(QWidget *parent = nullptr);
    ~TechnicianInterface();


private:
    Ui::TechnicianInterface *ui;
    Convoyeur *convoyeur;
    bool marcheAvantExecute = false;
    bool arretExecute = false;
    bool voyantVertExecute = false;
    bool voyantRougeExecute = false;

    bool productionTermine = true;

    //function(button)
    void manuel();
    void marche();
    void lireCapteurs();
    void connexion();
    void deconnexion();
    void marcheAvant();
    void marcheArrière();
    void arret();
    void autoMode();
    void voyantVert();
    void voyantRouge();
    void boucleAuto();

    //style
    void Style_marche();
    void Style_arret();
    void Style_default();
    void Style_manuel();

    void boucleCapteurs();

};
#endif // TECHNICIANINTERFACE_H
