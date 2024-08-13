#include "niryo.h"

Niryo::Niryo() {
    serveurNormal = new ModbusUtil();
    serveurCustom = new ModbusUtil();

    axis = new NiryoAxis(serveurNormal);
    controller = new NiryoController(serveurNormal, axis);
    stats = new NiryoStats(serveurNormal);
    trajectory = new NiryoTrajectory(serveurCustom);
}

Niryo::~Niryo() {
    disconnectAll();

    delete axis;
    delete controller;
    delete stats;
    delete trajectory;
}

bool Niryo::connectServeurNormal(QString ip, int port) {
    return serveurNormal->connectDevice(ip, port);
}

bool Niryo::connectServeurCustom(QString ip, int port) {
    return serveurCustom->connectDevice(ip, port);
}

void Niryo::disconnectAll() {
    serveurNormal->disconnectDevice();
    serveurCustom->disconnectDevice();
}

