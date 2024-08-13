#include "afficheur.h"


bool Afficheur::connexion(QString host, int port) {
    return modbusClient->connectDevice(host, port);
}

void Afficheur::deconnexion() {
    modbusClient->disconnectDevice();
}

bool Afficheur::estConnecte() {
    return modbusClient->isConnected();
}

QModbusDataUnit Afficheur::formatterTexte(QModbusDataUnit requete, QString texte, bool clignote) {
    // Prend en charge le retour à la ligne (\n).
    // Remplis la différence de caractère, par des espaces.
    texte = texte.replace("\\n", "\n");
    int finLigne = texte.indexOf('\n');
    if (finLigne != -1)
        texte.replace('\n', QString(" ").repeated(NB_CHARS-finLigne));

    // Remplis le reste du texte avec des espaces,
    // pour remplir l'afficheur
    texte = texte.leftJustified(NB_LETTERS);

    // Convertie le texte en ASCII 8bits
    char* lettres = texte.toLatin1().data();
    int taille = texte.length();

    // Remplace tout les caractères non affichable,
    // non compris entre 0x20 et 0x7F, par '?'.
    for (int i=0; i<taille; i++) {
        if (lettres[i] < 0x20 || lettres[i] > 0x7f)
            lettres[i] = '?';
    }

    // Convertie les caractères en version "clignotante".
    // Comme spécifié dans la documentation de l'afficheur,
    // le 8ème bit doit être mis à 1.
    if (clignote) {
        for (int i=0; i<taille; i++)
            lettres[i] = lettres[i] | 0b10000000;
    }

    // Met deux caractères par mot Modbus
    for (int i=0; i<NB_LETTERS; i+=2)
        requete.setValue((int) i/2, (lettres[i] << 8) | lettres[i+1]);

    return requete;
}


bool Afficheur::afficherTexte(QString texte, bool clignote) {
    // Ne fait rien, si non connecté
    if (!estConnecte()) return false;

    QModbusDataUnit request = modbusClient->holdingRegistersRequest(1, NB_LETTERS);

    // Prépare la requête
    request = formatterTexte(request, texte, clignote);

    // Envoir la requête
    QModbusReply *reply = modbusClient->sendWriteRequest(request);

    // Vérifie les erreurs
    bool ok = reply != NULL;
    if (!ok) return false;
    reply->deleteLater();
    return ok;
}

QList<QString> Afficheur::listerMessages() {
    QList<QString> messages;

    // Ne fait rien, si non connecté ou si une opération
    // de listage est déjà en cours
    if (!estConnecte() || _listage_messages) return messages;
    _listage_messages = true;

    return messages;

    /* Fonction non terminé */
/*
    QModbusDataUnit request = modbusClient->inputRegistersRequest(1, MAX_MESSAGES*MESSAGE_SIZE);
    QModbusReply *reply = modbusClient->sendReadRequest(request);

    // Vérifie les erreurs
    bool ok = reply != NULL;
    if (!ok) {
        _listage_messages = false;
        return messages;
    }

    // Décode la réponse
    // ...


    _listage_messages = false;
    reply->deleteLater();
    return messages;
*/
}

bool Afficheur::enregistrerMessage(uint numero, QString texte, bool clignote) {
    // Ne fait rien, si non connecté ou si le message
    // demandé est en dehors de la mémoire
    if (!estConnecte() || numero < 1 || numero > MAX_MESSAGES+1) return false;

    // Remplis le reste du texte avec des espaces
    texte = texte.leftJustified(MESSAGE_SIZE);

    /* Fonction non terminé */
/*
    QModbusDataUnit request = modbusClient->holdingRegistersRequest(NB_LETTERS*numero, NB_LETTERS);

    // Prépare la requête
    request = formatterTexte(request, texte, clignote);

    // Envoir la requête
    QModbusReply *reply = modbusClient->sendWriteRequest(request);

    // Vérifie les erreurs
    bool ok = reply != NULL;
    if (!ok) return false;
    reply->deleteLater();
    return ok;
*/
    return true;

}

bool Afficheur::afficherMessage(uint numero) {
    // Ne fait rien, si non connecté ou si le message
    // demandé est en dehors de la mémoire
    if (!estConnecte() || numero < 1 || numero > MAX_MESSAGES+1) return false;



    return true;

    /* Fonction non terminé */

}


bool Afficheur::viderMesssage() {
    return afficherTexte("");
}


