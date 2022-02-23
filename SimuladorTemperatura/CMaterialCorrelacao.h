#ifndef CMATERIALCORRELACAO_H
#define CMATERIALCORRELACAO_H

#include <QDir>
#include <string>
#include <QColor>
#include <fstream>
#include <iostream>

#include "CMaterial.h"

class CMaterialCorrelacao:public CMaterial {
public:
    CMaterialCorrelacao(std::string fileName);
    double getThermalConst(double T);
    double getK(double T);
    double getCp() {return rho;}
    double getRho() {return cp;}

    QColor getColor()       { return color; }
    std::string getName()   { return name; }

protected:
    std::string name;
    QColor color;

    double rho;
    double cp;
    double C0_k, C1_k, C2_k;
};
#endif
