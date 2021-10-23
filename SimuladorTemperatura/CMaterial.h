#ifndef	CMATERIAL_HPP
#define CMATERIAL_HPP
#include <iostream>
#include <string>
#include <QColor>

class CMaterial {
public:
    CMaterial(std::string _name) : name{ _name } { }
    double getThermalConst();
    double getThermalConst(double T);

    QColor getColor();
    static QColor getColor(std::string _name);
    static std::vector<std::string> getMateriais();
    std::string getName() { return name; }
    void setName(std::string _name) { name = _name; }

private:
    std::string name;
};
#endif
