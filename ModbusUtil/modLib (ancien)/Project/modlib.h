#ifndef MODLIB_H
#define MODLIB_H

#include "modLib_global.h"
#include <QTcpSocket>
#include <QString>

class MODLIB_EXPORT ModLib {
public:
    ModLib();
    ~ModLib();

    // Connexion et déconnexion
    bool connectToServer(const QString& host, int port);
    void disconnectServer();

    // Lecture et écriture de registres
    QByteArray readHoldingRegisters(int startingAddress, int numberOfRegisters);
    bool writeSingleRegister(int address, const QByteArray& value);

    // Lecture et écriture de disjoncteurs
    QByteArray readCoils(int startingAddress, int numberOfCoils);
    bool writeSingleCoil(int address, bool value);

    // Gestion des erreurs
    QString lastError() const;

private:
    QTcpSocket tcpSocket;
    QString lastErrorMessage;

    // Méthodes utilitaires internes
    void setLastError(const QString& errorMessage);
    QByteArray createModbusRequest(int functionCode, int startingAddress, int valueOrCount);

    // Ajoutez ici d'autres membres privés selon vos besoins
};

#endif // MODLIB_H
