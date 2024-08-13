#ifndef TRAJECTOIRNIRYO_H
#define TRAJECTOIRNIRYO_H

#include <QString>
#include<QList>

class TrajectoireNiryo
{
public:
    TrajectoireNiryo();
    TrajectoireNiryo(int _ID,QString _nom,int _index);
    TrajectoireNiryo(int _ID,QList<quint16> _reponsenom,int _index);
    
    
    ~TrajectoireNiryo();

    void setTrajectoir(int _ID,QString _nom,int _index);

    int getID();
    QString getNom();
    QList<quint16> getNomQuint16();
    int getIndex();
    bool getExist();


    //conversion
    static QString quint16VersNom(QList<quint16> nomQuint16);
    static QList<quint16> nomVersQuint16(QString nom);

private:
    int ID;
    QString nom;
    int index;
    bool exist;
};

#endif // TRAJECTOIRNIRYO_H
