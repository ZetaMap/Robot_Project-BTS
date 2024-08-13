#include "ihmglobale.h"
#include "ui_ihmglobale.h"


IHMGlobale::IHMGlobale(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IHMGlobale)
{
    ui->setupUi(this);

    // Créer les objects des composants
    projet = new Projet();
    production = new Production(projet);


    /* Partie production */
    // Connecte une fonction pour écouter l'évènement de changement d'état de la production
    connect(production, &Production::etatChange, [this]() {
        // Affiche l'état de production
        ui->production_status->setText(
            production->etatProduction() == Production::Etat::ConditionProduction ? "Mise en place pour la production" :
            production->etatProduction() == Production::Etat::ConditionInitial ? "Remise en condition initiale" :
            production->etatProduction() == Production::Etat::ProductionEnCours ? "Cycle de production en cours" :
            production->etatProduction() == Production::Etat::ProductionStoppe ? "Cycle de production stoppé !" :
            production->etatProduction() == Production::Etat::ErreurProduction ? "!! Erreur de production !!" :
            production->etatProduction() == Production::Etat::ErreurCondition ? "!! Erreur de mise en place !!" :
            production->etatProduction() == Production::Etat::PieceProduite ? "Production pièce terminé" :
            production->etatProduction() == Production::Etat::EnAttente ? "En attente de commandes" :
            "<< Etat inconnue >>"
        );

        // Mise en évidance du texte en cas d'erreurs
        ui->production_status->setStyleSheet(
            production->etatProduction() == Production::Etat::ErreurProduction ||
            production->etatProduction() == Production::Etat::ErreurCondition
                ? "color:red;font:bold;" : "");

        // Affichage des pièces produites
        ui->production_produite->setValue(production->piecesProduites());

        // Vérifie les erreurs possibles
        QString erreurs = production->erreurProduction();
        //erreurs niryo
        if (projet->niryo->controller->getCollisionDetected() || projet->niryo->trajectory->getCollisionDetected())
            erreurs += "Niryo collision détecté. ";
        if (projet->fanuc->faultDetected()) erreurs += "Fault Fanuc détecté. ";
        if (!projet->fanuc->sensorLoopRunning()) erreurs += "Boucle lecture capteurs Fanuc non lancé. ";
        if (projet->convoyeur->erreurProduction()) erreurs += "Erreur de production Convoyeur. ";
        ui->production_erreur->setText(erreurs);

        // Affiche le bon message sur l'afficheur
        if (production->etatProduction() == Production::Etat::EnAttente)
            projet->afficheur->viderMesssage();
        else
            projet->afficheur->afficherTexte(
                production->etatProduction() == Production::Etat::ConditionProduction ? ui->afficheur_texte_mise_en_place->text() :
                production->etatProduction() == Production::Etat::ConditionInitial ? ui->afficheur_texte_mise_en_place->text() :
                production->etatProduction() == Production::Etat::ProductionEnCours ? ui->afficheur_texte_production_encours->text() :
                production->etatProduction() == Production::Etat::ProductionStoppe ? ui->afficheur_texte_production_stoppe->text() :
                production->etatProduction() == Production::Etat::ErreurProduction ? ui->afficheur_texte_erreur_production->text() :
                production->etatProduction() == Production::Etat::ErreurCondition ? ui->afficheur_texte_erreur_mise_en_place->text() :
                production->etatProduction() == Production::Etat::PieceProduite ? QString::number(production->piecesProduites()) + ui->afficheur_texte_piece_produites->text() :
                "<< Etat\ninconnue >>",
            ui->afficheur_texte_clignotant->checkState() == Qt::CheckState::Checked);
    });

    // Connecte les boutons
    connect(ui->production_lancer, &QPushButton::clicked, this, &IHMGlobale::production_lancer);
    connect(ui->production_stopper, &QPushButton::clicked, this, &IHMGlobale::production_stopper);
    connect(ui->production_condition_initiale, &QPushButton::clicked, this, &IHMGlobale::production_conditionInitiale);
    connect(ui->production_condition_production, &QPushButton::clicked, this, &IHMGlobale::production_conditionProduction);
    connect(ui->production_lancer_cycle, &QPushButton::clicked, this, &IHMGlobale::production_lancerCycle);



    /* Partie Niryo */
    // Connecte les erreurs de ModbusUtil, au widget de statut
    connect(projet->niryo->serveurNormal, &ModbusUtil::errorOccured, [this](QString error) {
        ui->niryo_status->setText("Normal: " + error);
    });
    connect(projet->niryo->serveurCustom, &ModbusUtil::errorOccured, [this](QString error) {
        ui->niryo_status->setText("Custom: " + error);
    });
    connect(ui->niryo_stopper_robot, &QPushButton::clicked, this, &IHMGlobale::niryo_stopperRobot);


    // Page Statistiques
    // Tableau de widget, pour simplifier l'affichage des statiqtiques
    QDoubleSpinBox* voltages[STATS_HARDWARES_NUMBER] = {
        ui->niryo_voltage_1, ui->niryo_voltage_2, ui->niryo_voltage_3, ui->niryo_voltage_4,
        ui->niryo_voltage_5, ui->niryo_voltage_6, ui->niryo_voltage_7, ui->niryo_voltage_8
    };
    QSpinBox* temps[STATS_HARDWARES_NUMBER] = {
        ui->niryo_temperature_1, ui->niryo_temperature_2, ui->niryo_temperature_3, ui->niryo_temperature_4,
        ui->niryo_temperature_5, ui->niryo_temperature_6, ui->niryo_temperature_7, ui->niryo_temperature_8
    };
    QSpinBox* moteurs[STATS_HARDWARES_NUMBER] = {
        ui->niryo_moteur_1, ui->niryo_moteur_2, ui->niryo_moteur_3, ui->niryo_moteur_4,
        ui->niryo_moteur_5, ui->niryo_moteur_6, ui->niryo_moteur_7, ui->niryo_moteur_8
    };

    // Connecte les events du Niryo, pour afficher les statuts
    connect(projet->niryo->stats, &NiryoStats::statsReaded, [this, temps, voltages, moteurs]() {
        ui->niryo_status_lecture_stats->setText(projet->niryo->stats->statsGetterReadError() ? "Erreur" : "OK");
        ui->niryo_moteurs->setText(projet->niryo->stats->getMotorsConnectionUp() ? "OK" : "Erreur");
        ui->niryo_calibration_status->setText(NiryoEnums::getCalibrationName(projet->niryo->stats->getCalibrationState()));
        ui->niryo_temperature_cpu->setValue(projet->niryo->stats->getRaspberryPiTemperature());
        ui->niryo_hwversion->setText(projet->niryo->stats->getNedRPiVersion());
        ui->niryo_outil->setText(NiryoEnums::getToolName(projet->niryo->stats->getToolType()));

        // Statistiques avancées
        for (int i=0; i<STATS_HARDWARES_NUMBER; i++) {
            voltages[i]->setValue(projet->niryo->stats->getHardwareVoltages()[i]);
            temps[i]->setValue(projet->niryo->stats->getHardwareTemperatures()[i]);
            moteurs[i]->setValue(projet->niryo->stats->getHardwareErrors()[i]);
        }
    });


    // Page Options
    // Charge les paramètres
    ui->niryo_host_s1->setText(projet->settings.value("Niryo/ServeurNormal", QVariant(ui->niryo_host_s1->text())).toString());
    ui->niryo_host_s2->setText(projet->settings.value("Niryo/ServeurCustom", QVariant(ui->niryo_host_s2->text())).toString());
    ui->niryo_trajectoire_initiale->setValue(projet->settings.value("Niryo.Trajectoires/Initiale", QVariant(ui->niryo_trajectoire_initiale->value())).toInt());
    ui->niryo_trajectoire_production->setValue(projet->settings.value("Niryo.Trajectoires/Production", QVariant(ui->niryo_trajectoire_production->value())).toInt());
    ui->niryo_trajectoire_cycle->setValue(projet->settings.value("Niryo.Trajectoires/Cycle", QVariant(ui->niryo_trajectoire_cycle->value())).toInt());

    // Connecte les boutons
    connect(ui->niryo_connexion_s1, &QPushButton::clicked, this, &IHMGlobale::niryo_connexionServeurNormal);
    connect(ui->niryo_connexion_s2, &QPushButton::clicked, this, &IHMGlobale::niryo_connexionServeurCustom);
    // Change le bouton de connexion en fonction de l'état de connexion
    connect(projet->niryo->serveurNormal, &ModbusUtil::stateChanged, [this](QModbusDevice::State state) {
        if (state == QModbusDevice::State::ConnectedState) {
            ui->niryo_host_s1->setEnabled(false);
            ui->niryo_connexion_s1->setText("Déconnecter");

            // Lance les boucles de lecture
            projet->niryo->axis->startAxisGetterLoop();
            projet->niryo->controller->startResultGetterLoop();
            projet->niryo->stats->startStatsGetterLoop();

        } else if (state == QModbusDevice::State::UnconnectedState) {
            // Stoppe les boucles de lecture
            projet->niryo->axis->stopAxisGetterLoop();
            projet->niryo->controller->stopResultGetterLoop();
            projet->niryo->stats->stopStatsGetterLoop();
            projet->niryo->trajectory->stopResultGetterLoop();

            ui->niryo_host_s1->setEnabled(true);
            ui->niryo_connexion_s1->setText("Connecter");
        }
    });
    connect(projet->niryo->serveurCustom, &ModbusUtil::stateChanged, [this](QModbusDevice::State state) {
        if (state == QModbusDevice::State::ConnectedState) {
            ui->niryo_host_s2->setEnabled(false);
            ui->niryo_connexion_s2->setText("Déconnecter");

            // Lance les boucles de lecture
            projet->niryo->trajectory->startResultGetterLoop();
            projet->niryo->trajectory->listTrajectories();

        } else if (state == QModbusDevice::State::UnconnectedState) {
            // Stoppe les boucles de lecture
            projet->niryo->trajectory->stopResultGetterLoop();

            ui->niryo_host_s2->setEnabled(true);
            ui->niryo_connexion_s2->setText("Connecter");
        }
    });

    connect(ui->niryo_unite, &QPushButton::clicked, this, &IHMGlobale::niryo_changerUnite);
    connect(ui->niryo_lancer_calibration, &QPushButton::clicked, projet->niryo->controller, &NiryoController::newCalibration);
    connect(ui->niryo_detecter_outil, &QPushButton::clicked, projet->niryo->controller, &NiryoController::updateTool);
    connect(ui->niryo_nettoyer_colisions, &QPushButton::clicked, projet->niryo->controller, &NiryoController::clearCollisionDetected);
    connect(ui->niryo_vitesse, &QSlider::sliderReleased, this, &IHMGlobale::niryo_changerVitesse);

    // Sauvegarde les praramètres des trajectoires pour la production
    connect(ui->niryo_trajectoire_initiale, &QSpinBox::editingFinished, [this]() {
        projet->settings.setValue("Niryo.Trajectoires/Initiale", QVariant(ui->niryo_trajectoire_initiale->value()));
    });
    connect(ui->niryo_trajectoire_production, &QSpinBox::editingFinished, [this]() {
        projet->settings.setValue("Niryo.Trajectoires/Production", QVariant(ui->niryo_trajectoire_production->value()));
    });
    connect(ui->niryo_trajectoire_cycle, &QSpinBox::editingFinished, [this]() {
        projet->settings.setValue("Niryo.Trajectoires/Cycle", QVariant(ui->niryo_trajectoire_cycle->value()));
    });


    // Page Commandes
    // Connecte les boutons
    connect(projet->niryo->controller, &NiryoController::resultReaded, [this]() {
        ui->niryo_status_lecture_commande->setText(projet->niryo->controller->resultGetterReadError() ? "Erreur lecture commande" : "Commande OK");
        ui->niryo_commande_resultat->setText(NiryoEnums::getCommandResultName(projet->niryo->controller->getLastCommandResult()));
        ui->niryo_commande_encours->setText(projet->niryo->controller->getCommandIsExecuting() ? "En cours" : "En attente");
        ui->niryo_colision->setText(projet->niryo->controller->getCollisionDetected() ? "Collision Détecté" : "OK");
        ui->niryo_colision->setStyleSheet(projet->niryo->controller->getCollisionDetected() ? "color:red;font:bold;" : "");
    });
    connect(ui->niryo_attraper, &QPushButton::clicked, this, &IHMGlobale::niryo_activerOutil);
    connect(ui->niryo_lacher, &QPushButton::clicked, this, &IHMGlobale::niryo_desactiverOutil);
    connect(ui->niryo_pose_repos, &QPushButton::clicked, projet->niryo->controller, &NiryoController::moveToStandBy);
    connect(ui->niryo_pose_zero, &QPushButton::clicked, projet->niryo->controller, &NiryoController::moveToZero);

    // Connecte les events du Niryo, pour afficher les statuts et les axes
    connect(projet->niryo->axis, &NiryoAxis::axisReaded, [this]() {
        ui->niryo_status_lecture_axes->setText(projet->niryo->axis->axisGetterReadError() ? "Erreur lecture Axes" : "Axes OK");
        if (!niryo_j1_pressed) {
            ui->niryo_J1_spin->setValue(projet->niryo->axis->getJ1Base(niryo_degres));
            ui->niryo_J1->setValue(projet->niryo->axis->getJ1Base(niryo_degres) * 1000.0);
        }
        if (!niryo_j2_pressed) {
            ui->niryo_J2_spin->setValue(projet->niryo->axis->getJ2Shoulder(niryo_degres));
            ui->niryo_J2->setValue(projet->niryo->axis->getJ2Shoulder(niryo_degres) * 1000.0);
        }
        if (!niryo_j3_pressed) {
            ui->niryo_J3_spin->setValue(projet->niryo->axis->getJ3Elbow(niryo_degres));
            ui->niryo_J3->setValue(projet->niryo->axis->getJ3Elbow(niryo_degres) * 1000.0);
        }
        if (!niryo_j4_pressed) {
            ui->niryo_J4_spin->setValue(projet->niryo->axis->getJ4ForeArm(niryo_degres));
            ui->niryo_J4->setValue(projet->niryo->axis->getJ4ForeArm(niryo_degres) * 1000.0);
        }
        if (!niryo_j5_pressed) {
            ui->niryo_J5_spin->setValue(projet->niryo->axis->getJ5Wrist(niryo_degres));
            ui->niryo_J5->setValue(projet->niryo->axis->getJ5Wrist(niryo_degres) * 1000.0);
        }
        if (!niryo_j6_pressed) {
            ui->niryo_J6_spin->setValue(projet->niryo->axis->getJ6Hand(niryo_degres));
            ui->niryo_J6->setValue(projet->niryo->axis->getJ6Hand(niryo_degres) * 1000.0);
        }
    });
    niryo_changerUnite(); // met l'unité de mesure en degrès

    // Pour faire joli et éviter que les sliders ne se replacent pendant que l'on le maintiens.
    connect(ui->niryo_J1, &QSlider::sliderReleased, this, &IHMGlobale::niryo_envoyerAxes);
    connect(ui->niryo_J1, &QSlider::sliderPressed, [this]() { niryo_j1_pressed = true; });
    connect(ui->niryo_J1, &QSlider::sliderReleased, [this]() { niryo_j1_pressed = false; });
    connect(ui->niryo_J2, &QSlider::sliderReleased, this, &IHMGlobale::niryo_envoyerAxes);
    connect(ui->niryo_J2, &QSlider::sliderPressed, [this]() { niryo_j2_pressed = true; });
    connect(ui->niryo_J2, &QSlider::sliderReleased, [this]() { niryo_j2_pressed = false; });
    connect(ui->niryo_J3, &QSlider::sliderReleased, this, &IHMGlobale::niryo_envoyerAxes);
    connect(ui->niryo_J3, &QSlider::sliderPressed, [this]() { niryo_j3_pressed = true; });
    connect(ui->niryo_J3, &QSlider::sliderReleased, [this]() { niryo_j3_pressed = false; });
    connect(ui->niryo_J4, &QSlider::sliderReleased, this, &IHMGlobale::niryo_envoyerAxes);
    connect(ui->niryo_J4, &QSlider::sliderPressed, [this]() { niryo_j4_pressed = true; });
    connect(ui->niryo_J4, &QSlider::sliderReleased, [this]() { niryo_j4_pressed = false; });
    connect(ui->niryo_J5, &QSlider::sliderReleased, this, &IHMGlobale::niryo_envoyerAxes);
    connect(ui->niryo_J5, &QSlider::sliderPressed, [this]() { niryo_j5_pressed = true; });
    connect(ui->niryo_J5, &QSlider::sliderReleased, [this]() { niryo_j5_pressed = false; });
    connect(ui->niryo_J6, &QSlider::sliderReleased, this, &IHMGlobale::niryo_envoyerAxes);
    connect(ui->niryo_J6, &QSlider::sliderPressed, [this]() { niryo_j6_pressed = true; });
    connect(ui->niryo_J6, &QSlider::sliderReleased, [this]() { niryo_j6_pressed = false; });


    // Page Trajectoires
    // Connecte les boutons
    connect(ui->niryo_trajectoire_lancer, &QPushButton::clicked, projet->niryo->trajectory, &NiryoTrajectory::startTrajectory);
    connect(ui->niryo_trajectoire_nom, &QLineEdit::editingFinished, this, &IHMGlobale::niryo_enregistrerNomTrajectoire);
    connect(ui->niryo_apprentissage_enregistrer, &QPushButton::clicked, this, &IHMGlobale::niryo_enregistrerTrajectoire);
    connect(ui->niryo_apprentissage_supprimer, &QPushButton::clicked, this, &IHMGlobale::niryo_supprimerTrajectoire);
    connect(ui->niryo_trajectoire_unselect, &QPushButton::clicked, projet->niryo->trajectory, &NiryoTrajectory::unselectTrajectory);
    connect(ui->niryo_apprentissage_lancer, &QPushButton::clicked, this, &IHMGlobale::niryo_lancerApprentissage);
    connect(ui->niryo_apprentissage_drappeau, &QPushButton::clicked, projet->niryo->trajectory, &NiryoTrajectory::addMoveFlag);
    connect(ui->niryo_trajectoires, &QListWidget::clicked, this, &IHMGlobale::niryo_selectionnerTrajectoire);
    connect(ui->niryo_trajectoire_actualiser, &QPushButton::clicked, this, &IHMGlobale::niryo_actualiserTrajectoires);

    // Connecte les events du Niryo, pour afficher les statuts
    connect(projet->niryo->trajectory, &NiryoTrajectory::resultReaded, [this]() {
        ui->niryo_status_lecture_trj->setText(projet->niryo->trajectory->resultGetterReadError() ? "Erreur" : "OK");
        ui->niryo_trajectoire_encours->setText(projet->niryo->trajectory->getTrajectoryIsExecuting() ? "En cours" : "En attente");
        ui->niryo_trajectoire_resultat->setText(NiryoEnums::getCommandResultName(projet->niryo->trajectory->getLastCommandResult()));
        ui->niryo_trajectoire_collisions->setText(projet->niryo->trajectory->getCollisionDetected() ? "Collision Détecté" : "OK");
        ui->niryo_trajectoire_collisions->setStyleSheet(projet->niryo->trajectory->getCollisionDetected() ? "color:red;font:bold;" : "");
        ui->niryo_apprentissage_lancer->setText(projet->niryo->trajectory->getLearningModeIsRunning() ? "Stopper" : "Lancer");
    });
    connect(projet->niryo->trajectory, &NiryoTrajectory::trajectorySelectChanged, [this]() {
        if (projet->niryo->trajectory->trajectoryIsSelected()) {
            NiryoTrajectory::TrajectoryData current = projet->niryo->trajectory->getSelectedTrajectory();
            if (current.isValid()) {
                ui->niryo_trajectoire_numero->setValue(current.getIndex());
                ui->niryo_trajectoire_id->setValue(current.getID());
                ui->niryo_trajectoire_nom->setText(current.getName());
                ui->niryo_trajectoire_nom->setEnabled(true);
            }

        } else {
            ui->niryo_trajectoire_numero->setValue(-1);
            ui->niryo_trajectoire_id->setValue(-1);
            ui->niryo_trajectoire_nom->clear();
            ui->niryo_trajectoire_nom->setEnabled(false);
        }
    });
    connect(projet->niryo->trajectory, &NiryoTrajectory::trajectoriesListed, [this](QList<NiryoTrajectory::TrajectoryData> list) {
        ui->niryo_trajectoires->clear();
        for (int i=0; i<list.length(); i++)
            ui->niryo_trajectoires->addItem(QString::number(list[i].getID()) + "-  " + list[i].getName());
    });



    /* Partie Fanuc */
    // Charge les paramètres
    ui->fanuc_host->setText(projet->settings.value("Fanuc/Serveur", QVariant(ui->fanuc_host->text())).toString());
    ui->fanuc_rsr_initiale->setValue(projet->settings.value("Fanuc.Programmes/Initiale", QVariant(ui->fanuc_rsr_initiale->value())).toInt());
    ui->fanuc_rsr_initiale_di->setValue(projet->settings.value("Fanuc.Programmes/InitialeDI", QVariant(ui->fanuc_rsr_initiale_di->value())).toInt());
    ui->fanuc_rsr_initiale_do->setValue(projet->settings.value("Fanuc.Programmes/InitialeDO", QVariant(ui->fanuc_rsr_initiale_do->value())).toInt());
    ui->fanuc_rsr_cycle->setValue(projet->settings.value("Fanuc.Programmes/Cycle", QVariant(ui->fanuc_rsr_cycle->value())).toInt());
    ui->fanuc_rsr_select_spin->setValue(ui->fanuc_rsr_cycle->value());
    ui->fanuc_rsr_cycle_di->setValue(projet->settings.value("Fanuc.Programmes/CycleDI", QVariant(ui->fanuc_rsr_cycle_di->value())).toInt());
    ui->fanuc_di_select->setValue(ui->fanuc_rsr_cycle_di->value());
    ui->fanuc_rsr_cycle_do->setValue(projet->settings.value("Fanuc.Programmes/CycleDO1", QVariant(ui->fanuc_rsr_cycle_do->value())).toInt());
    ui->fanuc_rsr_cycle_do2->setValue(projet->settings.value("Fanuc.Programmes/CycleDO2", QVariant(ui->fanuc_rsr_cycle_do2->value())).toInt());


    // Connecte les boutons
    connect(ui->fanuc_connexion, &QPushButton::clicked, this, &IHMGlobale::fanuc_connexion);
    // Change le bouton de connexion en fonction de l'état de connexion
    connect(projet->fanuc->modbusClient, &ModbusUtil::stateChanged, [this](QModbusTcpClient::State state) {
        if (state == QModbusDevice::State::ConnectedState) {
            ui->fanuc_host->setEnabled(false);
            ui->fanuc_connexion->setText("Déconnexion");

            // Lance les boucles de lecture
            projet->fanuc->startSensorLoop();

        } else if (state == QModbusDevice::State::UnconnectedState) {
            // Stoppe les boucles de lecture
            projet->fanuc->stopSensorLoop();

            ui->fanuc_host->setEnabled(true);
            ui->fanuc_connexion->setText("Connexion");
        }
    });
    connect(ui->fanuc_uop_init, &QPushButton::clicked, projet->fanuc, &Fanuc::initUop);
    connect(ui->fanuc_fault_reset, &QPushButton::clicked, projet->fanuc, &Fanuc::faultReset);
    connect(ui->fanuc_rsr_select, &QPushButton::clicked, this, &IHMGlobale::fanuc_selectionnerProgramme);
    connect(ui->fanuc_rsr_start, &QPushButton::clicked, projet->fanuc, &Fanuc::startRsr);
    connect(ui->fanuc_di_envoyer, &QPushButton::clicked, this, &IHMGlobale::fanuc_envoyerDI);
    connect(ui->fanuc_pause, &QPushButton::clicked, this, &IHMGlobale::fanuc_pauseRobot);
    connect(ui->fanuc_stopper_robot, &QPushButton::clicked, projet->fanuc, &Fanuc::stopRsr);

    // Connecte les events du Fanuc, pour afficher les statuts
    connect(projet->fanuc, &Fanuc::sensorReaded, [this]() {
        ui->fanuc_erreurs->setStyleSheet(projet->fanuc->faultDetected() ? "color:red;font:bold;" : "");
        ui->fanuc_erreurs->setText(projet->fanuc->faultDetected() ? "Fault Detecté" : "Status OK" );
        ui->fanuc_erreurs_capteurs->setText(projet->fanuc->sensorReadError() ? "Erreur Lecture" : "Lecture OK");
        ui->fanuc_condition_rsr->setText(projet->fanuc->rsrStateOK() ? "OK" : "No");
        ui->fanuc_programme_exec->setText(projet->fanuc->programExec() ? "Yes" : "No");
    });

    // Sauvegarde les praramètres des trajectoires pour la production
    connect(ui->fanuc_rsr_initiale, &QSpinBox::editingFinished, [this]() {
        projet->settings.setValue("Fanuc.Programmes/Initiale", QVariant(ui->fanuc_rsr_initiale->value()));
    });
    connect(ui->fanuc_rsr_initiale_di, &QSpinBox::editingFinished, [this]() {
        projet->settings.setValue("Fanuc.Programmes/InitialeDI", QVariant(ui->fanuc_rsr_initiale_di->value()));
    });
    connect(ui->fanuc_rsr_initiale_do, &QSpinBox::editingFinished, [this]() {
        projet->settings.setValue("Fanuc.Programmes/InitialeDO", QVariant(ui->fanuc_rsr_initiale_do->value()));
    });
    connect(ui->fanuc_rsr_cycle, &QSpinBox::editingFinished, [this]() {
        projet->settings.setValue("Fanuc.Programmes/Cycle", QVariant(ui->fanuc_rsr_cycle->value()));
    });
    connect(ui->fanuc_rsr_cycle_di, &QSpinBox::editingFinished, [this]() {
        projet->settings.setValue("Fanuc.Programmes/CycleDI", QVariant(ui->fanuc_rsr_cycle_di->value()));
    });
    connect(ui->fanuc_rsr_cycle_do, &QSpinBox::editingFinished, [this]() {
        projet->settings.setValue("Fanuc.Programmes/CycleDO1", QVariant(ui->fanuc_rsr_cycle_do->value()));
    });
    connect(ui->fanuc_rsr_cycle_do2, &QSpinBox::editingFinished, [this]() {
        projet->settings.setValue("Fanuc.Programmes/CycleDO2", QVariant(ui->fanuc_rsr_cycle_do2->value()));
    });

    // Connecte les erreurs de ModbusUtil, au widget de statut
    connect(projet->fanuc->modbusClient, &ModbusUtil::errorOccured, [this](QString error) {
        ui->fanuc_status->setText(error);
    });



    /* Partie Convoyeur */
    // Charge les paramètres
    ui->convoyeur_host->setText(projet->settings.value("Convoyeur/Serveur", QVariant(ui->convoyeur_host->text())).toString());

    // Connecte les boutons
    connect(ui->convoyeur_connexion, &QPushButton::clicked, this, &IHMGlobale::convoyeur_connexion);
    // Change le bouton de connexion en fonction de l'état de connexion
    connect(projet->convoyeur->modbusClient, &ModbusUtil::stateChanged, [this](QModbusDevice::State state) {
        if (state == QModbusDevice::State::ConnectedState) {
            ui->convoyeur_host->setEnabled(false);
            ui->convoyeur_connexion->setText("Déconnexion");

            // Lance les boucles de lecture
            projet->convoyeur->lancerBoucleCapteurs();

        } else if (state == QModbusDevice::State::UnconnectedState) {
            // Stoppe les boucles de lecture
            projet->convoyeur->stopperBoucleCapteurs();

            ui->convoyeur_host->setEnabled(true);
            ui->convoyeur_connexion->setText("Connexion");
        }
    });
    connect(ui->convoyeur_marche, &QPushButton::clicked, projet->convoyeur, &Convoyeur::marche);
    connect(ui->convoyeur_arret, &QPushButton::clicked, projet->convoyeur, &Convoyeur::arret);
    connect(ui->convoyeur_avant, &QPushButton::clicked, projet->convoyeur, &Convoyeur::marcheAvant);
    connect(ui->convoyeur_arriere, &QPushButton::clicked, projet->convoyeur, &Convoyeur::marcheArriere);
    connect(ui->convoyeur_voyant_vert, &QPushButton::clicked, projet->convoyeur, &Convoyeur::voyantV);
    connect(ui->convoyeur_voyant_rouge, &QPushButton::clicked, projet->convoyeur, &Convoyeur::voyantR);
    connect(ui->convoyeur_voyant_eteindre, &QPushButton::clicked, projet->convoyeur, &Convoyeur::eteindreVoyants);
    connect(ui->convoyeur_lancer_auto, &QPushButton::clicked, this, &IHMGlobale::convoyeur_lancerBoucleAuto);
    connect(ui->convoyeur_reset_erreurs, &QPushButton::clicked, this, &IHMGlobale::convoyeur_resetErreurs);

    // Connecte les erreurs de ModbusUtil, au widget de statut
    connect(projet->convoyeur->modbusClient, &ModbusUtil::errorOccured, [this](QString error) {
        ui->convoyeur_status->setText(error);
    });
    // Connecte les events de Convoyeur, pour afficher les statuts
    connect(projet->convoyeur, &Convoyeur::capteursLus, [this]() {
        ui->convoyeur_status_entree->setText(projet->convoyeur->capteurEntree() ? "ON" : "OFF");
        ui->convoyeur_status_sortie->setText(projet->convoyeur->capteurSortie() ? "ON" : "OFF");
        ui->convoyeur_erreur_lecture->setText(projet->convoyeur->erreurProduction() ? "Erreur Capteurs" : "Capteurs OK");
    });
    connect(projet->convoyeur, &Convoyeur::boucleAutoLoop, [this]() {
        ui->convoyeur_erreur_production->setText(projet->convoyeur->erreurProduction() ? "Erreur Production" : "Production OK");
        ui->convoyeur_erreur_production->setStyleSheet(projet->convoyeur->erreurProduction() ? "color:red;font:bold;" : "");
        ui->convoyeur_status_production->setText(projet->convoyeur->statutProduction() ? "Terminé" : "En cours");
    });
    connect(projet->convoyeur, &Convoyeur::boucleAutoStatut, [this]() {
        ui->convoyeur_lancer_auto->setText(projet->convoyeur->boucleAutoLancee() ? "Stopper" : "Lancer");
    });



    /* Partie Afficheur */
    // Charge les paramètres
    ui->afficheur_host->setText(projet->settings.value("Afficheur/Serveur", QVariant(ui->afficheur_host->text())).toString());
    ui->afficheur_texte_erreur_production->setText(projet->settings.value("Afficheur.Messages/ErreurProduction", QVariant(ui->afficheur_texte_erreur_production->text())).toString());
    ui->afficheur_texte_piece_produites->setText(projet->settings.value("Afficheur.Messages/NPieces", QVariant(ui->afficheur_texte_piece_produites->text())).toString());
    ui->afficheur_texte_production_encours->setText(projet->settings.value("Afficheur.Messages/Production", QVariant(ui->afficheur_texte_production_encours->text())).toString());
    ui->afficheur_texte_production_stoppe->setText(projet->settings.value("Afficheur.Messages/Stoppe", QVariant(ui->afficheur_texte_production_stoppe->text())).toString());
    ui->afficheur_texte_mise_en_place->setText(projet->settings.value("Afficheur.Messages/MiseEnPlace", QVariant(ui->afficheur_texte_mise_en_place->text())).toString());
    ui->afficheur_texte_erreur_mise_en_place->setText(projet->settings.value("Afficheur.Messages/ErreurMiseEnPlace", QVariant(ui->afficheur_texte_erreur_mise_en_place->text())).toString());

    // Connecte les boutons
    connect(ui->afficheur_connexion, &QPushButton::clicked, this, &IHMGlobale::afficheur_connexion);
    // Change le bouton de connexion en fonction de l'état de connexion
    connect(projet->afficheur->modbusClient, &ModbusUtil::stateChanged, [this](QModbusDevice::State state) {
        if (state == QModbusDevice::State::ConnectedState) {
            ui->afficheur_host->setEnabled(false);
            ui->afficheur_connexion->setText("Déconnexion");
        } else if (state == QModbusDevice::State::UnconnectedState) {
            ui->afficheur_host->setEnabled(true);
            ui->afficheur_connexion->setText("Connexion");
        }
    });
    connect(ui->afficheur_envoyer_texte, &QPushButton::clicked, this, &IHMGlobale::afficheur_envoyerTexte);
    connect(ui->afficheur_vider_texte, &QPushButton::clicked, projet->afficheur, &Afficheur::viderMesssage);
    connect(ui->afficheur_afficher_message, &QPushButton::clicked, this, &IHMGlobale::afficheur_afficherMessage);
    connect(ui->afficheur_refresh, &QPushButton::clicked, this, &IHMGlobale::afficheur_listerMessages);

    // Sauvegarde les praramètres des textes de production
    connect(ui->afficheur_texte_erreur_production, &QLineEdit::editingFinished, [this]() {
        projet->settings.setValue("Afficheur.Messages/ErreurProduction", QVariant(ui->afficheur_texte_erreur_production->text()));
    });
    connect(ui->afficheur_texte_piece_produites, &QLineEdit::editingFinished, [this]() {
        projet->settings.setValue("Afficheur.Messages/NPieces", QVariant(ui->afficheur_texte_piece_produites->text()));
    });
    connect(ui->afficheur_texte_production_encours, &QLineEdit::editingFinished, [this]() {
        projet->settings.setValue("Afficheur.Messages/Production", QVariant(ui->afficheur_texte_production_encours->text()));
    });
    connect(ui->afficheur_texte_production_stoppe, &QLineEdit::editingFinished, [this]() {
        projet->settings.setValue("Afficheur.Messages/Stoppe", QVariant(ui->afficheur_texte_production_stoppe->text()));
    });
    connect(ui->afficheur_texte_mise_en_place, &QLineEdit::editingFinished, [this]() {
        projet->settings.setValue("Afficheur.Messages/MiseEnPlace", QVariant(ui->afficheur_texte_mise_en_place->text()));
    });
    connect(ui->afficheur_texte_erreur_mise_en_place, &QLineEdit::editingFinished, [this]() {
        projet->settings.setValue("Afficheur.Messages/ErreurMiseEnPlace", QVariant(ui->afficheur_texte_erreur_mise_en_place->text()));
    });

    // Connecte les erreurs de ModbusUtil, au widget de statut
    connect(projet->afficheur->modbusClient, &ModbusUtil::errorOccured, [this](QString error) {
        ui->afficheur_status->setText(error);
    });
}

IHMGlobale::~IHMGlobale() {
    delete production;
    delete projet;
    delete ui;
}



/* Partie production */
bool IHMGlobale::production_connexion() {
    enConnexion = true;
    bool erreur = false;
    ui->production_stopper->setEnabled(false);

    // Connecte tout les composants avant de lancer un cycle
    if (!erreur && !projet->niryo->serveurNormal->isConnected()) ui->niryo_connexion_s1->click();
    if (!erreur && !projet->niryo->serveurNormal->isConnected()) {
        ui->production_erreur->setText("Niryo : Impossible de ce connecter au serveur Normal");
        erreur = true;
    }
    if (!erreur && !projet->niryo->serveurCustom->isConnected()) ui->niryo_connexion_s2->click();
    if (!erreur && !projet->niryo->serveurCustom->isConnected()) {
        ui->production_erreur->setText("Niryo : Impossible de ce connecter au serveur Custom");
        erreur = true;
    }

    if (!erreur && !projet->fanuc->isConnected()) ui->fanuc_connexion->click();
    if (!erreur && !projet->fanuc->isConnected()) {
        ui->production_erreur->setText("Fanuc : Impossible de ce connecter");
        erreur = true;
    }
    if (!erreur && !projet->convoyeur->estConnecte()) ui->convoyeur_connexion->click();
    if (!erreur && !projet->fanuc->isConnected()) {
        ui->production_erreur->setText("Convoyeur : Impossible de ce connecter");
        erreur = true;
    }
    if (!erreur && !projet->afficheur->estConnecte()) ui->afficheur_connexion->click();
    if (!erreur && !projet->fanuc->isConnected()) {
        ui->production_erreur->setText("Afficheur : Impossible de ce connecter");
        erreur = true;
    }

    ui->production_stopper->setEnabled(true);
    enConnexion = false;
    return !erreur;
}

void IHMGlobale::production_lancer() {
    // Evite plusieurs lancement de la boucle
    if (production->boucleProductionLancee()) {
        ui->production_erreur->setText("");
        ui->production_status->setText("Boucle de production déjà lancée.");
        return;
    }

    // Empêche l'appuis du bouton pendant la connexion aux composants
    production_setButtons(false);

    // Connecte tout les composants
    bool erreurConnexion = !production_connexion();

    if (erreurConnexion) {
        production_setButtons(true);
        return;
    }

    // Lance la boucle de production
    production->lancerBoucleProduction();
}

void IHMGlobale::production_stopper() {
    // Empêche l'appuis du bouton pendant la connexion aux composants
    ui->production_stopper->setEnabled(false);
    production_setButtons(false);

    // Stoppe la boucle de production
    production->stopperBoucleProduction();

    // Et déconnecte tout les composants
    projet->niryo->disconnectAll();
    projet->fanuc->disconnectDevice();
    projet->convoyeur->deconnexion();
    projet->afficheur->deconnexion();

    ui->production_stopper->setEnabled(true);
    production_setButtons(true);
}

void IHMGlobale::production_lancerCycle() {
    production_setButtons(false);
    if (production_verificationLancement()) production->lancerCycle();
    production_setButtons(true);
}

void IHMGlobale::production_conditionInitiale() {
    production_setButtons(false);
    if (production_verificationLancement()) production->lancerConditionInitiale();
    production_setButtons(true);
}

void IHMGlobale::production_conditionProduction() {
    production_setButtons(false);
    if (production_verificationLancement()) production->lancerConditionProduction();
    production_setButtons(true);
}

bool IHMGlobale::production_verificationLancement() {
    if (enConnexion) return false;

    // N'autorise pas l'opération si la boucle de production est en cours
    if (production->boucleProductionLancee()) {
        ui->production_erreur->setText("");
        ui->production_status->setText("Boucle de production lancée. Opération non autorisé !");
        return false;
    }

    // Connecte les composants si ce n'est pas le cas
    return production_connexion();
}

void IHMGlobale::production_setButtons(bool state) {
    ui->production_lancer->setEnabled(state);
    ui->production_condition_initiale->setEnabled(state);
    ui->production_condition_production->setEnabled(state);
    ui->production_lancer_cycle->setEnabled(state);
}



/* Partie Niryo */
void IHMGlobale::niryo_stopperRobot() {
    if (projet->niryo->trajectory->getTrajectoryIsExecuting())
         projet->niryo->trajectory->stopTrajectory();
    else projet->niryo->controller->stopMove();
}


// Page Statistiques


// Page Options
void IHMGlobale::niryo_connexionServeurNormal() {
    if (!projet->niryo->serveurNormal->isConnected()) {
        // Vérification de l'ip et du port
        QString host = ui->niryo_host_s1->text();

        if (host.isEmpty()) {
            ui->niryo_status->setText("Serveur 1 : Pas d'adresse et de port");
            return;
        }

        QUrl url = QUrl::fromUserInput(host);
        QString ip = url.host();
        if (ip.isEmpty()) ip = "localhost";
        int port = url.port(5020);

        // Sauvegarde l'ip dans les paramètres
        projet->settings.setValue("Niryo/ServeurNormal", ip + ':' + QString::number(port));

        // Connection au serveur, Normal/par défaut, niryo
        ui->niryo_host_s1->setText(ip + ':' + QString::number(port));
        projet->niryo->connectServeurNormal(ip, port);

    } else projet->niryo->serveurNormal->disconnectDevice();
}

void IHMGlobale::niryo_connexionServeurCustom() {
    if (!projet->niryo->serveurCustom->isConnected()) {
        // Vérification de l'ip et du port
        QString host = ui->niryo_host_s2->text();

        if (host.isEmpty()) {
            ui->niryo_status->setText("Serveur 2 : Pas d'adresse et de port");
            return;
        }

        QUrl url = QUrl::fromUserInput(host);
        QString ip = url.host();
        if (ip.isEmpty()) ip = "localhost";
        int port = url.port(5022);

        // Sauvegarde l'ip dans les paramètres
        projet->settings.setValue("Niryo/ServeurCustom", ip + ':' + QString::number(port));

        // Connection au serveur, ajouté pour le projet, du niryo
        ui->niryo_host_s2->setText(ip + ':' + QString::number(port));
        projet->niryo->connectServeurCustom(ip, port);

    } else projet->niryo->serveurCustom->disconnectDevice();
}

void IHMGlobale::niryo_changerUnite() {
    niryo_degres = !niryo_degres;

    if (niryo_degres) {
        ui->niryo_unite->setText("Degrès");
        ui->niryo_J1->setRange(qRadiansToDegrees(projet->niryo->axis->j1BaseRange[0])*1000.0, qRadiansToDegrees(projet->niryo->axis->j1BaseRange[1])*1000.0);
        ui->niryo_J2->setRange(qRadiansToDegrees(projet->niryo->axis->j2ShoulderRange[0])*1000.0, qRadiansToDegrees(projet->niryo->axis->j2ShoulderRange[1])*1000.0);
        ui->niryo_J3->setRange(qRadiansToDegrees(projet->niryo->axis->j3ElbowRange[0]*1000.0), qRadiansToDegrees(projet->niryo->axis->j3ElbowRange[1])*1000.0);
        ui->niryo_J4->setRange(qRadiansToDegrees(projet->niryo->axis->j4ForeArmRange[0])*1000.0, qRadiansToDegrees(projet->niryo->axis->j4ForeArmRange[1])*1000.0);
        ui->niryo_J5->setRange(qRadiansToDegrees(projet->niryo->axis->j5WristRange[0])*1000.0, qRadiansToDegrees(projet->niryo->axis->j5WristRange[1])*1000.0);
        ui->niryo_J6->setRange(qRadiansToDegrees(projet->niryo->axis->j6HandRange[0])*1000.0, qRadiansToDegrees(projet->niryo->axis->j6HandRange[1])*1000.0);
        ui->niryo_J1_spin->setDecimals(2);
        ui->niryo_J2_spin->setDecimals(2);
        ui->niryo_J3_spin->setDecimals(2);
        ui->niryo_J4_spin->setDecimals(2);
        ui->niryo_J5_spin->setDecimals(2);
        ui->niryo_J6_spin->setDecimals(2);

    } else {
        ui->niryo_unite->setText("Radians");
        ui->niryo_J1->setRange(projet->niryo->axis->j1BaseRange[0]*1000.0, projet->niryo->axis->j1BaseRange[1]*1000.0);
        ui->niryo_J2->setRange(projet->niryo->axis->j2ShoulderRange[0]*1000.0, projet->niryo->axis->j2ShoulderRange[1]*1000.0);
        ui->niryo_J3->setRange(projet->niryo->axis->j3ElbowRange[0]*1000.0, projet->niryo->axis->j3ElbowRange[1]*1000.0);
        ui->niryo_J4->setRange(projet->niryo->axis->j4ForeArmRange[0]*1000.0, projet->niryo->axis->j4ForeArmRange[1]*1000.0);
        ui->niryo_J5->setRange(projet->niryo->axis->j5WristRange[0]*1000.0, projet->niryo->axis->j5WristRange[1]*1000.0);
        ui->niryo_J6->setRange(projet->niryo->axis->j6HandRange[0]*1000.0, projet->niryo->axis->j6HandRange[1]*1000.0);
        ui->niryo_J1_spin->setDecimals(4);
        ui->niryo_J2_spin->setDecimals(4);
        ui->niryo_J3_spin->setDecimals(4);
        ui->niryo_J4_spin->setDecimals(4);
        ui->niryo_J5_spin->setDecimals(4);
        ui->niryo_J6_spin->setDecimals(4);
    }
}

void IHMGlobale::niryo_changerVitesse() {
    if (projet->niryo->trajectory->getLearningModeIsRunning())
         projet->niryo->trajectory->setMotorSpeed(ui->niryo_vitesse->value());
    else projet->niryo->controller->setMotorSpeed(ui->niryo_vitesse->value());
}


// Page Commandes
void IHMGlobale::niryo_activerOutil() {
    if (projet->niryo->trajectory->getLearningModeIsRunning())
        projet->niryo->trajectory->setTool(true);
    else projet->niryo->controller->setTool(true);
}

void IHMGlobale::niryo_desactiverOutil() {
    if (projet->niryo->trajectory->getLearningModeIsRunning())
        projet->niryo->trajectory->setTool(false);
    else projet->niryo->controller->setTool(false);
}

void IHMGlobale::niryo_envoyerAxes() {
    if (niryo_degres)
         projet->niryo->controller->moveTo(
            qDegreesToRadians(ui->niryo_J1->value() / 1000.0), qDegreesToRadians(ui->niryo_J2->value() / 1000.0),
            qDegreesToRadians(ui->niryo_J3->value() / 1000.0), qDegreesToRadians(ui->niryo_J4->value() / 1000.0),
            qDegreesToRadians(ui->niryo_J5->value() / 1000.0), qDegreesToRadians(ui->niryo_J6->value() / 1000.0));

    else projet->niryo->controller->moveTo(
            ui->niryo_J1->value() / 1000.0, ui->niryo_J2->value() / 1000.0, ui->niryo_J3->value() / 1000.0,
             ui->niryo_J4->value() / 1000.0, ui->niryo_J5->value() / 1000.0, ui->niryo_J6->value() / 1000.0);
}



// Page Trajectoires
void IHMGlobale::niryo_enregistrerNomTrajectoire() {
    projet->niryo->trajectory->setSelectedTrajectoryName(ui->niryo_trajectoire_nom->text());
}

void IHMGlobale::niryo_lancerApprentissage() {
    if (projet->niryo->trajectory->getLearningModeIsRunning())
         projet->niryo->trajectory->setLearningMode(false);
    else projet->niryo->trajectory->setLearningMode(true);
}

void IHMGlobale::niryo_enregistrerTrajectoire() {
    projet->niryo->trajectory->saveSelectedTrajectory();
    ui->niryo_trajectoire_actualiser->click();
}

void IHMGlobale::niryo_supprimerTrajectoire() {
    projet->niryo->trajectory->deleteSelectedTrajectory();
    ui->niryo_trajectoire_actualiser->click();
}

void IHMGlobale::niryo_selectionnerTrajectoire(const QModelIndex &index) {
    projet->niryo->trajectory->selectTrajectory(index.row());
}

void IHMGlobale::niryo_actualiserTrajectoires() {
    ui->niryo_trajectoire_actualiser->setEnabled(false);
    projet->niryo->trajectory->listTrajectories();
    ui->niryo_trajectoire_actualiser->setEnabled(true);
}


/* Partie Fanuc */
void IHMGlobale::fanuc_connexion() {
    if (!projet->fanuc->isConnected()) {
        // Vérification de l'ip et du port
        QString host = ui->fanuc_host->text();

        if (host.isEmpty()) {
            ui->fanuc_status->setText("Pas d'adresse et de port");
            return;
        }

        QUrl url = QUrl::fromUserInput(host);
        QString ip = url.host();
        if (ip.isEmpty()) ip = "localhost";
        int port = url.port(502);

        // Sauvegarde l'ip dans les paramètres
        projet->settings.setValue("Fanuc/Serveur", ip + ':' + QString::number(port));

        // Connection au fanuc
        ui->fanuc_host->setText(ip + ':' + QString::number(port));
        projet->fanuc->connectDevice(ip, port);

    } else projet->fanuc->disconnectDevice();
}

void IHMGlobale::fanuc_selectionnerProgramme() {
    projet->fanuc->selectRsr(ui->fanuc_rsr_select_spin->value());
}

void IHMGlobale::fanuc_envoyerDI() {
    projet->fanuc->triggerDI(ui->fanuc_di_select->value());
}

void IHMGlobale::fanuc_pauseRobot() {
    if (!projet->fanuc->isConnected()) return;
    fanuc_resume = !fanuc_resume;
    projet->fanuc->holdRsr(fanuc_resume);
    if (fanuc_resume) projet->fanuc->startRsr();
    ui->fanuc_pause->setText(fanuc_resume ? "Pause" : "Resume");
}



/* Partie Convoyeur */
void IHMGlobale::convoyeur_connexion() {
    if (!projet->convoyeur->estConnecte()) {
        // Vérification de l'ip et du port
        QString host = ui->convoyeur_host->text();

        if (host.isEmpty()) {
            ui->convoyeur_status->setText("Pas d'adresse et de port");
            return;
        }

        QUrl url = QUrl::fromUserInput(host);
        QString ip = url.host();
        if (ip.isEmpty()) ip = "localhost";
        int port = url.port(502);

        // Sauvegarde l'ip dans les paramètres
        projet->settings.setValue("Convoyeur/Serveur", ip + ':' + QString::number(port));

        // Connection au convoyeur
        ui->convoyeur_host->setText(ip + ':' + QString::number(port));
        projet->convoyeur->connexion(ip, port);

    } else projet->convoyeur->deconnexion();
}

void IHMGlobale::convoyeur_lancerBoucleAuto() {
    ui->convoyeur_lancer_auto->setEnabled(false);

    if (projet->convoyeur->boucleAutoLancee())
         projet->convoyeur->stopperBoucleAuto();
    else projet->convoyeur->lancerBoucleAuto();

    ui->convoyeur_lancer_auto->setEnabled(true);
}

void IHMGlobale::convoyeur_resetErreurs() {
    projet->convoyeur->retirerErreurs();
    projet->convoyeur->eteindreVoyants();
}



/* Partie Afficheur */
void IHMGlobale::afficheur_connexion() {
    if (!projet->afficheur->estConnecte()) {
        // Vérification de l'ip et du port
        QString host = ui->afficheur_host->text();

        if (host.isEmpty()) {
            ui->afficheur_status->setText("Pas d'adresse et de port");
            return;
        }

        QUrl url = QUrl::fromUserInput(host);
        QString ip = url.host();
        if (ip.isEmpty()) ip = "localhost";
        int port = url.port(502);

        // Sauvegarde l'ip dans les paramètres
        projet->settings.setValue("Afficheur/Serveur", ip + ':' + QString::number(port));

        // Connection au afficheur
        ui->afficheur_host->setText(ip + ':' + QString::number(port));
        projet->afficheur->connexion(ip, port);

    } else projet->afficheur->deconnexion();
}

void IHMGlobale::afficheur_envoyerTexte() {
    QString texte = ui->afficheur_texte->text();

    if (texte.isEmpty()) {
        ui->afficheur_status->setText("Pas de texte spécifié");
        return;
    }

    projet->afficheur->afficherTexte(texte,
        ui->afficheur_texte_clignotant->checkState() == Qt::CheckState::Checked);
}

void IHMGlobale::afficheur_enregistrerMessage() {
    QString texte = ui->afficheur_texte->text();

    if (texte.isEmpty()) {
        ui->afficheur_status->setText("Pas de texte spécifié");
        return;
    }

    projet->afficheur->enregistrerMessage(ui->afficheur_index->value(), texte,
        ui->afficheur_texte_clignotant->checkState() == Qt::CheckState::Checked);
}

void IHMGlobale::afficheur_afficherMessage() {
    projet->afficheur->afficherMessage(ui->afficheur_index->value());
}

void IHMGlobale::afficheur_listerMessages() {
    QList<QString> messages = projet->afficheur->listerMessages();

    if (messages.isEmpty())
        ui->afficheur_status->setText(projet->afficheur->modbusClient->getLastError());

    ui->afficheur_messages->clear();
    for (int i=0; i<messages.length(); i++)
        ui->afficheur_messages->addItem(QString::number(i+1) + "- " + messages[i]);
}

