#ifndef NIRYO_H
#define NIRYO_H

#include "Niryo_global.h"
#include <modbusutil.h>


#include "axis.h"
#include "controller.h"
#include "stats.h"
#include "trajectory.h"


class NIRYO_EXPORT Niryo : public QObject
{
public:
    // Object pour récupérer le valeurs des axes
    NiryoAxis *axis = NULL;

    // Object pour controler le robot
    // Note : uniquement avec le serveur de base, pas le custom
    NiryoController *controller = NULL;

    // Object pour récupérer les statistiques du robot
    NiryoStats *stats = NULL;

    // Object pour le mode d'apprentissage, et la gestion
    // des trajectoires
    NiryoTrajectory *trajectory = NULL;

    // Client modbus pour le serveur par défaut du robot
    // et pour le serveur ajouté pour le projet
    ModbusUtil *serveurNormal = NULL,
               *serveurCustom = NULL;


    Niryo();
    ~Niryo();


    bool connectServeurNormal(QString ip, int port);
    bool connectServeurCustom(QString ip, int port);
    void disconnectAll();
};

#endif // NIRYO_H
