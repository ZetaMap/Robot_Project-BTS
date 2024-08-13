#ifndef NIRYOCONTROLLER_H
#define NIRYOCONTROLLER_H

#include "Niryo_global.h"
#include <modbusutil.h>
#include <QTimer>
#include <QEventLoop>

#include "axis.h"
#include "enums.h"

#define CONTROLLER_LOOP_DELAY 100 //ms


// Classe pour controller le robot.
// (uniquement avec le serveur de base)

// Bouger le robot, changer l'état de l'outil,
// faire une calibration, etc.
class NIRYO_EXPORT NiryoController : public QObject
{
    Q_OBJECT

public:
    NiryoController(ModbusUtil *_client, NiryoAxis *_axis) {
        client = _client;
        axis = _axis;
    }
    ~NiryoController() { stopResultGetterLoop(); }


    // Envoie la commande au robot de bouger.
    // Le paramètre wait permet d'attendre que le
    // mouvement soit effectué.
    bool moveTo(float j1, float j2, float j3, float j4, float j5, float j6, bool wait=false);
    // Bouge en position de repos
    bool moveToStandBy(bool wait=false);
    // Bouge en position zéro
    bool moveToZero(bool wait=false);
    // Attend que le mouvement soit fini
    bool waitForMoveFinished(long timeout=10000); //ms
    // Stoppe le mouvement du robot
    bool stopMove();
    // Retire le drappeau de collision
    bool clearCollisionDetected();
    // Fait une recherche d'outil
    bool updateTool();
    // Active ou désactive l'outil
    bool setTool(bool enabled);
    // Change la vitesse des moteurs, entre 1 et 200%
    bool setMotorSpeed(int percent);
    // Effectue une nouvelle calibration
    bool newCalibration();

    // Fonctions pour controler la boucle de lecture
    // des résultats de commandes.
    void startResultGetterLoop();
    void stopResultGetterLoop();
    bool resultGetterRunning() { return timer != NULL && timer->isActive(); }
    bool resultGetterReadError() { return readError; }

    // Accesseurs
    NiryoEnums::CommandResult getLastCommandResult() { return commandResult; }
    bool getCollisionDetected() { return commandResult == NiryoEnums::CommandResult::CollisionDetected; }
    bool getCommandIsExecuting() { return cmdRunning; }

    // Force la lecture du résultat de commande
    // L'utilisation directe est déconseillé,
    // il est préférable de laisser la boucle de lecture le faire.
    void forceReadCommandResult();

signals:
    // Signaux pour être signalé d'une lecture du résultat
    // de command et du changement d'état de la boucle.
    void resultReaded();
    void resultGetterStateChanged();

protected:
    bool sendValue(uint address, quint16 value);

private:
    // Résultat de la dernière commande
    NiryoEnums::CommandResult commandResult = NiryoEnums::CommandResult::UnkownStatus;
    // Command en cours
    bool cmdRunning = false;
    // Pour pouvoir lancer la boucle des axes et faire des converssions
    NiryoAxis *axis;

    // Variable qui dit s'il y a eu une erreur de lecture
    bool readError = false;
    // Timer pour récupérer les valeurs des axes périodiquement
    QTimer *timer = NULL;
    // Client modbus
    ModbusUtil *client = NULL;
};

#endif // NIRYOCONTROLLER_H
