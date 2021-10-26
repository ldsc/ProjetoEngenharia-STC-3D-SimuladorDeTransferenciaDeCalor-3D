#ifndef CMATERIALCORRELACAO_H
#define CMATERIALCORRELACAO_H

#include <iostream>
#include <fstream>
#include <string>
#include <QColor>

#include "CMaterial.h"

class CMaterialCorrelacao:public CMaterial {
public:
    CMaterialCorrelacao(std::string fileName);
    double getThermalConst(double T);

    QColor getColor()       { return color; }
    std::string getName()   { return name; }

protected:
    std::string name;
    QColor color;

    double C0_rho, C1_rho;
    double C0_cp, C1_cp, C2_cp;
    double C0_k, C1_k, C2_k;
};
#endif
