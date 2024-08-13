#ifndef ESCLAVEMODBUSTCP_H
#define ESCLAVEMODBUSTCP_H

#include<QTcpSocket>

// LG pour LONGUEUR
const unsigned int PORT_MODBUS_TCP = 502;
const unsigned int LG_MBAP = 7;

const unsigned int FONCTION_ECRIRE1BIT = 5;
const unsigned int LG_DEMANDE_ECRIRE1BIT = LG_MBAP+5;
const unsigned int LG_REPONSE_ECRIRE1BIT = LG_MBAP+5;

const unsigned char FONCTION_LECTURENMOTS = 3;
const unsigned int LG_DEMANDE_LECTURENMOTS = LG_MBAP+5;
const unsigned int LG_REPONSE_LECTURENMOTS = LG_MBAP+2;

const unsigned char FONCTION_ECRIRENMOTS = 16;
const unsigned int LG_DEMANDE_ECRIRENMOTS = LG_MBAP+6;
const unsigned int LG_REPONSE_ECRIRENMOTS = LG_MBAP+5;

const unsigned int REPONSE_OK=0;
const unsigned int TIMEOUT=2000;
const unsigned int ERREUR_TIMEOUT=-257;
const unsigned int LG_ERREUR=LG_MBAP+2;

class EsclaveModbusTCP {
private:
    QString         _adresseIP;
    int             _numEsclave;
    QTcpSocket      _socket;
    unsigned short  _transactionId;

    unsigned char*  _trameDemande;
    unsigned char*  _trameReponse;
    unsigned char	_fonctionModbus;
    void    connecter();
    void    afficher            (unsigned char* trame, int nbOctets);
    void    remplirMBAP         (int lgTrame);
    int     envoyerTrameDemande (int nbOctets);
    int     recevoirTrameReponse(int nbOctets);

public:
    EsclaveModbusTCP(QString adresseIP, int numEsclave=0);
    int ecrire1Bit  (unsigned short adresse, int valeur);
    int lireNMots   (unsigned short adresse,  unsigned int nbMots, unsigned short* tabMots);
    int	ecrireNMots (unsigned short adresse, unsigned int nbMots, unsigned short* tabMots);
};

#endif // ESCLAVEMODBUSTCP_H
