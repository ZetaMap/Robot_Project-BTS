#include <QApplication>
#include "fanucrobotcontrol.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FanucRobotControl w;
    w.show();
    return a.exec();
}
