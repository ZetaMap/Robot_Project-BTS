#include "niryoqmodbusbase.h"
#include "qeventloop.h"




NiryoQModBusBase::NiryoQModBusBase()
{
    serverNormal = new QModbusTcpClient();
    serverNormal->setTimeout(2000);
    serverNormal->setNumberOfRetries(3);

    serverCustom = new QModbusTcpClient();
    serverCustom->setTimeout(2000);
    serverCustom->setNumberOfRetries(3);
}

NiryoQModBusBase::~NiryoQModBusBase()
{
    serverNormal->disconnectDevice();
    serverCustom->disconnectDevice();
    delete serverNormal;
    delete serverCustom;
}

bool NiryoQModBusBase::connecterNiryo(const QString &IP1,quint16 port1,const QString &IP2 , quint16 port2)
{
    serverNormal->setConnectionParameter(QModbusDevice::NetworkPortParameter, port1);
    serverCustom->setConnectionParameter(QModbusDevice::NetworkPortParameter, port2);

    serverNormal->setConnectionParameter(QModbusDevice::NetworkAddressParameter, QVariant(IP1));
    serverCustom->setConnectionParameter(QModbusDevice::NetworkAddressParameter, QVariant(IP2));


    if(!serverNormal->connectDevice()){
        this->error = "erreur de connection:" + serverCustom->errorString();
        return false;
    }

    if(!serverCustom->connectDevice()){
        this->error = "erreur de connection:" + serverCustom->errorString();
        return false;
    }

    return true;
}

void NiryoQModBusBase::deconnecterNiryo()
{
    serverNormal->disconnectDevice();
    serverCustom->disconnectDevice();
}

int NiryoQModBusBase::temperatureRaspBerry()
{
    bool ok = false;
    QList<quint16> resultat;
    QModbusDataUnit readcmd(QModbusDataUnit::InputRegisters,403,1);
    resultat = communication(serverID::ServerNormal,TypeDeCommunication::Read,readcmd,&ok);
    return resultat.value(0);
}

int NiryoQModBusBase::getState(serverID SID)
{
    QModbusTcpClient *tempServptr = nullptr;
    if(SID == serverID::ServerNormal){// choix du serveur et mise dans un pointeur
        tempServptr=serverNormal;
    } else if (SID == serverID::ServerCustom){
        tempServptr=serverCustom;
    }

    if(tempServptr == nullptr){
        this->error = "getState ServerID inconnue";
        return -1;
    }

    int result = tempServptr->state();
    return result;
}

bool NiryoQModBusBase::isConnected(serverID SID)
{
    QModbusTcpClient *tempServptr = nullptr;
    if(SID == serverID::ServerNormal){// choix du serveur et mise dans un pointeur
        tempServptr=serverNormal;
    } else if (SID == serverID::ServerCustom){
        tempServptr=serverCustom;
    }

    if(tempServptr == nullptr){
        this->error = "isconnected ServerID inconnue";
        return -1;
    }
    bool result = false;
    if(tempServptr->state() == 2){
        result = true;
    }
    return result;
}

QString NiryoQModBusBase::errorStringNormal() const
{
    return serverNormal->errorString();
}

QString NiryoQModBusBase::errorStringCustom() const
{
    return serverCustom->errorString();
}

QList<quint16> NiryoQModBusBase::communication(serverID SID,TypeDeCommunication typeCom,QModbusDataUnit _data,bool *ok)
{
    QModbusReply *reply;
    QModbusTcpClient *tempServptr = nullptr;

    if(SID == serverID::ServerNormal){// choix du serveur et mise dans un pointeur
        tempServptr=serverNormal;
    } else if (SID == serverID::ServerCustom){
        tempServptr=serverCustom;
    } else {
        this->error = "communication ServerID inconnue";
        *ok = false;
        return QList<quint16>();
    }

    if(!_data.isValid()){
        this->error = "demande qmodbus non valid";
        *ok = false;
        return QList<quint16>();
    }

    if(tempServptr->state() != QModbusDevice::ConnectedState){
        this->error = "connxion perdue ServerID = " + QString::number(SID);
        *ok = false;
        return QList<quint16>();
    }

    if(typeCom == TypeDeCommunication::Raw){// choix du type de comm. et preparation de la requete
        //reply = tempServptr->sendRawRequest(_data,0);
        this->error = "Type de communcation non supporter: Raw";
        *ok = false;
        return QList<quint16>();
    } else if(typeCom == TypeDeCommunication::Read) {
        reply = tempServptr->sendReadRequest(_data,0);
    } else if(typeCom == TypeDeCommunication::Write) {
        reply = tempServptr->sendWriteRequest(_data,0);
    } else if(typeCom == TypeDeCommunication::ReadWrite) {
        //reply = tempServptr->sendReadWriteRequest(_data1,_data2,0);
        this->error = "Type de communcation non supporter: ReadWrite";
        *ok = false;
        return QList<quint16>();
    } else {
        this->error = "Type de communcation inconnue";
        *ok = false;
        return QList<quint16>();
    }

    QEventLoop loop;
    QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
    loop.exec();


    const QModbusDataUnit result=reply->result();

    *ok = true;
    return result.values();
}

QString NiryoQModBusBase::getError()
{
    return error;
}
