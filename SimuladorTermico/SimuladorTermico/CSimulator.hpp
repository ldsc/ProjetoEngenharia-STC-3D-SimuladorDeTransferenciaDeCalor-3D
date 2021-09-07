#ifndef CSIMULATOR_HPP
#define CSIMULATOR_HPP

#include "CThermal.hpp"
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

	CThermal thermal;
	double constTermal = thermal.constante() * delta_x / delta_t;
	double constTermal2 = delta_x / (delta_t * thermal.difusividadeTermica());

	double actual_time = 0.0;
	int positionStudy = 0;
	int gridStudy = 0;
	std::vector<double> temperatureStudy;
	std::vector<double> timeStudy;

public:
	std::vector<CGrid*> grid;
public:
	/// --------- FUNCOES DE CRIACAO ---------
	CSimulator(){}

	CSimulator(CThermal _thermal, double _delta_x, double _delta_t, double temperature_i);

	void resetSize(int width, int height);
	void resetGrid();

	/// --------- FUNCOES DO SOLVER ---------
	void run();
	void run(int g);
	void solverByGrid(int g);
	void calculatePointIteration(int  x, int y, int g);
	void updateActualTime();

	/// --------- FUNCOES PARA ESTUDO ---------
	void saveStudy();
	void studyPosition(sf::Vector2i pos, int _gridStudy);
	void plot();


	/// --------- FUNCOES SET ---------
	void set_ActualTemperature(double newTemperature);
	void plusDelta_t() { delta_t += 0.5; }
	void minusDelta_t() { delta_t += 0.5;}
	void changeParallel() { parallel = parallel ? false : true; }

	/// --------- FUNCOES GET ---------
	int getNGRIDS() { return NGRIDS; }
	bool getParallel() { return parallel; }
	double maxTemp();
	double minTemp();
	double get_ActualTemperature() { return thermal.actualTemperature; }

	double getTmax() { return thermal.Tmax; }
	double getTmin() { return thermal.Tmin; }

	double get_delta_t() { return delta_t; }
	double get_time() { return actual_time; }

	std::vector<double> getTemperatureStudy() { return temperatureStudy; }
	std::vector<double> getTimeStudy() { return timeStudy; }
};
#endif