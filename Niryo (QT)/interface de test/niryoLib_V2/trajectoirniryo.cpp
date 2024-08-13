#include "trajectoirniryo.h"


TrajectoireNiryo::TrajectoireNiryo()
{
    ID = 0;
    nom = "";
    index = 0;
    exist = false;
}

TrajectoireNiryo::TrajectoireNiryo(int _ID,QString _nom,int _index) {
    ID = _ID;
    nom = _nom;
    index = _index;
    exist = true;
}

TrajectoireNiryo::TrajectoireNiryo(int _ID, QList<quint16> _reponsenom, int _index)
{
    ID = _ID;
    nom = quint16VersNom(_reponsenom);
    index = _index;
    exist = true;
}


TrajectoireNiryo::~TrajectoireNiryo()
{

}

void TrajectoireNiryo::setTrajectoir(int _ID, QString _nom, int _index)
{
    ID = _ID;
    nom = _nom;
    index = _index;
    exist = true;
}

int TrajectoireNiryo::getID()
{
    return ID;
}

QString TrajectoireNiryo::getNom()
{
    return nom;
}

QList<quint16> TrajectoireNiryo::getNomQuint16()
{
    return nomVersQuint16(nom);
}

int TrajectoireNiryo::getIndex()
{
    return index;
}

bool TrajectoireNiryo::getExist()
{
    return exist;
}

QString TrajectoireNiryo::quint16VersNom(QList<quint16> nomQuint16)
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

QList<quint16> TrajectoireNiryo::nomVersQuint16(QString nom)
{
    char *nomptr;
    QList<quint16> nomQuint16;
    nomptr  = nom.toUtf8().data();


    for (int i = 0; i < nom.length(); i++) {
        if(nomptr[i] < 0x20){
            nomQuint16[i] = '?';
        } else {
            nomQuint16[i] = nomptr[i];
        }
    }
    return nomQuint16;
}
