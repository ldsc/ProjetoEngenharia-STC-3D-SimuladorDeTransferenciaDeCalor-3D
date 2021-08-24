#include "CSimulator.hpp"

CSimulator::CSimulator(CThermal _thermal, double _delta_x, double _delta_t, double temperature_i) {
	thermal.cp = _thermal.cp;
	thermal.k = _thermal.k;
	thermal.rho = _thermal.rho;
	thermal.ti = _thermal.ti;
	delta_x = _delta_x;
	delta_t = _delta_t;
}

void CSimulator::resetSize(int width, int height) {
	grid.resetSize( width, height, thermal.ti);
}

void CSimulator::run() {
	double erro = 1;
	int iter = 0;
	grid.startIteration();
	while (erro > MIN_ERRO && iter <= MAX_ITERATION) {
		grid.updateIteration();
		for (int i = 0; i < grid.getWidth(); i++)
			for (int k = 0; k < grid.getHeight(); k++)
				calculateIteration(i,k);
		erro = grid.maxErroIteration();
		iter++;
		std::cout << "Time: " << std::setw(5) << actual_time << " seg - " << std::setw(2) << iter << " iteracoes - " << erro << " erro" << "\r";
	}
	// std::cout << "iteration: " << iter - 1 << " - erro: " << erro << std::endl;
	grid.updateSolver();
	saveStudy();
}

void CSimulator::saveStudy() {
	temperatureStudy.push_back(grid[positionStudy]->temp_nup1);
	actual_time += delta_t;
	timeStudy.push_back(actual_time);
}
void CSimulator::calculateIteration(int x, int y) {
	if (!grid(x,y)->active)
		return;
	float n = 0;
	double inf = .0, sup = .0, esq = .0, dir = .0;

	if (y - 1 > 0) {
		if (grid(x, y - 1)->active)
			n++;
		inf = grid(x, y - 1)->temp_nup1;
	}

	if (y + 1 < grid.getHeight()) {
		if (grid(x, y + 1)->active)
			n++;
		sup = grid(x, y + 1)->temp_nu;
	}

	if (x - 1 > 0) {
		if (grid(x - 1, y)->active)
			n++;
		esq = grid(x - 1, y)->temp_nup1;
	}

	if (x + 1 < grid.getWidth()) {
		if (grid(x + 1, y)->active)
			n++;
		dir = grid(x + 1, y)->temp_nu;
	}

	grid(x, y)->temp_nup1 = (constTermal * grid(x, y)->temp + inf + sup + esq + dir) / (n + constTermal);
}

void CSimulator::studyPosition(sf::Vector2i pos) {
	actual_time = 0.0;
	temperatureStudy.clear();
	timeStudy.clear();
	positionStudy = (int)pos.x + (int)pos.y * grid.getWidth();
	std::cout << "posicao " << positionStudy << " - " << pos.x << " / " << pos.y << std::endl;
}

void CSimulator::plot() {
	std::vector<double> sw;
	std::vector<double> fw;
	std::string name;
	int n = 100;

	name = ("Temperature_versus_time");

	std::ofstream outdata; //save data
	outdata.open((name + ".dat").c_str());
	outdata << "# time Temperature " << std::endl;
	for (int i = 0; i < temperatureStudy.size(); i++) 
		outdata << timeStudy[i] << " " << temperatureStudy[i] << std::endl;
	
	CGnuplot::plot((name + ".dat").c_str(), "time", "temperature", (name + ".png").c_str());
}

void CSimulator::set_ActualTemperature(double newTemperature) {
	if (newTemperature > thermal.Tmax)
		thermal.Tmax = newTemperature;
	if (newTemperature < thermal.Tmin)
		thermal.Tmin = newTemperature;
	thermal.actualTemperature = newTemperature;
}