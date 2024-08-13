#ifndef POSENIRYO_H
#define POSENIRYO_H

#include<QList>

class PoseNiryo
{
public:
    PoseNiryo();
    PoseNiryo(QList<float> _axes,bool _estEnDegree);
    PoseNiryo(float _axes[],bool _estEnDegree);
    PoseNiryo(float axe1,float axe2,float axe3,float axe4,float axe5,float axe6,bool _estEnDegree);

    bool setPose(QList<float> _axes,bool _estEnDegree);
    bool setPose(float _axes[],bool _estEnDegree);
    bool setPose(float axe1,float axe2,float axe3,float axe4,float axe5,float axe6,bool _estEnDegree);

    QList<float> getAxesRadiant();
    QList<float> getAxesDegree();

    QList<quint16> getAxesQuint16();

    bool getEstEnDegree();

    bool appliquerLimites();


private:
    QList<float> axes;
    bool estEnDegree;

    QList<float> degreeVersRadiantL(QList<float> f);
    QList<float> radiantVersDegreeL(QList<float> f);
    QList<quint16> radiantVersQuint16L(QList<float> f);
    QList<quint16> degreeVersQuint16L(QList<float> f);

    float degreeVersRadiant(float f);
    float radiantVersDegree(float f);

    quint16 radiantVersQuint16(float f);
    float quint16VersRadiant(quint16 _axerobot);
};

#endif // POSENIRYO_H
