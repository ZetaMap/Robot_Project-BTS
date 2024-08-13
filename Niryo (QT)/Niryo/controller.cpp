#include "controller.h"


bool NiryoController::moveTo(float j1, float j2, float j3, float j4, float j5, float j6, bool wait) {
    if(!client->isConnected()) return false;

    // Envoie les valeurs des axes a suivre.
    QModbusDataUnit request = client->holdingRegistersRequest(0, 5);

    // Note: std::clamp permet d'appliquer un seuil min et max a une valeur, "clip a value".
    request.setValue(0, axis->radToUMiliRad(std::clamp(j1, axis->j1BaseRange[0], axis->j1BaseRange[1])));
    request.setValue(1, axis->radToUMiliRad(std::clamp(j2, axis->j2ShoulderRange[0], axis->j2ShoulderRange[1])));
    request.setValue(2, axis->radToUMiliRad(std::clamp(j3, axis->j3ElbowRange[0], axis->j3ElbowRange[1])));
    request.setValue(3, axis->radToUMiliRad(std::clamp(j4, axis->j4ForeArmRange[0], axis->j4ForeArmRange[1])));
    request.setValue(4, axis->radToUMiliRad(std::clamp(j5, axis->j5WristRange[0], axis->j5WristRange[1])));
    request.setValue(5, axis->radToUMiliRad(std::clamp(j6, axis->j6HandRange[0], axis->j6HandRange[1])));

    QModbusReply *reply = client->sendWriteRequest(request);

    bool ok = reply != NULL;
    if (!ok) return false;
    reply->deleteLater();

    // Envoie la commande de bouger
    ok = sendValue(100, 1);
    if (!ok) return false;

    // Attend la fin du mouvement, si spécifié
    return wait ? waitForMoveFinished() : ok;
}

bool NiryoController::moveToStandBy(bool wait) {
    return moveTo(axis->jointsStandBy[0], axis->jointsStandBy[1], axis->jointsStandBy[2],
                  axis->jointsStandBy[3], axis->jointsStandBy[4], axis->jointsStandBy[5],
                  wait);
}

bool NiryoController::moveToZero(bool wait) {
    return moveTo(0, 0, 0, 0, 0, 0, wait);
}

bool NiryoController::waitForMoveFinished(long timeout) {
    if (!client->isConnected()) return false;
    startResultGetterLoop();

    QEventLoop *loop = new QEventLoop();
    QTimer *timer = new QTimer();

    connect(timer, &QTimer::timeout, [&timeout, loop]() {
        timeout = -1;
        loop->quit();
    });
    connect(this, &NiryoController::resultReaded, [this, loop, timer]() {
        if (!getCommandIsExecuting()) {
            timer->stop();
            loop->quit();
        }
    });

    timer->setSingleShot(true);
    timer->start(timeout);
    loop->exec();

    return timeout != -1;
}

bool NiryoController::stopMove() {
    return sendValue(110, 1);
}

bool NiryoController::clearCollisionDetected() {
    return sendValue(103, 1);
}

bool NiryoController::updateTool() {
    return sendValue(500, 1);
}

bool NiryoController::setTool(bool enabled) {
    return sendValue(513 - enabled, 1);
}

bool NiryoController::setMotorSpeed(int percent) {
    return sendValue(514, std::clamp(percent, 1, 200));
}

bool NiryoController::newCalibration() {
    if (!sendValue(310, 1)) return false;
    return sendValue(311, 1);
}


void NiryoController::startResultGetterLoop() {
    // Vérifie si connecté
    if (!client->isConnected()) return;
    // Empêche le double lancement
    if (resultGetterRunning()) return;

    // Lance la boucle de lecture des axes en premier
    axis->startAxisGetterLoop();

    if (timer == NULL) {
        timer = new QTimer();
        connect(timer, &QTimer::timeout, this, &NiryoController::forceReadCommandResult);
    }

    timer->start(CONTROLLER_LOOP_DELAY);
    forceReadCommandResult();
    emit resultGetterStateChanged();
}

void NiryoController::stopResultGetterLoop() {
    if (!resultGetterRunning()) return;

    // Stoppe le timer
    timer->stop();
    // Attend un peut, s'il est toujours actif
    if (timer->isActive()) QThread::msleep(100);

    emit resultGetterStateChanged();
}

void NiryoController::forceReadCommandResult() {
    if (!axis->axisGetterRunning()) {
        stopResultGetterLoop();
        return;
    }

    QModbusDataUnit request = client->holdingRegistersRequest(150, 2);
    QModbusReply *reply = client->sendReadRequest(request);

    readError = reply == NULL;
    if (readError) {
        // Signale la lecture même en cas d'erreur, pour le savoir.
        emit resultReaded();
        return;
    }

    // Réutilisation de la variable de requête pour la réponse.
    request = reply->result();

    cmdRunning = request.value(0) != 0;
    commandResult = static_cast<NiryoEnums::CommandResult>(request.value(1));

    emit resultReaded();
}


bool NiryoController::sendValue(uint address, quint16 value) {
    if(!client->isConnected()) return false;

    QModbusDataUnit request = client->holdingRegistersRequest(address);
    request.setValue(0, value);
    QModbusReply *reply = client->sendWriteRequest(request);

    bool ok = reply != NULL;
    if (!ok) return false;
    reply->deleteLater();
    return ok;
}
