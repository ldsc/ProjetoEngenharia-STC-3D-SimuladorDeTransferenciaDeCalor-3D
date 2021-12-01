#ifndef CSIMULADORTEMPERATURA_H
#define CSIMULADORTEMPERATURA_H

#include <map>
#include <QDir>
#include <omp.h>
#include <QPoint>
#include <fstream>
#include <iomanip>
#include "CMaterial.h"
#include <QDirIterator>

#include "CGrid.h"
#include "CMaterialCorrelacao.h"
#include "CMaterialInterpolacao.h"

class CSimuladorTemperatura {
private:
    //int parallel = 0;
    QDir dir;
    int MAX_THREADS = omp_get_max_threads()-1;
    int width, height;
    bool materialPropertiesStatus = true;
    int NGRIDS = 1;
    const double MIN_ERRO = 1.0e-1;
    const int MAX_ITERATION = 39;
    double delta_x = 2.6e-4, delta_t = 5.0e-1, delta_z = 0.5;

    double Tmax = 1000, Tmin = 300;

    double actualTemperature = 300;
    double actual_time = 0.0;
    std::map<std::string, CMaterial*> materiais;
    std::vector<std::string> name_materiais;

public:
    std::vector<CGrid*> grid;
public:
    /// --------- FUNCOES DE CRIACAO ---------
    CSimuladorTemperatura() { createListOfMaterials();	}

    void resetSize(int width, int height);
    void resetGrid();

    void createListOfMaterials();
    CMaterial* chooseMaterialType(std::string name);

    void addGrid();
    void delGrid(int _grid);

    /// --------- FUNCOES DO SOLVER ---------
    void run_sem_paralelismo();
    void run_paralelismo_por_grid();
    void run_paralelismo_total();
    void solverByGrid(int g);
    void solverByThread(int thread_num);
    double calculatePointIteration(int  x, int y, int g);

    std::string saveGrid(std::string nameFile);
    std::string openGrid(std::string nameFile);
    std::string openMaterial(std::string nameFile);

    /// --------- FUNCOES SET ---------
    void setActualTemperature(double newTemperature);
    void changeMaterialPropertiesStatus();
    void setDelta_t(double _delta_t) { delta_t = _delta_t; }
    void setDelta_x(double _delta_x) { delta_x = _delta_x; }
    void setDelta_z(double _delta_z) { delta_z = _delta_z; }

    /// --------- FUNCOES GET ---------
    double getProps(double temperature, std::string material);
    QColor getColor(std::string material);
    int getNGRIDS() { return NGRIDS; }
    bool getMaterialStatus() { return materialPropertiesStatus; }
    double maxTemp();
    double minTemp();
    double get_ActualTemperature() { return actualTemperature; }

    double getTmax() { return Tmax; }
    double getTmin() { return Tmin; }

    double getDelta_t() { return delta_t; }
    double getDelta_x() { return delta_x; }
    double getDelta_z() { return delta_z; }
    double getTime() { return actual_time; }

    CMaterial* getMaterial(std::string mat) { return materiais[mat]; }

    std::vector<std::string> getMateriais() { return name_materiais; }
};
#endif
