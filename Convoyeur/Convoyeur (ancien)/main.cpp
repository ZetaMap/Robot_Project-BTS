#include "technicianinterface.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TechnicianInterface w;
    w.show();
    return a.exec();
}
