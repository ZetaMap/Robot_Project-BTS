#include "production.h"


Production::Production(Projet *_projet) {
    projet = _projet;

    // Connecte une fonction pour stopper la boucle en cas d'erreur
    connect(this, &Production::etatChange, [this]() {
        if (etatProduction() == Production::Etat::ErreurProduction ||
            etatProduction() == Production::Etat::ErreurCondition)
            stopperBoucleProduction();
    });
    connect(timerBoucleProduction, &QTimer::timeout, this, &Production::lancerCycle);
}

void Production::lancerBoucleProduction() {
    if (boucleProductionLancee()) return;

    arretDemande = false;

    // Met en condition de production
    lancerConditionProduction();

    // Lance la boucle
    timerBoucleProduction->start(PRODUCTION_LOOP_DELAY);
    loopProduction->exec();
}

void Production::stopperBoucleProduction() {
    arretDemande = true;

    // Stoppe les composants
    projet->fanuc->stopRsr();
    projet->niryo->trajectory->stopTrajectory();
    projet->niryo->controller->stopMove();
    projet->convoyeur->stopperBoucleAuto();
    projet->convoyeur->arret();
    projet->convoyeur->eteindreVoyants();

    // Stoppe la boucle de production
    timerBoucleProduction->stop();
    if (timerBoucleProduction->isActive()) QThread::msleep(100);

    // Remet en condition initiale
    // Note : Pour des questions de sécurité, la remise en condition initiale sera manuelle
    //lancerConditionInitiale();

    // Stoppe les boucles
    loopConditionInitiale->quit();
    loopConditionProduction->quit();
    loopCycle->quit();
    loopProduction->quit();

    // Attend un peut, si les boucles sont toujours actives
    if (loopConditionInitiale->isRunning()) QThread::msleep(100);
    if (loopConditionProduction->isRunning()) QThread::msleep(100);
    if (loopCycle->isRunning()) QThread::msleep(100);
    if (loopProduction->isRunning()) QThread::msleep(100);

    etat = Production::Etat::EnAttente;
    emit etatChange();
}


void Production::lancerConditionInitiale() {
    // Ne lance pas si déjà lancé
    if (conditionInitialeEnCours()) return;
    arretDemande = false;

    // Delais de 100 ms avant lancement
    QTimer::singleShot(100, [this]() {
        conditionInitiale();
        loopConditionInitiale->quit();
    });

    loopConditionInitiale->exec();
}

void Production::lancerConditionProduction() {
    // Ne lance pas si déjà lancé
    if (conditionProductionEnCours()) return;
    arretDemande = false;

    // Delais de 100 ms avant lancement
    QTimer::singleShot(100, [this]() {
        conditionProduction();
        loopConditionProduction->quit();
    });

    loopConditionProduction->exec();
}

void Production::lancerCycle() {
    // Ne lance pas si déjà lancé
    if (cycleEnCours()) return;
    arretDemande = false;

    // Delais de 100 ms avant lancement
    QTimer::singleShot(100, [this]() {
        cycle();
        loopCycle->quit();
    });

    loopCycle->exec();
}


void Production::conditionInitiale() {
    erreur = "";
    etat = Production::Etat::ConditionInitial;
    emit etatChange();

    projet->convoyeur->lancerBoucleAuto();

    // Lance le programme de mise en condition initiale du fanuc
    projet->fanuc->initUop();
    QThread::msleep(1000);
    if (projet->fanuc->faultDetected()) {
        projet->fanuc->faultReset();
        QThread::msleep(2000);
    }
    if (verifierStatutCondition(projet->fanuc->stopRsr())) return;
    if (verifierStatutCondition(projet->fanuc->selectRsr(projet->settings.value("Fanuc.Programmes/Initiale").toInt()))) return;
    if (verifierStatutCondition(projet->fanuc->startRsr())) return;

    // Lance la position de par défaut du Niryo
    if (verifierStatutCondition(projet->niryo->trajectory->stopTrajectory())) return;
    projet->niryo->trajectory->listTrajectories();
    if (verifierStatutCondition(projet->niryo->trajectory->selectTrajectoryByID(projet->settings.value("Niryo.Trajectoires/Initiale").toInt()))) return;
    if (verifierStatutCondition(projet->niryo->trajectory->startTrajectory())) return;

    // Eteint la boucle de production, le convoyeur et les voyants
    projet->convoyeur->stopperBoucleAuto();
    if (verifierStatutCondition(projet->convoyeur->arret())) return;
    if (verifierStatutCondition(projet->convoyeur->eteindreVoyants())) return;

    etat = Production::Etat::EnAttente;
    emit etatChange();
}

void Production::conditionProduction() {
    // Met le status
    erreur = "";
    etat = Production::Etat::ConditionProduction;
    emit etatChange();

    // Lance le programme de production du fanuc
    projet->fanuc->initUop();
    QThread::msleep(1000);
    if (projet->fanuc->faultDetected()) {
        projet->fanuc->faultReset();
        QThread::msleep(2000);
    }
    if (verifierStatutCondition(projet->fanuc->stopRsr())) return;
    if (verifierStatutCondition(projet->fanuc->selectRsr(projet->settings.value("Fanuc.Programmes/Cycle").toInt()))) return;
    if (verifierStatutCondition(projet->fanuc->startRsr())) return;

    // Lance la position de production du Niryo
    if (verifierStatutCondition(projet->niryo->trajectory->stopTrajectory())) return;
    projet->niryo->trajectory->listTrajectories();
    if (verifierStatutCondition(projet->niryo->trajectory->selectTrajectoryByID(projet->settings.value("Niryo.Trajectoires/Production").toInt()))) return;
    QThread::msleep(100);
    if (verifierStatutCondition(projet->niryo->trajectory->startTrajectory())) return;

    // Test le convoyeur et lance la boucle de production
    projet->convoyeur->retirerErreurs();
    if (verifierStatutCondition(projet->convoyeur->voyantV())) return;
    QThread::msleep(1000);
    if (verifierStatutCondition(projet->convoyeur->eteindreVoyants())) return;
    if (verifierStatutCondition(projet->convoyeur->voyantR())) return;
    QThread::msleep(1000);
    if (verifierStatutCondition(projet->convoyeur->eteindreVoyants())) return;
    if (verifierStatutCondition(projet->convoyeur->marcheAvant())) return;
    QThread::msleep(2000);
    if (verifierStatutCondition(projet->convoyeur->arret())) return;

    // Attend les robots
    if (!projet->fanuc->waitForDO(projet->settings.value("Fanuc.Programmes/CycleDO2").toInt())) {
        erreur = "Fanuc DO waiting timed out. ";
        verifierStatutCondition(false);
        return;
    }
    if (!projet->niryo->trajectory->waitForTrajectoryFinished()) {
        erreur = "Niryo trajectory waiting timed out. ";
        verifierStatutCondition(false);
        return;
    }

    etat = Production::Etat::EnAttente;
    emit etatChange();
}

void Production::cycle() {
    // Met le status
    erreur = "";
    etat = Production::Etat::ProductionEnCours;
    emit etatChange();

    projet->convoyeur->eteindreVoyants();

    if (projet->fanuc->faultDetected()) {
        projet->fanuc->faultReset();
        QThread::msleep(2000);
    }
    if (!projet->fanuc->programExec()) {
        erreur = "Pas de programme Fanuc en cours. ";
        verifierStatutCycle(false);
        return;
    }

    if (verifierStatutCycle(projet->fanuc->triggerDI(projet->settings.value("Fanuc.Programmes/CycleDI").toInt()))) return;
    if (!projet->fanuc->waitForDO(projet->settings.value("Fanuc.Programmes/CycleDO1").toInt())) {
        erreur = "Fanuc DO waiting timed out. ";
        verifierStatutCycle(false);
        return;
    }

    // lance la boucle auto
    projet->convoyeur->lancerBoucleAuto();
    if (verifierStatutCycle(!projet->convoyeur->statutProduction())) {
        erreur = "Le Convoyeur n'a pas lancé la production. ";
        verifierStatutCycle(false);
        return;
    }
    // attend que le convoyeur ai fini son cycle
    bool erreurProduction = !projet->convoyeur->attendreProductionFini();
    projet->convoyeur->stopperBoucleAuto();
    if (erreurProduction) {
        erreur = "Délais d'attente de production, du Convoyeur, dépassé. ";
        verifierStatutCycle(false);
        return;
    }

    // Au tour de niryo
    if (verifierStatutCycle(projet->niryo->trajectory->selectTrajectoryByID(projet->settings.value("Niryo.Trajectoires/Cycle").toInt()))) return;
    QThread::msleep(100);
    if (projet->niryo->trajectory->startTrajectory(true)){
        erreur = "Niryo trajectory waiting timed out. ";
        verifierStatutCycle(false);
        return;
    }

    pieces++;
    etat = Production::Etat::PieceProduite;
    emit etatChange();
}


// renvoie true s'il y a un problème
bool Production::verifierStatutCondition(bool statut){
    if (arretDemande) {
        etat = Production::Etat::ProductionStoppe;
        emit etatChange();
        return true;
    }

    if (verifierStatuts() || !statut) {
        etat = Production::Etat::ErreurCondition;
        emit etatChange();
        return true;
    }

    return false;
}

// renvoie true s'il y a un problème
bool Production::verifierStatutCycle(bool statut) {
    if (arretDemande) {
        etat = Production::Etat::ProductionStoppe;
        emit etatChange();
        return true;
    }

    if (verifierStatuts() || !statut) {
        etat = Production::Etat::ErreurProduction;
        emit etatChange();
        return true;
    }

    return false;
}

// Renvoie true s'il y a un problème
bool Production::verifierStatuts() {
    return (!projet->niryo->axis->axisGetterRunning() || !projet->niryo->controller->resultGetterRunning() ||
            projet->niryo->controller->getCollisionDetected() || !projet->niryo->stats->statsGetterRunning() ||
            !projet->niryo->trajectory->resultGetterRunning() || projet->niryo->trajectory->getCollisionDetected() ||
            !projet->fanuc->sensorLoopRunning() || projet->fanuc->faultDetected() ||
            !projet->convoyeur->boucleCapteursLancee() /*|| projet->convoyeur->erreurProduction()*/);
}
