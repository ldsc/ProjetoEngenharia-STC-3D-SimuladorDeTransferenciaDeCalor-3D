#ifndef CMATERIALINTERPOLACAO_H
#define CMATERIALINTERPOLACAO_H

#include <QDir>
#include <string>
#include <vector>
#include "CMaterial.h"
#include "CSegmentoReta.h"

// Falta a documentação no código informando as classes, atributos, métodos
// deveria sempre dar algum valor inicial para todos os atributos, pois não estão sendo inicializados!
class CMaterialInterpolacao :public CMaterial {
public:
    CMaterialInterpolacao();
    CMaterialInterpolacao(std::string _name);

    double getThermalConst(double T);
    double getK(double T);
    double getCp() {return cp;}
    double getRho() {return rho;}

    // Pense em criar uma classe CMaterialInterpolacaoInterfaceGrafica, herdeira de CMaterialInterpolacao e que incluiria os atributos e funções associadas a Qt, como getColor;
    // da forma como esta obriga o uso de Qt.
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
