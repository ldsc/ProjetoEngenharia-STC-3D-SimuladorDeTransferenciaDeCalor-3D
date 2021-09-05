#ifndef CSIMULATOR_HPP
#define CSIMULATOR_HPP

#include "CThermal.hpp"
#include "CGrid.hpp"
#include "CGnuplot.hpp"
#include <fstream>
#include <iomanip>


class CSimulator {
private:
	int NGRIDS = 4;
	const double MIN_ERRO = 1.0e-1;
	const int MAX_ITERATION = 9;
	double delta_x = 2.6e-4, delta_t = 1.0e-0;
	CThermal thermal;
	double constTermal = thermal.constante() * delta_x / delta_t;
	double constTermal2 = delta_x / (delta_t * thermal.difusividadeTermica());

	double actual_time = 0.0;
	int positionStudy = 0;
	int gridStudy = 0;
	std::vector<double> temperatureStudy;
	std::vector<double> timeStudy;

	void calculateIteration(int  x, int y, int g);
public:
	std::vector<CGrid*> grid;
public:
	CSimulator(){}

	CSimulator(CThermal _thermal, double _delta_x, double _delta_t, double temperature_i);

	void resetSize(int width, int height);
	void resetGrid();
	void run();
	void solverByGrid(int g);
	void studyPosition(sf::Vector2i pos, int _gridStudy);

	std::vector<double> getTemperatureStudy() { return temperatureStudy; }
	std::vector<double> getTimeStudy() { return timeStudy; }

	double maxTemp();
	double minTemp();

	void saveStudy();
	void plot();

	double get_ActualTemperature() { return thermal.actualTemperature; }
	void set_ActualTemperature(double newTemperature);


	double getTmax() { return thermal.Tmax; }
	double getTmin() { return thermal.Tmin; }

	void plusDelta_t() { delta_t += 0.5; }
	void minusDelta_t() { delta_t += 0.5; }

	double get_delta_t() { return delta_t; }

	double get_time() { return actual_time; }

};
#endif