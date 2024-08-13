#include "modbusutil.h"

QString ModbusUtil::_error = "";

// Fonction qui crée une requête Modbus pour écrire dans des registres
QModbusDataUnit ModbusUtil::writeRequest()
{
    return QModbusDataUnit(QModbusDataUnit::RegisterType::Coils, 0x0000 , 0x000F );
}
// Fonction qui crée une requête Modbus pour lire les entrées
QModbusDataUnit ModbusUtil::readRequest()
{
    return QModbusDataUnit(QModbusDataUnit::RegisterType::DiscreteInputs,0x0000 ,0x0011 );
}


QModbusReply* ModbusUtil::sendWriteRequest(QModbusTcpClient &modbusClient, QModbusDataUnit writeUnit){

    QEventLoop loop;

    QObject::connect(&modbusClient, &QModbusTcpClient::stateChanged, &loop, [&loop](QModbusTcpClient::State state){
        if(state == QModbusTcpClient::ConnectedState)
            loop.quit();
    });

    if (modbusClient.state() != QModbusTcpClient::ConnectedState) {
        setError("Failed to connect to Modbus device");
        return nullptr;
    }

    QModbusReply *reply = modbusClient.sendWriteRequest(writeUnit, 1);
    if (!reply) {
        setError("Failed to send read request");
        return nullptr;
    }

    if (!reply->isFinished()) {
        QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
        loop.exec(); // Wait for reply
    }

    if (!reply->isFinished()) {
        setError("Device disconnected");
        return nullptr;
    }

    if (reply->error() != QModbusDevice::NoError) {
        setError("Read error: " + reply->errorString());
        return nullptr;
    }

    return reply;
}

QModbusReply* ModbusUtil::sendReadRequest(QModbusTcpClient &modbusClient, QModbusDataUnit readUnit){
    QEventLoop loop;

    QObject::connect(&modbusClient, &QModbusTcpClient::stateChanged, &loop, [&loop](QModbusTcpClient::State state){
        if(state == QModbusTcpClient::ConnectedState)
            loop.quit();
    });

    if (modbusClient.state() != QModbusTcpClient::ConnectedState) {
        setError("Failed to connect to Modbus device");
        return nullptr;
    }

    QModbusReply *reply = modbusClient.sendReadRequest(readUnit, 2);
    if (!reply) {
        setError("Failed to send read request");
        return nullptr;
    }

    if (!reply->isFinished()) {
        QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
        loop.exec(); // Wait for reply
    }

    if (!reply->isFinished()) {
        setError("Device disconnected");
        return nullptr;
    }

    if (reply->error() != QModbusDevice::NoError) {
        setError("Read error: " + reply->errorString());
        return nullptr;
    }

    return reply;
}

void ModbusUtil::setError(QString error) {
    _error = error;
}

QString ModbusUtil::getLastError() {
    QString last = _error;
    _error = "";
    return last;
}

bool ModbusUtil::hasError() {
    return !_error.trimmed().isEmpty();
}
