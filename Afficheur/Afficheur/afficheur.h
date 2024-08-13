#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include "Afficheur_global.h"
#include <modbusutil.h>

#include <QList>
#include <QString>


#define NB_LINES   2
#define NB_CHARS   12
#define NB_LETTERS (NB_CHARS*NB_LINES)
#define MAX_MESSAGES 510
#define MESSAGE_SIZE 20 //mots modbus (40 caractères)


class AFFICHEUR_EXPORT Afficheur : public QObject
{
public:
    // public car utilisé pour connecter un event à l'IHM
    ModbusUtil *modbusClient = NULL;

    Afficheur() { modbusClient = new ModbusUtil(); }
    ~Afficheur() {
        deconnexion();
        delete modbusClient;
    }

    bool connexion(QString host, int port);
    void deconnexion();
    bool estConnecte();

    QModbusDataUnit formatterTexte(QModbusDataUnit requete, QString texte, bool clignote);

    bool afficherTexte(QString texte, bool clignote = false);

    QList<QString> listerMessages();
    bool enregistrerMessage(uint numero, QString texte, bool clignote = false);
    bool afficherMessage(uint numero);

    bool viderMesssage();

private:
    // Sécurité pour éviter de saturer le réseau
    // Car lister les messages est une oprétation très lourde
    bool _listage_messages = false;
};

#endif // AFFICHEUR_H
