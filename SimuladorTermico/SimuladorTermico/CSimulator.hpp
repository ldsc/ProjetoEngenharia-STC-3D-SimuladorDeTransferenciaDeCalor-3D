#ifndef CSIMULATOR_HPP
#define CSIMULATOR_HPP

#include "CGrid.hpp"
#include "CGnuplot.hpp"
#include <fstream>
#include <iomanip>
#include <omp.h>

class CSimulator {
private:
	bool parallel = true;
	int NGRIDS = 4;
	const double MIN_ERRO = 1.0e-1;
	const int MAX_ITERATION = 39;
	double delta_x = 2.6e-4, delta_t = 1.0e-0;
	double delta_z = 0.5;

	double Tmax = 1000, Tmin = 300;
	double actualTemperature = 300;

	double actual_time = 0.0;
	int positionStudy = 0;
	int gridStudy = 0;
	int actualMaterial = 0;
	std::vector<double> temperatureStudy = { 0 };
	std::vector<double> timeStudy = { 0 };
	std::vector<CMaterial*> materiais;
	sf::Vector2f positionStudyVector = sf::Vector2f(0,0);
	CGnuplot *grafico;

public:
	std::vector<CGrid*> grid;
public:
	/// --------- FUNCOES DE CRIACAO ---------
	CSimulator() { createListOfMaterials(); plot(); grafico = new CGnuplot;	}

	CSimulator( double _delta_x, double _delta_t, double temperature_i);

	void resetSize(int width, int height);
	void resetGrid();

	void createListOfMaterials();

	/// --------- FUNCOES DO SOLVER ---------
	void run();
	void run(int g);
	void solverByGrid(int g);
	void calculatePointIteration(int  x, int y, int g);
	void updateActualTime();
	void changeRightMaterial();
	void changeLeftMaterial();

	/// --------- FUNCOES PARA ESTUDO ---------
	void saveStudy();
	void studyPosition(sf::Vector2i pos, int _gridStudy);
	void plot();
	void replot();


	/// --------- FUNCOES SET ---------
	void set_ActualTemperature(double newTemperature);
	void plusDelta_t() { delta_t += 0.5; }
	void minusDelta_t() { delta_t += 0.5;}
	void changeParallel() { parallel = parallel ? false : true; }

	/// --------- FUNCOES GET ---------
	int getNGRIDS() { return NGRIDS; }
	int getStudyGrid() { return gridStudy; }
	bool getParallel() { return parallel; }
	double maxTemp();
	double minTemp();
	double get_ActualTemperature() { return actualTemperature; }

	double getTmax() { return Tmax; }
	double getTmin() { return Tmin; }

	double get_delta_t() { return delta_t; }
	double get_time() { return actual_time; }

	sf::Vector2f getPositionStudyVector() { return positionStudyVector; }

	CMaterial* getActualMaterial() { return materiais[actualMaterial]; }

	std::vector<double> getTemperatureStudy() { return temperatureStudy; }
	std::vector<double> getTimeStudy() { return timeStudy; }
	std::string getNameMaterial() { return materiais[actualMaterial]->getName(); }
};
#endif