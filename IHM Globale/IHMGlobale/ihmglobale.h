#ifndef IHMGLOBALE_H
#define IHMGLOBALE_H

#include <QMainWindow>
#include <QSettings>
#include <QUrl>
#include <QTimer>

#include "production.h"
#include "projet.h"


QT_BEGIN_NAMESPACE
namespace Ui { class IHMGlobale; }
QT_END_NAMESPACE

class IHMGlobale : public QMainWindow
{
    Q_OBJECT

public:
    IHMGlobale(QWidget *parent=nullptr);
    ~IHMGlobale();

public slots:
    /* Partie production */
    bool production_connexion();
    void production_lancer();
    void production_stopper();
    void production_lancerCycle();
    void production_conditionInitiale();
    void production_conditionProduction();
    bool production_verificationLancement();
    void production_setButtons(bool state);


    /* Partie Niryo */
    void niryo_connexionServeurNormal();
    void niryo_connexionServeurCustom();
    void niryo_stopperRobot();

    // Page Statistiques


    // Page Options
    void niryo_changerUnite();
    void niryo_changerVitesse();

    // Page Commandes
    void niryo_activerOutil();
    void niryo_desactiverOutil();
    void niryo_envoyerAxes();

    // Page Trajectoires
    void niryo_enregistrerNomTrajectoire();
    void niryo_lancerApprentissage();
    void niryo_enregistrerTrajectoire();
    void niryo_supprimerTrajectoire();
    void niryo_selectionnerTrajectoire(const QModelIndex &index);
    void niryo_actualiserTrajectoires();

    /* Partie Fanuc */
    void fanuc_connexion();
    void fanuc_selectionnerProgramme();
    void fanuc_envoyerDI();
    void fanuc_pauseRobot();

    /* Partie Convoyeur */
    void convoyeur_connexion();
    void convoyeur_lancerBoucleAuto();
    void convoyeur_resetErreurs();


    /* Partie Afficheur */
    void afficheur_connexion();
    void afficheur_envoyerTexte();
    void afficheur_enregistrerMessage();
    void afficheur_afficherMessage();
    void afficheur_listerMessages();

private:
    Ui::IHMGlobale *ui;

    Projet *projet;
    Production *production;

    // Evite de re-cliquer sur un bouton de Production quand
    // la connexion aux composants, est en cours
    bool enConnexion = false,
    // fanuc holding
         fanuc_resume = true,
    // Affichage en degrès ou radians
         niryo_degres = false,

    // Juste pour les sliders du niryo
         niryo_j1_pressed = false, niryo_j2_pressed = false,
         niryo_j3_pressed = false, niryo_j4_pressed = false,
         niryo_j5_pressed = false, niryo_j6_pressed = false;

};
#endif // IHMGLOBALE_H
