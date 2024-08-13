#ifndef FANUC_H
#define FANUC_H

#include "Fanuc_global.h"
#include <modbusutil.h>

#include <QTimer>
#include <QEventLoop>


#define SENSOR_READ_DELAY 100 //ms
#define PULSE_SLEEP 200 //ms

#define UOP_INIT    0b0000000010000111
#define FAULT_RESET 0b0000000000010000
#define RSR_START   0b0000000000100000
#define RSR_HOLD    0b0000000000000010
#define CSTOPI      0b0000000000001000
#define IMSTP       0b0000000000000000

#define RSR_OK_MASK       0b0000000000000001
#define PROGRAM_EXEC_MASK 0b0000000000000100
#define FAULT_MASK        0b0000000000100000

// macro
#define RSR_UOP(rsr) (1 << (rsr + 7))
#define BIT_DI(num)  (1 << (num - 113))
#define BIT_DO(num)  (1 << (num - 129))


class FANUC_EXPORT Fanuc : public QObject
{
    Q_OBJECT

public:
    Fanuc() { modbusClient = new ModbusUtil(); }
    ~Fanuc() {
        disconnect();
        delete modbusClient;
        delete timer;
    }


    bool connectDevice(QString address, uint port);
    void disconnectDevice();
    bool isConnected();

    // Gestion des UOP (User Operator Panel)
    bool initUop();
    void readUop();
    bool resetUop();

    bool triggerDI(int num);
    // Return false if timeout, else true
    bool waitForDO(int num, long timeout=10000); //ms

    bool faultReset();
    bool startRsr();
    bool selectRsr(int rsr);
    bool holdRsr(bool resume);
    bool stopRsr();
    bool emergencyStop();

    // boucle capteurs
    void startSensorLoop();
    void stopSensorLoop();

    // accesseurs
    bool rsrStateOK() { return _rsrStateOK; }
    bool programExec() { return _programExec; }
    bool faultDetected() { return _faultDetected; }
    bool sensorReadError() { return _readError; }
    bool sensorLoopRunning() { return timer != NULL && timer->isActive(); }

    ModbusUtil *modbusClient;

protected:
    bool sendValue(int value);
    bool sendPulse(int value);

    // Signaux, utilisable avec connect() pour être notifié d'évènements
signals:
    void sensorReaded(quint16 mot1, quint16 mot2);
    void sensorLoopStatus();

private:
    quint16 state = 0, di = 0;
    bool _rsrStateOK = false, _programExec = false,
        _faultDetected = false, _readError = false;
    QTimer *timer = NULL;
};

#endif // FANUC_H
