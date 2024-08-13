#ifndef NIRYOTRAJECTORY_H
#define NIRYOTRAJECTORY_H

#include "Niryo_global.h"
#include <modbusutil.h>
#include <QTimer>
#include <QEventLoop>

#include "enums.h"

#define TRAJECTORY_LOOP_DELAY 100 //ms


class NIRYO_EXPORT NiryoTrajectory : public QObject
{
    Q_OBJECT

public:
    // Juste une représentation des trajectoires.
    // Avec leurs index, identifiant unique et nom
    class TrajectoryData {
    public:
        TrajectoryData(int _index, int _id, QString _name, bool _valid=true) {
            index = _index;
            id = _id;
            name = _name;
            valid = _valid;
        }

        int getIndex() { return index; }
        int getID() { return id; }
        QString getName() { return name; }
        bool isValid() { return valid; }

    private:
        int index = 0, id = 0;
        QString name = "";
        bool valid = true;
    };


    NiryoTrajectory(ModbusUtil *_client) { client = _client; }
    ~NiryoTrajectory() {  }


    // Active/Désactive le mode d'apprentissage
    bool setLearningMode(bool enabled);
    // Enregistre la position actuel.
    bool addMoveFlag();
    // Ces fonctions sont différentes de NiryoController
    // car elles utilise le serveur custom qui va
    // enregistrer les commandes.
    bool setTool(bool enabled);
    bool setMotorSpeed(int percent);

    // Revoie un objet représentant les informations de la
    // trajectoire séletionné, ou NULL s'il y en a pas.
    TrajectoryData getSelectedTrajectory();
    // Change le nom de la trajectoire sélectionné
    bool setSelectedTrajectoryName(QString name);
    // Sauvegarde les informations de la trajectoire
    // sélectionné, puis la désélectionne.
    bool saveSelectedTrajectory();
    // Supprime la trajectoire sélectionné. (action irréversible)
    bool deleteSelectedTrajectory();

    // Sélectionne une trajectoire.
    bool selectTrajectory(int index);
    // Note : Depuis la dernière actualisation
    bool selectTrajectoryByID(int id);
    bool selectTrajectoryByName(QString name);

    // Lance la trajectoire sélectionné, wait permet
    // d'en attendre la fin.
    bool startTrajectory(bool wait=false);
    // Permet d'attendre la fin de la trajectoire
    bool waitForTrajectoryFinished(long timeout=10000); //10s
    // Stoppe la trajectoire en cours.
    bool stopTrajectory();

    // Liste les trajectoires et les renvoies.
    bool listTrajectories();
    // Demande combien de trajectoires sont disponibles.
    int numberOfTrajectories();
    // Revoie si une trajectoire est sélectionné.
    bool trajectoryIsSelected() { return isSelected; }

    // Désélectionne la trajectoire.
    bool unselectTrajectory();


    // Fonctions pour controler la boucle de lecture
    // des résultats de commandes.
    void startResultGetterLoop();
    void stopResultGetterLoop();
    bool resultGetterRunning() { return timer != NULL && timer->isActive(); }
    bool resultGetterReadError() { return readError; }

    // Accesseurs
    NiryoEnums::CommandResult getLastCommandResult() { return commandResult; }
    bool getCollisionDetected() { return commandResult == NiryoEnums::CommandResult::CollisionDetected; }
    bool getLearningModeIsRunning() { return isLearning; }
    bool getTrajectoryIsExecuting() { return isExecuting; }

    // Force la lecture du résultat de commande
    // L'utilisation directe est déconseillé,
    // il est préférable de laisser la boucle de lecture le faire.
    void forceReadCommandResult();

signals:
    // Signaux pour être signalé d'une lecture du résultat
    // de command et du changement d'état de la boucle.
    void resultReaded();
    void resultGetterStateChanged();
    void trajectorySelectChanged();
    void trajectoriesListed(QList<TrajectoryData> list);

protected:
    QModbusDataUnit sendRead(QModbusDataUnit request);
    bool sendValue(uint address, quint16 value);

private:
    // Liste des trajectoires du robot
    QList<TrajectoryData> trajectories;
    // Résultat de la dernière commande
    NiryoEnums::CommandResult commandResult = NiryoEnums::CommandResult::UnkownStatus;
    // Mode apprentissage activé
    bool isLearning = false;
    // Trajectoire en cours d'éxécution
    bool isExecuting = false;
    // Trajectoire est sélectionné
    bool isSelected = false;

    // Variable qui dit s'il y a eu une erreur de lecture
    bool readError = false;
    // Timer pour récupérer les valeurs des axes périodiquement
    QTimer *timer = NULL;
    // Client modbus
    ModbusUtil *client = NULL;
};

#endif // NIRYOTRAJECTORY_H
