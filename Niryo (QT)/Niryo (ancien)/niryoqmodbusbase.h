/*
    Cette class est destiner a gerer la communcication avec le niryo
    en utilisant qmodbus tout en essayant de garder la compatibiliter avec la class Niryo
    qui utilise ModLib
*/

#ifndef NIRYOQMODBUSBASE_H
#define NIRYOQMODBUSBASE_H


enum serverID
{
    ServerNormal = 1,
    ServerCustom = 2,
};

enum TypeDeCommunication
{
    Raw = 0,
    Read = 1,
    Write = 2,
    ReadWrite = 3,
};



#include <QModbusTcpClient>
#include <QModbusDataUnit>
#include <QVariant>



class NiryoQModBusBase
{
private:
    QModbusTcpClient *serverNormal;
    QModbusTcpClient *serverCustom;

    QString error;

public:
    NiryoQModBusBase();
    ~NiryoQModBusBase();
    bool connecterNiryo(const QString& IP1,quint16 port1,const QString &IP2 , quint16 port2);
    void deconnecterNiryo();
    int temperatureRaspBerry();//fonction de test
    int getState(serverID SID);
    bool isConnected(serverID SID);
    QString errorStringNormal() const;
    QString errorStringCustom() const;
    QList<quint16> communication(serverID SID,TypeDeCommunication typeCom,QModbusDataUnit _data,bool *ok);
    QString getError();

};

#endif // NIRYOQMODBUSBASE_H
