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
	grid.resize(NGRIDS);
	for (int i = 0; i < NGRIDS; i++)
		grid[i] = new CGrid(width, height, thermal.ti);
}

void CSimulator::resetGrid() { 
	for (int i = 0; i < NGRIDS; i++)
		grid[i]->resetGrid(thermal.ti); 
}

void CSimulator::run() {
	double erro = 1;
	int iter = 0;
	int tid;
	for (int i = 0; i < NGRIDS; i++)
		grid[i]->startIteration();

	double start_time = std::time(0);
	omp_set_num_threads(NGRIDS);
	#pragma omp parallel private(tid)
	{
		tid = omp_get_thread_num();
		std::cout << "tid: " << tid << std::endl;
		solverByGrid(tid);
	}
	saveStudy();

	std::cout << "Time: " << std::setw(5) << actual_time << " - duracao: " << std::time(0) - start_time << " seg" << "\r";
}

void CSimulator::solverByGrid(int g) {
	double erro = 1;
	int iter = 0;
	while (erro > MIN_ERRO && iter <= MAX_ITERATION) {
		grid[g]->updateIteration(); /// atualizo temp_nu para calcular o erro da iteracao
		for (int i = 0; i < grid[g]->getWidth(); i++)
			for (int k = 0; k < grid[g]->getHeight(); k++)
				calculatePointIteration(i, k, g);
		erro = grid[g]->maxErroIteration();
		iter++;
	}
	grid[g]->updateSolver();
}

void CSimulator::calculatePointIteration(int x, int y, int g) {
	if (!grid[g]->operator()(x,y)->active)
		return; 
	if (grid[g]->operator()(x, y)->source)
		return;
	float n = 0;
	double inf = .0, sup = .0, esq = .0, dir = .0, cima = .0, baixo =.0;

	if (y - 1 > 0) {
		if (grid[g]->operator()(x, y - 1)->active) {
			n++;
			inf = grid[g]->operator()(x, y - 1)->temp_nup1;
		}
	}

	if (y + 1 < grid[g]->getHeight()) {
		if (grid[g]->operator()(x, y + 1)->active) {
			n++;
			sup = grid[g]->operator()(x, y + 1)->temp_nup1;
		}
	}

	if (x - 1 > 0) {
		if (grid[g]->operator()(x - 1, y)->active) {
			n++;
			esq = grid[g]->operator()(x - 1, y)->temp_nup1;
		}
	}

	if (x + 1 < grid[g]->getWidth()) {
		if (grid[g]->operator()(x + 1, y)->active) {
			n++;
			dir = grid[g]->operator()(x + 1, y)->temp_nup1;
		}
	}

	if ( g < NGRIDS-1) {
		if (grid[g + 1]->operator()(x, y)->active) {
			n++;
			cima = grid[g + 1]->operator()(x, y)->temp_nup1;
		}
	}

	if (g > 0) {
		if (grid[g - 1]->operator()(x, y)->active) {
			n++;
			baixo = grid[g - 1]->operator()(x, y)->temp_nup1;
		}
	}

	grid[g]->operator()(x, y)->temp_nup1 = (constTermal * grid[g]->operator()(x, y)->temp + inf + sup + esq + dir + cima + baixo) / (n + constTermal);
}

void CSimulator::saveStudy() {
	temperatureStudy.push_back(grid[gridStudy]->getTemp(positionStudy));
	actual_time += delta_t;
	timeStudy.push_back(actual_time);
}

void CSimulator::studyPosition(sf::Vector2i pos, int _gridStudy) {
	actual_time = 0.0;
	gridStudy = _gridStudy;
	temperatureStudy.clear();
	timeStudy.clear();
	positionStudy = (int)pos.x + (int)pos.y * grid[gridStudy]->getWidth();
	std::cout << "posicao " << positionStudy << " - " << pos.x << " / " << pos.y << std::endl;
}

void CSimulator::plot() {
	std::vector<double> sw;
	std::vector<double> fw;
	std::string name;
	int n = 100;

	name = "Temperature_versus_time";

	std::ofstream outdata; //save data
	outdata.open((name + ".dat").c_str());
	outdata << "# time Temperature " << std::endl;
	for (int i = 0; i < temperatureStudy.size(); i++)
		outdata << timeStudy[i] << " " << temperatureStudy[i] << std::endl;

	CGnuplot grafico;
	grafico.plot(name+".dat", "time", "temperature", name);
}

void CSimulator::set_ActualTemperature(double newTemperature) {
	if (newTemperature > thermal.Tmax)
		thermal.Tmax = newTemperature;
	if (newTemperature < thermal.Tmin)
		thermal.Tmin = newTemperature;
	thermal.actualTemperature = newTemperature;
}

double CSimulator::maxTemp() {
	double maxErro = 0;
	double tempErro = 0;
	for (int i = 0; i < NGRIDS; i++) {
		tempErro = grid[i]->maxTemp();
		maxErro = maxErro < tempErro ? tempErro : maxErro;
	}
	return maxErro;
}

double CSimulator::minTemp() {
	double minErro = 0;
	double tempErro = 0;
	for (int i = 0; i < NGRIDS; i++) {
		tempErro = grid[i]->minTemp();
		minErro = minErro > tempErro ? tempErro : minErro;
	}
	return minErro;
}