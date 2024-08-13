#include "stats.h"


void NiryoStats::startStatsGetterLoop() {
    // Vérifie si connecté
    if (!client->isConnected()) return;
    // Empêche le double lancement
    if (statsGetterRunning()) return;

    if (timer == NULL) {
        timer = new QTimer();
        connect(timer, &QTimer::timeout, this, &NiryoStats::forceReadStats);
    }

    timer->start(STATS_LOOP_DELAY);
    forceReadStats();
    emit statsGetterStateChanged();
}

void NiryoStats::stopStatsGetterLoop() {
    if (!statsGetterRunning()) return;

    // Stoppe le timer
    timer->stop();
    // Attend un peut, s'il est toujours actif
    if (timer->isActive()) QThread::msleep(100);

    emit statsGetterStateChanged();
}

void NiryoStats::forceReadStats() {
    QModbusDataUnit result = sendRead(client->inputRegistersRequest(200));
    if (result.registerType() == QModbusDataUnit::RegisterType::Invalid) return;

    // Pas sûr de sa, à voir pour des problèmes futurs
    tool = static_cast<NiryoEnums::ToolType>(result.value(0));


    result = sendRead(client->inputRegistersRequest(400, 34));
    if (result.registerType() == QModbusDataUnit::RegisterType::Invalid) return;

    motorsConnection = result.value(0);
    calibration = result.value(1) ? NiryoEnums::CalibrationType::Nedded :
                  result.value(2) ? NiryoEnums::CalibrationType::InProgress :
                                    NiryoEnums::CalibrationType::Calibrated;
    rPiTemp = result.value(3);
    nedVersion = QString::number(result.value(6))+'.'+QString::number(result.value(7))+'.'+QString::number(result.value(8));
    // Met la température, la tesion et le code d'erreur, avec la même boucle
    for (int i=0; i<STATS_HARDWARES_NUMBER; i++) {
        hardwareTemps[i] = result.value(10 + i);
        hardwareVoltages[i] = result.value(18 + i) / 1000.0; // car recu en mili-volt
        hardwareErrors[i] = result.value(26 + i);
    }

    emit statsReaded();
}

QModbusDataUnit NiryoStats::sendRead(QModbusDataUnit request) {
    QModbusReply *reply = client->sendReadRequest(request);
    QModbusDataUnit result;

    readError = reply == NULL;
    if (readError) {
        // Signale la lecture même en cas d'erreur, pour le savoir.
        emit statsReaded();
        result.setRegisterType(QModbusDataUnit::RegisterType::Invalid);
        return result;
    }

    result = reply->result();
    reply->deleteLater();
    return result;
}
