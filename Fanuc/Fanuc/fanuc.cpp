#include "fanuc.h"


bool Fanuc::connectDevice(QString address, uint port) {
    return modbusClient->connectDevice(address, port);
}

void Fanuc::disconnectDevice() {
    modbusClient->disconnectDevice();
}

bool Fanuc::isConnected() {
    return modbusClient->isConnected();
}


bool Fanuc::initUop() {
    // IMST+HOLD+SFSPD+ENBL
    return sendValue(state | UOP_INIT);
}

void Fanuc::readUop() {
    // Ignore si non connecté
    if (!isConnected()) return;

    QModbusDataUnit request = modbusClient->holdingRegistersRequest(10000, 2);
    QModbusReply* reply = modbusClient->sendReadRequest(request);

    // Vérifie les erreurs
    _readError = reply == NULL;
    if (_readError) return;

    // Réutilisation de la variable de la requete, pour la réponse
    request = reply->result();

    _rsrStateOK = request.value(0) & RSR_OK_MASK;
    _programExec = request.value(0) & PROGRAM_EXEC_MASK;
    _faultDetected = request.value(0) & FAULT_MASK;

    // Appelle le callback
    emit sensorReaded(request.value(0), request.value(1));

    reply->deleteLater();
}

bool Fanuc::resetUop() {
    di = 0;
    return sendValue(0);
}


bool Fanuc::triggerDI(int num) {
    di = di | BIT_DI(num);
    if (!sendValue(state)) return false;
    QThread::msleep(PULSE_SLEEP);
    di = di & (~BIT_DI(num));
    return sendValue(state);
}

bool Fanuc::waitForDO(int num, long timeout){
    startSensorLoop();

    QEventLoop *loop = new QEventLoop();
    QTimer *timer = new QTimer();

    connect(timer, &QTimer::timeout, [&timeout, loop]() {
        timeout = -1;
        loop->quit();
    });
    connect(this, &Fanuc::sensorReaded, [this, &timeout, &num, loop, timer](quint16 mot1, quint16 mot2) {
        qDebug()<< QString::number(mot2, 2) << (mot2 & BIT_DO(num));
        if (mot2 & BIT_DO(num)) {
            timer->stop();
            loop->quit();

        } else if (!programExec()) {
            timeout = -1;
            timer->stop();
            loop->quit();
        }
    });

    readUop();
    timer->setSingleShot(true);
    timer->start(timeout);
    loop->exec();

    return timeout != -1;
}



bool Fanuc::faultReset() {
    return sendPulse(FAULT_RESET);
}

bool Fanuc::startRsr() {
    return sendPulse(RSR_START);
}

bool Fanuc::holdRsr(bool resume) {
    return sendValue(resume ? state | RSR_HOLD : state & (~RSR_HOLD));
}

bool Fanuc::selectRsr(int rsr) {
    // Stop the current RSR first
    stopRsr();

    if (!sendValue((state & 0xff) | RSR_UOP(rsr))) return false;
    QThread::msleep(PULSE_SLEEP);
    return sendValue(state & 0xff);
}

bool Fanuc::stopRsr() {
    return sendPulse(CSTOPI);
}

bool Fanuc::emergencyStop() {
    return sendPulse(IMSTP);
}


void Fanuc::startSensorLoop(){
    // Check if connected, first
    if (!isConnected()) return;
    // Avoid to run another time the auto mode
    if (sensorLoopRunning()) return;

    if (timer == NULL) {
        timer = new QTimer();
        connect(timer, &QTimer::timeout, this, &Fanuc::readUop);
    }

    timer->start(SENSOR_READ_DELAY);
    readUop();
    emit sensorLoopStatus();
}

void Fanuc::stopSensorLoop(){
    if (!sensorLoopRunning()) return;

    // Stop the timer
    timer->stop();
    // Wait a little if still active
    if (timer->isActive()) QThread::msleep(100);

    emit sensorLoopStatus();
}


bool Fanuc::sendValue(int value) {
    // Ignore si non connecté
    if (!isConnected()) return false;

    state = value;

    QModbusDataUnit request = modbusClient->holdingRegistersRequest(0, 2);
    request.setValue(0, state);
    request.setValue(1, di);

    QModbusReply* reply = modbusClient->sendWriteRequest(request);

    // Vérifie les erreurs
    bool ok = reply != NULL;
    if (!ok) return false;
    reply->deleteLater();
    return ok;
}

bool Fanuc::sendPulse(int value) {
    if (!sendValue(state | value)) return false;
    QThread::msleep(PULSE_SLEEP);
    return sendValue(state & (~value));
}
