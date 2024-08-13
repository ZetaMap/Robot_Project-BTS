#ifndef NIRYOSTATS_H
#define NIRYOSTATS_H

#include "Niryo_global.h"
#include <modbusutil.h>
#include <QTimer>

#include "enums.h"

#define STATS_LOOP_DELAY 2000 //ms
// Les 6 axes plus l'outil et le panneau 3 boutons
#define STATS_HARDWARES_NUMBER 8


class NIRYO_EXPORT NiryoStats : public QObject
{
    Q_OBJECT

public:
    NiryoStats(ModbusUtil *_client) { client = _client; }
    NiryoStats() { stopStatsGetterLoop(); }


    // Fonctions pour lancer ou stopper la boucle
    // qui récupère les statistiques du robot.
    void startStatsGetterLoop();
    void stopStatsGetterLoop();
    bool statsGetterRunning() { return timer != NULL && timer->isActive(); }
    bool statsGetterReadError() { return readError; }

    // Accesseurs des statistiques.
    NiryoEnums::ToolType getToolType() { return tool; }
    bool getMotorsConnectionUp() { return motorsConnection; }
    NiryoEnums::CalibrationType getCalibrationState() { return calibration; }
    int getRaspberryPiTemperature() { return rPiTemp; }
    QString getNedRPiVersion() { return nedVersion; }
    int* getHardwareTemperatures() { return hardwareTemps; }
    float* getHardwareVoltages() { return hardwareVoltages; }
    int* getHardwareErrors() { return hardwareErrors; }

    // Force la lecture des statistiques.
    // L'utilisation directe est déconseillé,
    // il est préférable de laisser la boucle de lecture le faire.
    void forceReadStats();

signals:
    // Signaux pour être signalé d'une lecture des
    // statistiques et du changement d'état de la boucle.
    void statsReaded();
    void statsGetterStateChanged();

protected:
    QModbusDataUnit sendRead(QModbusDataUnit request);

private:
    // Type d'outil
    NiryoEnums::ToolType tool = NiryoEnums::ToolType::None;
    // true=ok, false=problème.
    bool motorsConnection = false;
    // Status calibration
    NiryoEnums::CalibrationType calibration = NiryoEnums::CalibrationType::Calibrated;
    // Température Raspberry PI
    int rPiTemp = 0;
    // Version image Ned Raspberry Pi (maj.min.patch)
    QString nedVersion = "";
    // Températures des matériels
    int hardwareTemps[STATS_HARDWARES_NUMBER] = {};
    // Tensions des matériels
    float hardwareVoltages[STATS_HARDWARES_NUMBER] = {};
    // Erreurs des matériels
    int hardwareErrors[STATS_HARDWARES_NUMBER] = {};

    // Variable qui dit s'il y a eu une erreur de lecture
    bool readError = false;
    // Timer pour récupérer les valeurs des axes périodiquement
    QTimer *timer = NULL;
    // Client modbus
    ModbusUtil *client = NULL;
};

#endif // NIRYOSTATS_H
