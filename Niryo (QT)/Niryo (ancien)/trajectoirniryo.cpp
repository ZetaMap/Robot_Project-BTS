#include "trajectoirniryo.h"


TrajectoirNiryo::TrajectoirNiryo()
{
    ID = 0;
    nom = "";
    index = 0;
    exist = false;
}

TrajectoirNiryo::TrajectoirNiryo(int _ID,QString _nom,int _index) {
    ID = _ID;
    nom = _nom;
    index = _index;
    exist = true;
}

TrajectoirNiryo::TrajectoirNiryo(int _ID, QList<quint16> _reponsenom, int _index)
{
    ID = _ID;
    nom = quint16VersNom(_reponsenom);
    index = _index;
    exist = true;
}


TrajectoirNiryo::~TrajectoirNiryo()
{

}

void TrajectoirNiryo::setTrajectoir(int _ID, QString _nom, int _index)
{
    ID = _ID;
    nom = _nom;
    index = _index;
    exist = true;
}

int TrajectoirNiryo::getID()
{
    return ID;
}

QString TrajectoirNiryo::getNom()
{
    return nom;
}

int TrajectoirNiryo::getIndex()
{
    return index;
}

bool TrajectoirNiryo::getExist()
{
    return exist;
}

QString TrajectoirNiryo::quint16VersNom(QList<quint16> nomQuint16)
{
    QString nom;
    for (int i = 0; i < nomQuint16.length(); i++) { // transformation du nom
        if(nomQuint16.value(i) == 0){
            continue;
        }
        nom.append((char)(nomQuint16.value(i)));
    }

    return nom;
}

QList<quint16> TrajectoirNiryo::nomVersQuint16(QString nom)
{
    char *nomptr;
    QList<quint16> nomQuint16;
    nomptr  = nom.toUtf8().data();


    for (int i = 0; i < nom.length(); i++) {
        if(nomptr[i] < 0x20 ){
            nomQuint16[i] = '?';
        } else {
            nomQuint16[i] = nomptr[i];
        }
    }
    return nomQuint16;
}
