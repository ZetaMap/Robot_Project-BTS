#ifndef MODBUSUTIL_H
#define MODBUSUTIL_H

#include "ModbusUtil_global.h"

#include <QModbusTcpClient>
#include <QModbusDataUnit>
#include <QModbusTcpServer>
#include <QModbusReply>
#include <QThread>
#include <QEventLoop>
#include <QMetaEnum>

#define REQUEST_TIMEOUT 2000 //ms
#define CONNECT_TIMEOUT 5000 //ms


class MODBUSUTIL_EXPORT ModbusUtil : public QObject
{
    Q_OBJECT

public:
    enum RequestType {
        Read,
        Write,
        ReadWrite,
    };
    Q_ENUM(RequestType)


    ModbusUtil() {}
    ~ModbusUtil() {
        disconnectDevice();
        delete client;
    }

    // Connection things
    bool connectDevice(QString address, uint port);
    void reconnectDevice();
    void disconnectDevice();
    bool isConnected();

    // Create requests
    QModbusDataUnit createRequest(QModbusDataUnit::RegisterType type, uint address, uint count = 1);
    QModbusDataUnit coilsRequest(uint address, uint count = 1);
    QModbusDataUnit discreteInputsRequest(uint address, uint count = 1);
    QModbusDataUnit inputRegistersRequest(uint address, uint count = 1);
    QModbusDataUnit holdingRegistersRequest(uint address, uint count = 1);

    // Methods to send request
    QModbusReply* sendRequest(QModbusDataUnit unit, ModbusUtil::RequestType type, uint slave=1);
    QModbusReply* sendWriteRequest(QModbusDataUnit writeUnit, uint slave=1);
    QModbusReply* sendReadRequest(QModbusDataUnit readUnit, uint slave=1);
    QModbusReply* sendReadWriteRequest(QModbusDataUnit readWriteUnit, uint slave=1);

    // Errors things
    void setError(QString error);
    QString getLastError();
    bool hasError();

signals:
    // Signal to notify an error
    void errorOccured(QString error);
    // Signal to notify state changed
    void stateChanged(QModbusDevice::State state);

private:
    // The client
    QModbusTcpClient* client = NULL;

    QString _error = "";
    bool connecting = false;
    QString _address;
    int _port;
    // Avoid to reconnect the client when asked to deconnect
    bool noReconnect = false;
};

#endif // MODBUSUTIL_H
