#ifndef	CMATERIAL_HPP
#define CMATERIAL_HPP
#include <iostream>
#include <string>
#include <QColor>

class CMaterial {
public:
    CMaterial(){}
    CMaterial(std::string _name) {name = _name;}
    virtual double getThermalConst(double T) {return 0.0*T;}

    virtual QColor getColor()       { return QColor(0,0,0); }
    virtual std::string getName()   { return name; }

protected:
    std::string name;
    QColor color;
};
#endif
