#ifndef CMATERIALINTERPOLACAO_H
#define CMATERIALINTERPOLACAO_H

#include <QDir>
#include <string>
#include <vector>
#include "CMaterial.h"
#include "CSegmentoReta.h"

class CMaterialInterpolacao :public CMaterial {
public:
    CMaterialInterpolacao();
    CMaterialInterpolacao(std::string _name);

    double getThermalConst(double T);
    double getK(double T);
    double getCp() {return cp;}
    double getRho() {return rho;}

    QColor getColor()       { return color; }
    std::string getName()   { return name; }
protected:
    std::string name;
    QColor color;

private:
    std::vector<CSegmentoReta> retaInterpolacao;
    double rho, cp;
    double xmin, xmax, edx;

};

#endif // CMATERIALINTERPOLACAO_H
