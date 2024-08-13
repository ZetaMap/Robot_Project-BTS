#ifndef PROJET_H
#define PROJET_H

#include <niryo.h>
#include <fanuc.h>
#include <convoyeur.h>
#include <afficheur.h>

#include <QSettings>


class Projet : public QObject
{
public:
    Projet() {
        niryo = new Niryo();
        fanuc = new Fanuc();
        convoyeur = new Convoyeur();
        afficheur = new Afficheur();
    }
    ~Projet() {
        delete niryo;
        delete fanuc;
        delete convoyeur;
        delete afficheur;
    }

    // Contient les instances de tout les composants et quelques paramètres

    // instance des composants
    Niryo *niryo;
    Fanuc *fanuc;
    Convoyeur *convoyeur;
    Afficheur *afficheur;

    // Objet pour stocker les paramètres dans un fichier de config
    QSettings settings = QSettings("config.ini", QSettings::Format::IniFormat);
};

#endif // PROJET_H
