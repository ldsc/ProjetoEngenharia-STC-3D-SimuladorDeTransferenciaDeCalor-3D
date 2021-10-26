#ifndef CSIMULADORTEMPERATURA_H
#define CSIMULADORTEMPERATURA_H

#include "CGrid.h"
#include <fstream>
#include <iomanip>
#include <QPoint>
#include "CMaterial.h"
#include <map>
#include <omp.h>
#include "CMaterialCorrelacao.h"

class CSimuladorTemperatura {
private:
    int parallel = 0;
    int MAX_THREADS = omp_get_max_threads()-1;
    bool materialPropertiesStatus = true;
    int NGRIDS = 4;
    const double MIN_ERRO = 1.0e-1;
    const int MAX_ITERATION = 39;
    double delta_x = 2.6e-4, delta_t = 5.0e-1;
    double delta_z = 0.5;

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

    /// --------- FUNCOES DO SOLVER ---------
    void run_sem_paralelismo();
    void run_paralelismo_por_grid();
    void run_paralelismo_total();
    void solverByGrid(int g);
    void solverByThread(int thread_num);
    double calculatePointIteration(int  x, int y, int g);

    void saveGrid(std::string nameFile);
    void openGrid(std::string nameFile);

    /// --------- FUNCOES SET ---------
    void setActualTemperature(double newTemperature);
    void changeMaterialPropertiesStatus();
    void plusDelta_t() { delta_t += 0.5; }
    void minusDelta_t() { delta_t += 0.5;}
    void changeParallel() { parallel = parallel + 1 > 2 ? 0 : parallel + 1; }

    /// --------- FUNCOES GET ---------
    int getNGRIDS() { return NGRIDS; }
    int getParallel() { return parallel; }
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
