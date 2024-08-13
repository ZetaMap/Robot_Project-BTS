#ifndef PILOTEROBOTMI10_H
#define PILOTEROBOTMI10_H

#include <QMainWindow>
#include <QTimer>
#include <QThread>
#include "esclavemodbustcp.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PiloteRobotMi10; }
QT_END_NAMESPACE

class PiloteRobotMi10 : public QMainWindow
{
    Q_OBJECT

public:
    PiloteRobotMi10(QWidget *parent = nullptr);
    ~PiloteRobotMi10();

private:
    Ui::PiloteRobotMi10 *ui;
    EsclaveModbusTCP* robotMi10;
    QTimer timerLire;
    quint16 motsDI[2]={0,0};
    QString labelDO0[16]={"CMDENBL","SYSRDY","PROGRAM","PAUSED","HELD","FAULT","ATPERCH","TPENBL","BATALM","BUSY","ACK1","ACK2","ACK3","ACK4","ACK5","ACK6"};
    QString labelDO1[16]={"ACK7","ACK8","SNACK","RESERVED","DO133","DO134","DO135","DO136","DO137","DO138","DO139","DO140","DO141","DO142","DO143","DO144"};
    int statutModbusLecture=-1;
    int statutModbusEcriture=-1;
    void afficherStatutModbus();
    void afficherMotsDI();
    void ecrireDI(int num, bool etat);


private slots:
    void lireUOP();
    void startStopLireUOP(bool etat);
    void resetUOP();
    void ecrireUOPinit();
    void ecrireFaultReset();
    void ecrireSTART();
    void ecrireHOLD(bool etat);
    void ecrireRSR();
    void ecrireDI1(bool etat);
    void ecrireDI2(bool etat);
    void ecrireCSTOPI();

};
#endif // PILOTEROBOTMI10_H
