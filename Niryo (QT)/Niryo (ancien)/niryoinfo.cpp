#include "niryoinfo.h"

NiryoInfo::NiryoInfo(NiryoController *_controlleur)
{
    this->controlleur = _controlleur;
    this->temperature = 0;

    for(int i = 0 ; i < 6 ; i++){
        this->axesAngles[i]= 0.00;
    }
    for(int i = 0 ; i < 3 ; i++){
        this->positionsXYZ[i] = 0;
        this->rollPitchYaw[i] = 0.00;
    }
    this->toolID = 0;
    this->learningModOn = false;
    this->colision = false;
    this->motorsConnection = false;
}

NiryoInfo::~NiryoInfo()
{

}

bool NiryoInfo::actualiserInformations()
{
    if(!actualiserAxes()){
        return false;
    }
    if(!actualiserPosition()){
        return false;
    }
    if(!actualiserOrientation()){
        return false;
    }
    if(!actualiserOutil()){
        return false;
    }
    if(!actualiserApprentissage()){
        return false;
    }

    return true;
}

bool NiryoInfo::actualiserAxes()
{
    QList<float> reponse;
    bool ok = false;
    reponse = controlleur->recupererAxes(ok);

    if(!ok){
        return false;
    }
    if(reponse.length() != 6){
        return false;
    }
    for(int i = 0 ; i < 6 ; i++){
        axesAngles[i] = reponse.value(i);
    }
    return true;

}

bool NiryoInfo::actualiserPosition()
{
    QList<int> reponse;
    bool ok = false;
    reponse = controlleur->recupererPosition(ok);

    if(!ok){
        return false;
    }
    if(reponse.length() != 3){
        return false;
    }

    for(int i = 0 ; i < 3 ; i++){
        positionsXYZ[i] = reponse.value(i);
    }
    return true;
}

bool NiryoInfo::actualiserOrientation()
{
    QList<float> reponse;
    bool ok = false;
    reponse = controlleur->recupererOrientation(ok);
    qDebug() << reponse;
    if(!ok){
        return false;
    }

    if(reponse.length() != 3){
        return false;
    }

    for(int i = 0 ; i < 3 ; i++){
        rollPitchYaw[i] = reponse.value(i);
    }
    return true;
}

bool NiryoInfo::actualiserOutil()
{
    int reponse;
    bool ok = false;
    reponse = controlleur->recupererOutil(ok);

    if(!ok){
        return false;
    }

    this->toolID = reponse;

    return true;
}

bool NiryoInfo::actualiserApprentissage()
{
    QList<bool> reponse;
    bool ok = false;

    reponse = controlleur->recupererAprentissage(ok);

    this->learningModOn = reponse.value(0);

    return ok;
}

int NiryoInfo::getTemperarure()
{
    return temperature;
}

QList<float> NiryoInfo::getAngles()
{
    QList<float> resultat;
    for(int i = 0; i < 6 ; i++){
        resultat.append(axesAngles[i]);
    }
    return resultat;
}

QList<int> NiryoInfo::getPositionXYS()
{
    QList<int> resultat;
    for(int i = 0; i < 3 ; i++){
        resultat.append(positionsXYZ[i]);
    }
    return resultat;
}

QList<float> NiryoInfo::getRollPitchYaw()
{
    QList<float> resultat;
    for(int i = 0; i < 3 ; i++){
        resultat.append(rollPitchYaw[i]);
    }
    return resultat;
}

int NiryoInfo::getOutil()
{
    return toolID;
}

bool NiryoInfo::getApprentissageEnCour()
{
    return learningModOn;
}

void NiryoInfo::debugDump()
{
    for (int i = 0; i < 6; ++i) {
        qDebug() << "angle" << i << " : " << axesAngles[i];
    }
    for (int i = 0; i < 3; ++i) {
        qDebug() << "pos" << i << " : " << positionsXYZ[i];
    }
    for (int i = 0; i < 3; ++i) {
        qDebug() << "orientaion" << i << " : " << rollPitchYaw[i];
    }
    qDebug() << "toolID: " << toolID << "\nlearningmod: " << learningModOn << "\nmotorsco: " << motorsConnection ;
}
