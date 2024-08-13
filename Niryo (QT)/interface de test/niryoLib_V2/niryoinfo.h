#ifndef NIRYOINFO_H
#define NIRYOINFO_H

#include "niryocontroller.h"

class NiryoInfo
{
public:
    NiryoInfo(NiryoController *_controlleur);
    ~NiryoInfo();

    bool actualiserInformations();//actualise toutes les informations sur le robot
    bool actualiserAxes();
    bool actualiserPosition();
    bool actualiserOrientation();
    bool actualiserOutil();
    bool actualiserApprentissage();
    bool actualiserInfoDiverse();

    int getTemperarure();
    QList<float> getAngles();
    QList<int> getPositionXYS();
    QList<float> getRollPitchYaw();
    int getOutil();
    bool getApprentissageEnCour();

    void debugDump();
private:
    NiryoController *controlleur;
    int temperature;
    float axesAngles[6];                // address 0-5 fnct 4
    int positionsXYZ[3];                // address 10-12 fnct 4
    float rollPitchYaw[3];              // address 13-15 fnct 4
    int toolID;                         // address 200 fnct 4
    bool learningModOn;                 // address 300 fnct 4
    bool colision;                      // address 301 fnct 4
    bool motorsConnection;              // address 400 fnct 4
    bool calibrationRequise;            // address 401 fnct 4
    bool calibrationEnCour;            // address 402 fnct 4
};

#endif // NIRYOINFO_H
