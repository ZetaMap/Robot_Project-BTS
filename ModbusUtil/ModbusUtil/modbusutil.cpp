#include "modbusutil.h"

#include <QTimer>

bool ModbusUtil::connectDevice(QString address, uint port) {
    setError("");

    if (client == NULL) client = new QModbusTcpClient();

    // Connecte quelques events
    connect(client, &QModbusTcpClient::errorOccurred, [this](QModbusDevice::Error error){
        setError(QString(QMetaEnum::fromType<QModbusDevice::Error>().valueToKey(error)) + ": " + client->errorString());
    });
    connect(client, &QModbusTcpClient::stateChanged, this, &ModbusUtil::stateChanged);

    // Configure connect parameters
    _address = address;
    _port = port;
    client->setConnectionParameter(QModbusDevice::NetworkAddressParameter, _address);
    client->setConnectionParameter(QModbusDevice::NetworkPortParameter, _port);

    // Set timeout
    client->setTimeout(REQUEST_TIMEOUT);
    client->setNumberOfRetries(3);

    // Connect to modbus client
    noReconnect = false;
    reconnectDevice();

    // And return if connected
    return isConnected();
}

void ModbusUtil::reconnectDevice() {
    // Empty pointer, ignore this
    if (client == NULL) {
        setError("No Modbus device");
        return;
    }

    // Ignore if already connected or connecting
    if (isConnected() || connecting || noReconnect) return;

    // Connect device
    client->connectDevice();
    connecting = true;
    setError("Connecting ...");

    // Wait for connected
    QEventLoop *loop = new QEventLoop();
    // For timeout
    QTimer *timer = new QTimer();

    connect(timer, &QTimer::timeout, [this, loop](){
        loop->quit();
        connecting = false;
        setError("Connect Timeout");
    });
    connect(client, &QModbusDevice::stateChanged, [this, loop, timer](QModbusDevice::State state) {
        if (state == QModbusDevice::State::ConnectedState) {
            connecting = false;
            setError("Connected");
            timer->stop();
            loop->quit();
        }
    });
    connect(client, &QModbusDevice::errorOccurred, [this, loop, timer](QModbusDevice::Error error) {
        if (error != QModbusDevice::Error::NoError) {
            setError(QString(QMetaEnum::fromType<QModbusDevice::Error>().valueToKey(error)) + " while connecting");
            connecting = false;
            timer->stop();
            loop->quit();
        }
    });

    timer->setSingleShot(true);
    timer->start(CONNECT_TIMEOUT);
    loop->exec(); // Wait for connected
}


void ModbusUtil::disconnectDevice() {
    // Empty pointer, ignore this
    if (client == NULL) {
        setError("No Modbus device");
        return;

    // Ignore if not connected
    } else if (!isConnected()) {
        setError("Device not connected");
        return;
    }

    // Disconnect the client
    noReconnect = true;
    client->disconnectDevice();
}

bool ModbusUtil::isConnected() {
    // Empty pointer, ignore this
    if (client == NULL) {
        setError("Device not connected");
        return false;
    }

    return client->state() == QModbusDevice::State::ConnectedState;
}


QModbusDataUnit ModbusUtil::createRequest(QModbusDataUnit::RegisterType type, uint address, uint count) {
    return QModbusDataUnit(type, address, count);
}

QModbusDataUnit ModbusUtil::coilsRequest(uint address, uint count) {
    return createRequest(QModbusDataUnit::RegisterType::Coils, address, count);
}

QModbusDataUnit ModbusUtil::discreteInputsRequest(uint address, uint count) {
    return createRequest(QModbusDataUnit::RegisterType::DiscreteInputs, address, count);
}

QModbusDataUnit ModbusUtil::inputRegistersRequest(uint address, uint count) {
    return createRequest(QModbusDataUnit::RegisterType::InputRegisters, address, count);
}

QModbusDataUnit ModbusUtil::holdingRegistersRequest(uint address, uint count) {
    return createRequest(QModbusDataUnit::RegisterType::HoldingRegisters, address, count);
}


QModbusReply* ModbusUtil::sendRequest(QModbusDataUnit unit, ModbusUtil::RequestType type, uint slave) {
    setError("");

    // Empty pointer, ignore this
    if (client == NULL) {
        setError("No Modbus device");
        return NULL;
    }

    // Stop here if we not want to reconnect
    if (noReconnect) return NULL;

    // Try to reconnect the client
    if (!isConnected()) {
       // setError("Device not connected");
        reconnectDevice();
    }

    // If still not connected, set an error
    if (!isConnected()) {
        QString lastError = getLastError();
        setError("Failed to connect device" + (!lastError.isEmpty() ? ": " + lastError : ""));
        return NULL;
    }

    QModbusReply *reply = type == ModbusUtil::RequestType::Read ? client->sendReadRequest(unit, slave) :
                          type == ModbusUtil::RequestType::Write ? client->sendWriteRequest(unit, slave) :
                          type == ModbusUtil::RequestType::ReadWrite ? client->sendReadWriteRequest(unit, unit, slave) :
                          NULL;

    if (reply == NULL) {
        setError("Failed to send request");
        return NULL;
    }

    // If not respond yeet, wait for
    if (!reply->isFinished()) {
        QEventLoop *loop = new QEventLoop();
        // For timeout
        QTimer *timer = new QTimer();

        connect(timer, &QTimer::timeout, [this, loop](){
            loop->quit();
            setError("Request Timeout");
        });
        connect(reply, &QModbusReply::finished, [loop, timer]() {
            timer->stop();
            loop->quit();
        });
        connect(client, &QModbusDevice::stateChanged, [this, loop, timer](QModbusDevice::State state) {
            if (state == QModbusDevice::State::UnconnectedState) {
                setError("Disconnected");
                timer->stop();
                loop->quit();
            }
        });
        connect(client, &QModbusDevice::errorOccurred, [this, loop, timer](QModbusDevice::Error error) {
            if (error != QModbusDevice::Error::NoError) {
                setError(QString(QMetaEnum::fromType<QModbusDevice::Error>().valueToKey(error)) + " while sending request");
                timer->stop();
                loop->quit();
            }
        });

        timer->setSingleShot(true);
        timer->start(REQUEST_TIMEOUT);
        loop->exec(); // Wait for connected
    }

    if (!reply->isFinished()) {
        return NULL;
    }

    // Check if any errors durring the proccess
    if (reply->error() != QModbusDevice::NoError) {
        setError(QString(QMetaEnum::fromType<ModbusUtil::RequestType>().valueToKey(type)) + " error: " + reply->errorString());
        return NULL;
    }

    return reply;
}

QModbusReply* ModbusUtil::sendWriteRequest(QModbusDataUnit writeUnit, uint slave){
    return sendRequest(writeUnit, ModbusUtil::RequestType::Write, slave);
}

QModbusReply* ModbusUtil::sendReadRequest(QModbusDataUnit readUnit, uint slave){
    return sendRequest(readUnit, ModbusUtil::RequestType::Read, slave);
}

QModbusReply* ModbusUtil::sendReadWriteRequest(QModbusDataUnit readWriteUnit, uint slave) {
    return sendRequest(readWriteUnit, ModbusUtil::RequestType::ReadWrite, slave);
}


void ModbusUtil::setError(QString error) {
    _error = error;
    emit errorOccured(error);
}

QString ModbusUtil::getLastError() {
    QString last = _error;
    _error = "";
    return last;
}

bool ModbusUtil::hasError() {
    return !_error.trimmed().isEmpty();
}
