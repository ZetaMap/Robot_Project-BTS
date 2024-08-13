#ifndef NIRYOAXIS_H
#define NIRYOAXIS_H

#include "Niryo_global.h"
#include <modbusutil.h>
#include <QTimer>

#define AXIS_LOOP_DELAY 100 //ms


// Classe pour récupérer les valeurs des axes du Niryo.
// Les valeurs sont communiquées en mili-radiant,
// puis convertis en radians ou en degrès.
class NIRYO_EXPORT NiryoAxis : public QObject
{
    Q_OBJECT

public:
    // Variables qui indiquent des valeurs min et max de chaque axe
    static const float j1BaseRange[2];
    static const float j2ShoulderRange[2];
    static const float j3ElbowRange[2];
    static const float j4ForeArmRange[2];
    static const float j5WristRange[2];
    static const float j6HandRange[2];
    static const float jointsStandBy[6];

    // Permet la converssion entre mili-radiants sans signe et radiants
    static float umiliRadtoRad(quint16 mili);
    static quint16 radToUMiliRad(float rad);


    NiryoAxis(ModbusUtil *_client) { client = _client; }
    ~NiryoAxis() { stopAxisGetterLoop(); }


    // Accesseurs des axes.
    // Le paramètre 'toDeg' est optionnel et peut etre
    // mis à true pour avoir les valeurs en degrès.
    float getJ1Base(bool toDeg=false)     { return toDeg ? qRadiansToDegrees(j1) : j1; }
    float getJ2Shoulder(bool toDeg=false) { return toDeg ? qRadiansToDegrees(j2) : j2; }
    float getJ3Elbow(bool toDeg=false)    { return toDeg ? qRadiansToDegrees(j3) : j3; }
    float getJ4ForeArm(bool toDeg=false)  { return toDeg ? qRadiansToDegrees(j4) : j4; }
    float getJ5Wrist(bool toDeg=false)    { return toDeg ? qRadiansToDegrees(j5) : j5; }
    float getJ6Hand(bool toDeg=false)     { return toDeg ? qRadiansToDegrees(j6) : j6; }

    // Fonctions pour lancer ou stopper la boucle
    // qui récupère les valeurs des axes.
    void startAxisGetterLoop();
    void stopAxisGetterLoop();
    bool axisGetterRunning() { return timer != NULL && timer->isActive(); }
    bool axisGetterReadError() { return readError; }

    // Force la lecture des axes.
    // L'utilisation directe est déconseillé,
    // il est préférable de laisser la boucle de lecture le faire.
    void forceReadAxis();

signals:
    // Signaux pour être signalé d'une lecture des axes
    // et du changement d'état de la boucle.
    void axisReaded();
    void axisGetterStateChanged();

private:
    // Variables qui stocke les valeurs des axes
    float j1 = 0, j2 = 0, j3 = 0, j4 = 0, j5 = 0, j6 = 0;

    // Variable qui dit s'il y a eu une erreur de lecture
    bool readError = false;
    // Timer pour récupérer les valeurs des axes périodiquement
    QTimer *timer = NULL;
    // Client modbus
    ModbusUtil *client = NULL;
};

#endif // NIRYOAXIS_H
