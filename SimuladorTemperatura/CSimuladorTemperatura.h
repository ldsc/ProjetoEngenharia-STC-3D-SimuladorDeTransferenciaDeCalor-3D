#ifndef CSIMULADORTEMPERATURA_H
#define CSIMULADORTEMPERATURA_H

#include "CGrid.h"
#include <fstream>
#include <iomanip>
#include <QPoint>
#include "CMaterial.h"
#include <math.h>
#include <omp.h>

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
    int positionStudy = 0;
    int gridStudy = 0;
    std::string actualMaterial;
    std::vector<double> temperatureStudy = { 0 };
    std::vector<double> timeStudy = { 0 };
    std::vector<std::string> materiais;
    QPoint positionStudyVector = QPoint(0,0);

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
    void updateActualTime();

    /// --------- FUNCOES PARA ESTUDO ---------
    void saveStudy();
    void studyPosition(int x, int y, int _gridStudy);
    void plot();
    void replot();
    double getLastTimeStudy();
    double getLastTemperatureStudy();

    void saveGrid(std::string nameFile);
    void openGrid(std::string nameFile);

    /// --------- FUNCOES SET ---------
    void set_ActualTemperature(double newTemperature);
    void changeMaterialPropertiesStatus();
    void plusDelta_t() { delta_t += 0.5; }
    void minusDelta_t() { delta_t += 0.5;}
    void changeParallel() { parallel = parallel + 1 > 2 ? 0 : parallel + 1; }

    /// --------- FUNCOES GET ---------
    int getNGRIDS() { return NGRIDS; }
    int getStudyGrid() { return gridStudy; }
    int getParallel() { return parallel; }
    bool getMaterialStatus() { return materialPropertiesStatus; }
    double maxTemp();
    double minTemp();
    double get_ActualTemperature() { return actualTemperature; }

    double getTmax() { return Tmax; }
    double getTmin() { return Tmin; }

    double get_delta_t() { return delta_t; }
    double get_time() { return actual_time; }

    QPoint getPositionStudyVector() { return positionStudyVector; }

    std::string getActualMaterial() { return actualMaterial; }

    std::vector<double> getTemperatureStudy() { return temperatureStudy; }
    std::vector<double> getTimeStudy() { return timeStudy; }
    std::vector<std::string> getMateriais() { return materiais; }
};
#endif
