#include "CMaterial.h"

std::vector<std::string> CMaterial::getMateriais() {
    std::vector<std::string> materiais(5);
    materiais[0] = "aluminum";
    materiais[1] = "cooper";
    materiais[2] = "iron";
    materiais[3] = "magnesium";
    materiais[4] = "nickel";
    return materiais;
}

double CMaterial::getThermalConst(double T) {
    double rho=0, cp=0, k=0;
    if (name == "aluminum") {
        rho = 2.753 - 0.000223 * (T - 298);
        k = 76.64 + 0.2633 * T - 2 * T * T * 1.0e-4;
        cp = 0.7473 + 2 * T * 1.0e-4 + 5 * T * T * 1.0e-7;
    }
    else if (name == "cooper") {
        rho = 7.262 - 0.000486 * (T - 298);
        k = 7.925 + 0.1375 - 6 * T * T * 1.0e-5;
        cp = 0.353 + 3 * T * 1.0e-4 - T * T * 1.0e-7;
    }
    else if (name == "iron") {
        rho = 8.02 - 0.000501 * (T - 298);
        k = 10.33 + 15.4 * T / 1000 - 7 * T * T * 1.0e-7;
        cp = 0.593 + 4.8 * T * 1.0e-5;
    }
    else if (name == "magnesium") {
        rho = 1.8 - 0.000143 * (T - 298);
        k = 156;
        cp = 1.88 - 5.22 * T * 1.0e-4;
    }
    else if (name == "nickel") {
        rho = 8.7 - 0.000458 * (T - 298);
        k = 27.2;
        cp = 0.675;
    }
    return rho * cp / k;
}

double CMaterial::getThermalConst() {
    double rho = 0, cp = 0, k = 0;
    if (name == "aluminum") {
        rho = 2.753;
        k = 76.64;
        cp = 0.7473;
    }
    else if (name == "cooper") {
        rho = 7.262;
        k = 0.0001;
        cp = 0.353;
    }
    else if (name == "iron") {
        rho = 8.02;
        k = 10.33;
        cp = 0.593;
    }
    else if (name == "magnesium") {
        rho = 1.8;
        k = 156;
        cp = 1.88;
    }
    else if (name == "nickel") {
        rho = 8.7;
        k = 27.2;
        cp = 0.675;
    }
    return rho * cp / k;
}

QColor CMaterial::getColor() {
    return getColor(name);
}

QColor CMaterial::getColor(std::string _name) {
    if (_name == "aluminum")
        return QColor(236, 217, 122, 255);
    else if (_name == "cooper")
        return QColor(255, 128, 0, 255);
    else if (_name == "iron")
        return QColor(55, 55, 55, 255);
    else if (_name == "magnesium")
        return QColor(200, 200, 200, 255);
    else if (_name == "nickel")
        return QColor(150, 150, 255, 255);
    else
        return QColor(255, 255, 255, 255);
}
