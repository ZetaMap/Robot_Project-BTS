#include "piloterobotmi10.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PiloteRobotMi10 w;
    w.show();
    return a.exec();
}
