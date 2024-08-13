#ifndef NIRYOENUMS_H
#define NIRYOENUMS_H

#include "Niryo_global.h"
#include <QObject>
#include <QMetaEnum>


class NIRYO_EXPORT NiryoEnums : public QObject
{
    Q_OBJECT

public:
    enum CommandResult {
        // Erreurs de base
        NoResultYeet = 0,
        CommandSuccess = 1,
        CommandRejected = 2,
        CommandAborded = 3,
        CommandCancelled = 4,
        UnkownStatus = 5,
        CommandTimeout = 6,
        InternalFailure = 7,
        CommandIsRunning = 8,
        CollisionDetected = 9,

        // Erreurs ajoutées par le serveur custom
        FatalError = 99,
        IsLearning = 100,
        NotLearning = 101,
        NothingSelected = 102,
        TrajectoryNotFound = 103,
        InvalidTrajectoryName = 104,
        EmptyTrajectoryName = 105,
        InvalidTrajectory = 106,
        TrajectoryNotRunning = 107,
        TrajectoryAlreadyRunning = 108,
        TrajectoryAborded = 109,
    };
    Q_ENUM(CommandResult)

    enum ToolType {
        None = 0,
        StandardGripper = 11,
        LargeGripper = 12,
        AdaptativeGripper = 13,
        Gripper4 = 14, // TODO: nom a trouver
        ElectroMagnet = 30,
        VacuumPump = 31,
    };
    Q_ENUM(ToolType)

    enum CalibrationType {
        UnknownState,
        Nedded,
        InProgress,
        Calibrated,
    };
    Q_ENUM(CalibrationType)


    static QString getCommandResultName(NiryoEnums::CommandResult command) {
        QString name = QString(QMetaEnum::fromType<NiryoEnums::CommandResult>().valueToKey(command));
        return camelCase2UpperCase(name);
    }

    static QString getToolName(NiryoEnums::ToolType tool) {
        QString name = QString(QMetaEnum::fromType<NiryoEnums::ToolType>().valueToKey(tool));
        return camelCase2UpperCase(name);
    }

    static QString getCalibrationName(NiryoEnums::CalibrationType calibration) {
        QString name = QString(QMetaEnum::fromType<NiryoEnums::CalibrationType>().valueToKey(calibration));
        return camelCase2UpperCase(name);
    }


    /* Convert camelCase to Upper Case. */
    static QString camelCase2UpperCase(QString string) {
        QString result;

        for (int i=0; i<string.length(); i++) {
            QChar letter = string.at(i);

            if (i == 0) letter = letter.toUpper();
            else if (letter.isUpper()) result += ' ';

            result += letter;
        }

        return result;
    }
};

#endif // NIRYOENUMS_H
