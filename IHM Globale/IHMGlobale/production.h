#ifndef PRODUCTION_H
#define PRODUCTION_H

#include "projet.h"

#include <QTimer>
#include <QEventLoop>

#define PRODUCTION_LOOP_DELAY 3000 //ms


class Production : public QObject
{
    Q_OBJECT

public:
    // Les différents états de la production
    enum Etat {
        ConditionInitial,
        ConditionProduction,
        ProductionEnCours,
        ProductionStoppe,
        ErreurProduction,
        ErreurCondition,
        PieceProduite,
        EnAttente,
    };


    Production(Projet *_projet);
    ~Production() {
        stopperBoucleProduction();
        delete timerBoucleProduction;
        delete loopCycle;
        delete loopConditionInitiale;
        delete loopConditionProduction;
    }

    // fonctions pour la boucle de production
    void lancerBoucleProduction();
    void stopperBoucleProduction();


    // fonctions de mise en conditions
    void lancerConditionInitiale();
    void lancerConditionProduction();
    void lancerCycle();

    // fonctions d'accesseurs
    int piecesProduites() {return pieces; }
    bool boucleProductionLancee() { return timerBoucleProduction != NULL && timerBoucleProduction->isActive(); }
    bool conditionInitialeEnCours() { return loopConditionInitiale != NULL && loopConditionInitiale->isRunning(); }
    bool conditionProductionEnCours() { return loopConditionProduction != NULL && loopConditionProduction->isRunning(); }
    bool cycleEnCours() { return loopCycle != NULL && loopCycle->isRunning(); }
    QString erreurProduction() { return erreur; }
    Production::Etat etatProduction() { return etat; }

signals:
    // Evènement pour savoir quand un cycle ce fini
    void etatChange();

protected:
    void conditionInitiale();
    void conditionProduction();
    void cycle();

    bool verifierStatutCondition(bool statut);
    bool verifierStatutCycle(bool statut);
    bool verifierStatuts();

private:
    Projet *projet;

    // nombre de piece produites
    int pieces = 0;
    // état de production
    Production::Etat etat = Production::Etat::EnAttente;
    // erreur
    QString erreur = "";
    // Arret demandé
    bool arretDemande = false;

    // boucle de production
    /* Les threads sont trop difficile d'utilisation et
     * quasiment non fonctionnel sur QT.
     * L'utilisation de QEventLoop et QTimer sera donc nessecaire
     * pour un fonctionnement synchrone mais non bloquant.
     */
    QTimer *timerBoucleProduction = new QTimer();
    QEventLoop *loopCycle = new QEventLoop(), *loopProduction = new QEventLoop(),
               *loopConditionInitiale = new QEventLoop(), *loopConditionProduction = new QEventLoop();

};

#endif // PRODUCTION_H
