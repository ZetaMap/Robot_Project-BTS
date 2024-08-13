#ifndef MODBUSUTIL_H
#define MODBUSUTIL_H


#include <QDebug>
#include <QModbusTcpClient>
#include <QModbusDataUnit>
#include <QModbusTcpServer>
#include <QModbusReply>
#include <QThread>
#include <QEventLoop>
#include <QString>

class ModbusUtil
{
public:
    static QModbusReply* sendWriteRequest(QModbusTcpClient &modbusClient, QModbusDataUnit writeUnit);
    static QModbusDataUnit writeRequest();
    static QModbusDataUnit readRequest();
    static QModbusReply* sendReadRequest(QModbusTcpClient &modbusClient, QModbusDataUnit readUnit);

    static void setError(QString error);
    static QString getLastError();
    static bool hasError();

private:
    static QString _error;
};


#endif // MODBUSUTIL_H
