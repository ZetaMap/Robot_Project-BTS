#include "modlib.h"

ModLib::ModLib() {
    // Constructeur: peut être utilisé pour initialiser des paramètres ou des ressources
}

ModLib::~ModLib() {
    // Destructeur: s'assure que la connexion TCP est fermée proprement
    disconnectServer();
}

bool ModLib::connectToServer(const QString& host, int port) {
    // Établit une connexion TCP avec le serveur Modbus
    tcpSocket.connectToHost(host, port);
    if (!tcpSocket.waitForConnected()) {
        // En cas d'échec, stocke le message d'erreur et retourne false
        setLastError(tcpSocket.errorString());
        return false;
    }
    return true;
}

void ModLib::disconnectServer() {
    // Ferme la connexion TCP si elle est ouverte
    if (tcpSocket.isOpen()) {
        tcpSocket.close();
    }
}

QByteArray ModLib::readHoldingRegisters(int startingAddress, int numberOfRegisters) {
    // Construit une requête Modbus pour lire des registres de maintien
    QByteArray request = createModbusRequest(3, startingAddress, numberOfRegisters);
    // Envoie la requête au serveur
    tcpSocket.write(request);
    if (!tcpSocket.waitForBytesWritten()) {
        setLastError(tcpSocket.errorString());
        return QByteArray();
    }
    // Attend une réponse du serveur
    if (!tcpSocket.waitForReadyRead()) {
        setLastError(tcpSocket.errorString());
        return QByteArray();
    }
    // Retourne la réponse du serveur
    return tcpSocket.readAll();
}

bool ModLib::writeSingleRegister(int address, const QByteArray& value) {
    // Construit et envoie une requête pour écrire un registre
    QByteArray request = createModbusRequest(6, address, value.toInt());
    tcpSocket.write(request);
    return tcpSocket.waitForBytesWritten();
}

QByteArray ModLib::readCoils(int startingAddress, int numberOfCoils) {
    // Similaire à readHoldingRegisters, mais pour lire l'état des disjoncteurs
    QByteArray request = createModbusRequest(1, startingAddress, numberOfCoils);
    tcpSocket.write(request);
    if (!tcpSocket.waitForBytesWritten()) {
        setLastError(tcpSocket.errorString());
        return QByteArray();
    }
    if (!tcpSocket.waitForReadyRead()) {
        setLastError(tcpSocket.errorString());
        return QByteArray();
    }
    return tcpSocket.readAll();
}

bool ModLib::writeSingleCoil(int address, bool value) {
    // Construit et envoie une requête pour changer l'état d'un disjoncteur
    QByteArray request = createModbusRequest(5, address, value ? 0xFF00 : 0x0000);
    tcpSocket.write(request);
    return tcpSocket.waitForBytesWritten();
}

QString ModLib::lastError() const {
    // Retourne le dernier message d'erreur enregistré
    return lastErrorMessage;
}

void ModLib::setLastError(const QString& errorMessage) {
    // Enregistre le message d'erreur spécifié
    lastErrorMessage = errorMessage;
}

QByteArray ModLib::createModbusRequest(int functionCode, int startingAddress, int valueOrCount) {
    // Crée une requête Modbus spécifique en fonction du code de fonction,
    // de l'adresse de départ, et de la valeur ou du nombre de registres/coils
    QByteArray request;

    // Exemple de structure de base d'une requête Modbus :
    // [ID Transaction] [ID Protocole] [Longueur] [ID Unité] [Code Fonction] [Données]

    // ID Transaction - 2 octets: Identifiant unique pour la requête
    request.append((char)0x00); // Octet de poids fort
    request.append((char)0x01); // Octet de poids faible

    // ID Protocole - 2 octets: Toujours 0 pour Modbus/TCP
    request.append((char)0x00); // Octet de poids fort
    request.append((char)0x00); // Octet de poids faible

    // Longueur - 2 octets: Nombre d'octets suivants dans le message
    int length = 6; // 6 octets par défaut pour ID Unité, Code Fonction, et Données
    request.append((char)0x00); // Octet de poids fort
    request.append((char)length); // Octet de poids faible

    // ID Unité - 1 octet: Identifiant de l'unité Modbus (0 pour TCP/IP)
    request.append((char)0x00);

    // Code Fonction - 1 octet: Spécifie la fonction Modbus (par exemple, 0x03 pour lire des registres)
    request.append((char)functionCode);

    // Données - Dépendent de la fonction spécifique
    // Adresse de départ - 2 octets
    request.append((char)((startingAddress >> 8) & 0xFF)); // Octet de poids fort
    request.append((char)(startingAddress & 0xFF));        // Octet de poids faible

    // Valeur ou nombre de registres/coils - 2 octets
    request.append((char)((valueOrCount >> 8) & 0xFF)); // Octet de poids fort
    request.append((char)(valueOrCount & 0xFF));        // Octet de poids faible

    return request;
}
