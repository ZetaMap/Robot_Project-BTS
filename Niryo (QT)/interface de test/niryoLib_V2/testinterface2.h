#ifndef TESTINTERFACE2_H
#define TESTINTERFACE2_H

#include <QMainWindow>
#include "niryocontroller.h"
#include "niryoinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class TestInterface2;
}
QT_END_NAMESPACE

class TestInterface2 : public QMainWindow
{
    Q_OBJECT

public:
    TestInterface2(QWidget *parent = nullptr);
    ~TestInterface2();

private:
    Ui::TestInterface2 *ui;
    NiryoController *ControllerNiryo;
    NiryoInfo *InfoNiryo;
    QList<TrajectoireNiryo> trajectoirs;

private slots:
    void connecterRobot();
    void verifierEtatConnection();
    void deconnecterRobot();
    void lancerMouvement();
    void positionZero();
    void positionRepo();
    void lancerCalibration();
    void mettreAJourInfo();
    void indexerTrajectoirs();
    void stopperRobot();
    void lancerTrajectoire();
    void attaperObjet();
    void lacherObjet();
    void modeApprentissage();
    void drapeau();
    void annulerApprentissage();
};
#endif // TESTINTERFACE2_H
