#include "trajectory.h"


bool NiryoTrajectory::setLearningMode(bool enabled) {
    bool ok = sendValue(0, enabled);
    if (!ok) return false;
    // Avertis d'une sélection de trajectoire
    forceReadCommandResult();
    emit trajectorySelectChanged();
    return ok;
}

bool NiryoTrajectory::addMoveFlag() {
    return sendValue(1, 1);
}

bool NiryoTrajectory::setTool(bool enabled) {
    return sendValue(2, enabled);
}

bool NiryoTrajectory::setMotorSpeed(int percent) {
    return sendValue(3, std::clamp(percent, 1, 200));
}


NiryoTrajectory::TrajectoryData NiryoTrajectory::getSelectedTrajectory() {
    TrajectoryData nothing(-1, -1, "<unknown>", false);
    if (!client->isConnected()) return nothing;

    QModbusDataUnit reply = sendRead(client->holdingRegistersRequest(41));
    if (reply.registerType() == QModbusDataUnit::RegisterType::Invalid)
        return nothing;

    int index = reply.value(0);

    forceReadCommandResult();
    if (getLastCommandResult() == NiryoEnums::IsLearning)
        return nothing;


    reply = sendRead(client->holdingRegistersRequest(10, 22));
    if (reply.registerType() == QModbusDataUnit::RegisterType::Invalid)
        return nothing;

    QString name;
    for (int i=0; i<20; i++) {
        if(reply.value(i) == 0) continue;
        name += (char) reply.value(i);
    }


    return TrajectoryData(index, reply.value(21), name);
}

bool NiryoTrajectory::setSelectedTrajectoryName(QString name) {
    if(!client->isConnected()) return false;

    // Vérifie les caractères non affichable
    for (int i=0; i<name.length(); i++) {
        if (!name.at(i).isPrint()) {
            client->setError("Format de nom invalide");
            return false;
        }
    }

    QModbusDataUnit request = client->holdingRegistersRequest(10, 20);
    for (int i=0; i<name.length(); i++) request.setValue(i, name.at(i).unicode());
    QModbusReply *reply = client->sendWriteRequest(request);

    bool ok = reply != NULL;
    if (!ok) return false;
    reply->deleteLater();
    return ok;
}

bool NiryoTrajectory::saveSelectedTrajectory() {
    return sendValue(40, 1);
}

bool NiryoTrajectory::deleteSelectedTrajectory() {
    return sendValue(40, 2);
}


bool NiryoTrajectory::selectTrajectory(int index) {
    bool ok = sendValue(41, index);
    if (!ok) return false;
    // Avertis d'une sélection de trajectoire
    emit trajectorySelectChanged();
    return ok;
}

bool NiryoTrajectory::selectTrajectoryByID(int id) {
    for (int i=0; i<trajectories.length(); i++) {
        if(trajectories[i].getID() == id)
            return selectTrajectory(i);
    }
    return false;
}

bool NiryoTrajectory::selectTrajectoryByName(QString name) {
    for (int i=0; i<trajectories.length(); i++) {
        if(trajectories[i].getName() == name)
            return selectTrajectory(i);
    }
    return false;
}


bool NiryoTrajectory::startTrajectory(bool wait) {
    bool ok = sendValue(42,1);
    if (!ok) return false;
    return wait ? waitForTrajectoryFinished() : ok;
}

bool NiryoTrajectory::waitForTrajectoryFinished(long timeout) {
    if (!client->isConnected()) return false;
    startResultGetterLoop();

    QEventLoop *loop = new QEventLoop();
    QTimer *timer = new QTimer();

    connect(timer, &QTimer::timeout, [&timeout, loop]() {
        timeout = -1;
        loop->quit();
    });
    connect(this, &NiryoTrajectory::resultReaded, [this, loop, timer]() {
        if (!getTrajectoryIsExecuting()) {
            timer->stop();
            loop->quit();
        }
    });

    timer->setSingleShot(true);
    timer->start(timeout);
    loop->exec();

    return timeout != -1;
}

bool NiryoTrajectory::stopTrajectory() {
    return sendValue(43,1);
}


bool NiryoTrajectory::listTrajectories() {
    int size = numberOfTrajectories();
    if (size == -1) return false;

    QList<NiryoTrajectory::TrajectoryData> list;

    for (int i=0; i<size; i++) {
        selectTrajectory(i);
        NiryoTrajectory::TrajectoryData current = getSelectedTrajectory();
        if (!current.isValid()) return false;
        list.append(current);
    }
    unselectTrajectory();

    trajectories = list;
    // Notifie le listage des trajectoires
    emit trajectoriesListed(list);
    return true;
}

int NiryoTrajectory::numberOfTrajectories() {
    if (!client->isConnected()) return -1;
    QModbusDataUnit reply = sendRead(client->holdingRegistersRequest(50));
    if (reply.registerType() == QModbusDataUnit::RegisterType::Invalid) return -1;
    return reply.value(0);
}


bool NiryoTrajectory::unselectTrajectory() {
    return sendValue(51, 0);
}



void NiryoTrajectory::startResultGetterLoop() {
    // Vérifie si connecté
    if (!client->isConnected()) return;
    // Empêche le double lancement
    if (resultGetterRunning()) return;

    if (timer == NULL) {
        timer = new QTimer();
        connect(timer, &QTimer::timeout, this, &NiryoTrajectory::forceReadCommandResult);
    }

    timer->start(TRAJECTORY_LOOP_DELAY);
    forceReadCommandResult();
    emit resultGetterStateChanged();
}

void NiryoTrajectory::stopResultGetterLoop() {
    if (!resultGetterRunning()) return;

    // Stoppe le timer
    timer->stop();
    // Attend un peut, s'il est toujours actif
    if (timer->isActive()) QThread::msleep(100);

    emit resultGetterStateChanged();
}

void NiryoTrajectory::forceReadCommandResult() {
    QModbusDataUnit result = sendRead(client->holdingRegistersRequest(0));
    if (result.registerType() == QModbusDataUnit::RegisterType::Invalid) return;

    isLearning = result.value(0);


    result = sendRead(client->holdingRegistersRequest(42));
    if (result.registerType() == QModbusDataUnit::RegisterType::Invalid) return;

    isExecuting = result.value(0);


    result = sendRead(client->holdingRegistersRequest(51));
    if (result.registerType() == QModbusDataUnit::RegisterType::Invalid) return;

    bool last = isSelected;
    isSelected = result.value(0);
    if (last != isSelected) emit trajectorySelectChanged();


    result = sendRead(client->holdingRegistersRequest(100));
    if (result.registerType() == QModbusDataUnit::RegisterType::Invalid) return;

    // Pas sûr de sa, à voir pour des problèmes futurs
    commandResult = static_cast<NiryoEnums::CommandResult>(result.value(0));

    emit resultReaded();
}

QModbusDataUnit NiryoTrajectory::sendRead(QModbusDataUnit request) {
    QModbusReply *reply = client->sendReadRequest(request);
    QModbusDataUnit result;

    readError = reply == NULL;
    if (readError) {
        // Signale la lecture même en cas d'erreur, pour le savoir.
        emit resultReaded();
        result.setRegisterType(QModbusDataUnit::RegisterType::Invalid);
        return result;
    }

    result = reply->result();
    reply->deleteLater();
    return result;
}

bool NiryoTrajectory::sendValue(uint address, quint16 value) {
    if(!client->isConnected()) return false;

    QModbusDataUnit request = client->holdingRegistersRequest(address);
    request.setValue(0, value);
    QModbusReply *reply = client->sendWriteRequest(request);

    bool ok = reply != NULL;
    if (!ok) return false;
    reply->deleteLater();
    return ok;
}
