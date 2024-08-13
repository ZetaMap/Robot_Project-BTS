#include "poseniryo.h"

PoseNiryo::PoseNiryo()
{
    for (int i = 0; i < 6; ++i) {
        axes.append(0.00);
    }
    estEnDegree = false;
}

PoseNiryo::PoseNiryo(QList<float> _axes,bool _estEnDegree)
{
    for (int i = 0; i < 6; ++i) {
        axes.append(_axes.value(i));
    }
    estEnDegree = _estEnDegree;

}

PoseNiryo::PoseNiryo(float _axes[],bool _estEnDegree)
{
    for (int i = 0; i < 6; ++i) {
        axes.append(_axes[i]);
    }
    estEnDegree = _estEnDegree;
}

PoseNiryo::PoseNiryo(float axe1, float axe2, float axe3, float axe4, float axe5, float axe6,bool _estEnDegree)
{
    axes.append(axe1);
    axes.append(axe2);
    axes.append(axe3);
    axes.append(axe4);
    axes.append(axe5);
    axes.append(axe6);
    estEnDegree = _estEnDegree;
}

bool PoseNiryo::setPose(QList<float> _axes,bool _estEnDegree)
{
    if(_axes.length() < 6){
        return false;
    }
    for (int i = 0; i < 6; ++i) {
        axes[i] = _axes.value(i);
    }
    estEnDegree = _estEnDegree;
    return true;
}

bool PoseNiryo::setPose(float _axes[],bool _estEnDegree)
{
    for (int i = 0; i < 6; ++i) {
        axes[i] = _axes[i];
    }
    estEnDegree = _estEnDegree;
    return true;
}

bool PoseNiryo::setPose(float axe1, float axe2, float axe3, float axe4, float axe5, float axe6,bool _estEnDegree)
{
    axes.append(axe1);
    axes.append(axe2);
    axes.append(axe3);
    axes.append(axe4);
    axes.append(axe5);
    axes.append(axe6);
    estEnDegree = _estEnDegree;
    return true;
}

QList<float> PoseNiryo::getAxesRadiant()
{
    if(estEnDegree){
        return degreeVersRadiantL(axes);
    } else {
        return axes;
    }
}

QList<float> PoseNiryo::getAxesDegree()
{
    if(estEnDegree){
        return axes;
    } else {
        return radiantVersDegreeL(axes);
    }
}

QList<quint16> PoseNiryo::getAxesQuint16()
{
    QList<quint16> resultat;
    if(estEnDegree){
        resultat = degreeVersQuint16L(axes);
    } else {
        resultat = radiantVersQuint16L(axes);
    }
    return resultat;
}

bool PoseNiryo::getEstEnDegree()
{
    return estEnDegree;
}

bool PoseNiryo::appliquerLimites()//applique le slimites des axes du niryo ned2
{
    bool resultat = true;

    float max[6] = {2.900,0.600,1.540,2.070,1.910,2.520};// Limites max (en radiant) de chaque axes mesurer avec niryo studio
    float min[6] = {-2.860,-1.820,-1.290,-2.080,-1.910,-2.510};// Limites min (en radiant) de chaque axes mesurer avec niryo studio

    QList<float>temp;

    if(estEnDegree){
        temp = degreeVersRadiantL(axes);
    } else {
        temp = axes;
    }

    for (int i = 0; i < 6; ++i) {
        if(temp.value(i) > max[i]){
            resultat = false;
            temp[i] = max[i];
        } else if(temp.value(i) < min[i]){
            resultat = false;
            temp[i] = min[i];
        }
    }

    if(estEnDegree){
        axes = radiantVersDegreeL(temp);
    } else {
        axes = temp;
    }



    return resultat;
}

QList<float> PoseNiryo::degreeVersRadiantL(QList<float> f)
{
    QList<float> resultat;

    for (int i = 0; i < 6; ++i) {
        resultat.append(degreeVersRadiant(f.value(i)));
    }

    return resultat;
}

QList<float> PoseNiryo::radiantVersDegreeL(QList<float> f)
{
    QList<float> resultat;

    for (int i = 0; i < 6; ++i) {
        resultat.append(radiantVersDegree(f.value(i)));
    }

    return resultat;
}

QList<quint16> PoseNiryo::radiantVersQuint16L(QList<float> f)
{
    QList<quint16> resultat;

    for (int i = 0; i < 6; ++i) {
        resultat.append(radiantVersQuint16(f.value(i)));
    }

    return resultat;
}

QList<quint16> PoseNiryo::degreeVersQuint16L(QList<float> f)
{
    QList<quint16> resultat;

    for (int i = 0; i < 6; ++i) {
        resultat.append(radiantVersQuint16(degreeVersRadiantL(f).value(i)));
    }

    return resultat;
}

float PoseNiryo::degreeVersRadiant(float f)
{
    f = (f*(M_PI/180));
    return f;
}

float PoseNiryo::radiantVersDegree(float f)
{
    f = (f*(180/M_PI));
    return f;
}

quint16 PoseNiryo::radiantVersQuint16(float f)
{
    quint16 resultat = 0;
    f = f*1000;
    if(f < 0){
        resultat = (1 << 15) + (((quint16)-f) & 0x7fff);
    } else {
        resultat = (((quint16)f) & 0x7fff);
    }
    return resultat;
}

float PoseNiryo::quint16VersRadiant(quint16 _axerobot)
{
    float resultat = -1;
    if ((_axerobot >> 15) == 1){
        resultat = 0-(float)(_axerobot & 0x7fff);
    } else {
        resultat = (float)(_axerobot & 0x7fff);
    }
    resultat = resultat / 1000;
    return resultat;
}
