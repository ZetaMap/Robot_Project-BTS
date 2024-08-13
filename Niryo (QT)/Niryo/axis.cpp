#include "axis.h"


// Variables qui indiquent des valeurs min et max de chaque axe
const float NiryoAxis::j1BaseRange[2] =     {-2.860, 2.900};
const float NiryoAxis::j2ShoulderRange[2] = {-1.820, 0.600};
const float NiryoAxis::j3ElbowRange[2] =    {-1.290, 1.540};
const float NiryoAxis::j4ForeArmRange[2] =  {-2.080, 2.070};
const float NiryoAxis::j5WristRange[2] =    {-1.910, 1.910};
const float NiryoAxis::j6HandRange[2] =     {-2.510, 2.520};
const float NiryoAxis::jointsStandBy[6] =   {0, 0.5, -1.25, 0, 0, 0};

float NiryoAxis::umiliRadtoRad(quint16 mili) {
    float val = mili;
    // décode le signe
    if (mili >> 15) val = -(mili & 0x7fff);
    // et divise par 1000
    return val / 1000.0;
}

quint16 NiryoAxis::radToUMiliRad(float rad) {
    // multiple par 1000
    rad *= 1000.0;
    // encode le signe
    quint16 val = rad;
    if (rad < 0) val = (1 << 15) - rad;
    return val;
}


void NiryoAxis::startAxisGetterLoop() {
    // Vérifie si connecté
    if (!client->isConnected()) return;
    // Empêche le double lancement
    if (axisGetterRunning()) return;

    if (timer == nullptr) {
        timer = new QTimer();
        connect(timer, &QTimer::timeout, this, &NiryoAxis::forceReadAxis);
    }

    timer->start(AXIS_LOOP_DELAY);
    forceReadAxis();
    emit axisGetterStateChanged();
}

void NiryoAxis::stopAxisGetterLoop() {
    if (!axisGetterRunning()) return;

    // Stoppe le timer
    timer->stop();
    // Attend un peut, s'il est toujours actif
    if (timer->isActive()) QThread::msleep(100);

    emit axisGetterStateChanged();
}

void NiryoAxis::forceReadAxis() {
    if (!client->isConnected()) return;

    QModbusDataUnit request = client->inputRegistersRequest(0, 5);
    QModbusReply *reply = client->sendReadRequest(request);

    readError = reply == nullptr;
    if (readError) {
        // Signale la lecture même en cas d'erreur, pour le savoir.
        emit axisReaded();
        return;
    }

    // Réutilisation de la variable de requête pour la réponse.
    request = reply->result();

    // Les valeurs sont en mili-radians, convertion en radians.
    j1 = umiliRadtoRad(request.value(0));
    j2 = umiliRadtoRad(request.value(1));
    j3 = umiliRadtoRad(request.value(2));
    j4 = umiliRadtoRad(request.value(3));
    j5 = umiliRadtoRad(request.value(4));
    j6 = umiliRadtoRad(request.value(5));

    emit axisReaded();
}
