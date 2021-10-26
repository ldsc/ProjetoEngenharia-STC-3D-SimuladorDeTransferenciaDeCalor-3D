#ifndef	CMATERIAL_HPP
#define CMATERIAL_HPP
#include <iostream>
#include <string>
#include <QColor>

class CMaterial {
public:
    CMaterial(std::string _name) {name = _name;}
    virtual double getThermalConst(double T) {return 0.0;}

    virtual QColor getColor()       { return QColor(0,0,0); }
    virtual std::string getName()   { return name; }

protected:
    std::string name;
    QColor color;

    double C0_rho, C1_rho;
    double C0_cp, C1_cp, C2_cp;
    double C0_k, C1_k, C2_k;
};
#endif
