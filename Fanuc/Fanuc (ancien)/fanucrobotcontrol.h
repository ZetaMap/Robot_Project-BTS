#ifndef FANUCROBOTCONTROL_H
#define FANUCROBOTCONTROL_H

#include <QMainWindow>
#include <modbus/modbus.h>
#include <QTimer>

class FanucRobotControl : public QMainWindow
{
    Q_OBJECT

public:
    FanucRobotControl(QWidget *parent = nullptr);
    ~FanucRobotControl();

private slots:
    void connectToRobot();
    void startProgram();
    void pauseProgram();
    void stopProgram();
    void updateUopValues();
    void updateUopValuesPeriodically();

private:
    // UI Components
    QLineEdit *ipAddressLineEdit;
    QPushButton *connectButton;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *stopButton;
    QLabel *statusLabel;
    QLabel *uopStatusLabel;

    // Modbus variables
    modbus_t *modbusContext;
    QString ipAddress;
    int modbusServerPort;

    // Modbus addresses for UOP words
    const int uopStartAddress = 97;
    const int uopNumWords = 20;

    // Array to store UOP values
    QVector<int> uopValues;

    // Timer for periodic update
    QTimer *updateTimer;

    // Functions
    void setupUi();
    void setupModbus();
};

#endif // FANUCROBOTCONTROL_H
