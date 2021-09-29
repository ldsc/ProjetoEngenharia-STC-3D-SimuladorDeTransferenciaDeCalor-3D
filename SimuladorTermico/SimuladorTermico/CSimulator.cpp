#include "CSimulator.hpp"

CSimulator::CSimulator( double _delta_x, double _delta_t, double temperature_i) {
	delta_x = _delta_x;
	delta_t = _delta_t;
	createListOfMaterials(); 
	grafico = new CGnuplot;
}

void CSimulator::resetSize(int width, int height) {
	grid.resize(NGRIDS);
	for (int i = 0; i < NGRIDS; i++)
		grid[i] = new CGrid(width, height, 0.0);
}

void CSimulator::resetGrid() {
	for (int i = 0; i < NGRIDS; i++)
		grid[i]->resetGrid(0.0); 
}

void CSimulator::createListOfMaterials() {
	materiais.resize(4);
	materiais[0] = new CMaterial(0.897, 230, 2.800, sf::Color(100, 12, 50, 255), "aluminio");
	materiais[1] = new CMaterial(0.385, 200, 9.000, sf::Color(12, 155, 10, 255), "cooper");
	materiais[2] = new CMaterial(2.060, 0.61, 1.000, sf::Color(100, 100, 100, 255), "air");
	materiais[3] = new CMaterial(0.001, 0.026, 0.0012, sf::Color(0, 0, 255, 255), "water");
}

void CSimulator::run() {
	for (int g = 0; g < NGRIDS; g++)
		run(g);
	plot();
}

void CSimulator::run(int g) {
	grid[g]->startIteration();

	solverByGrid(g);
	if (g == gridStudy)
		saveStudy();
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
	if (!(*grid[g])(x,y)->active)
		return; 
	if ((*grid[g])(x, y)->source)
		return;
	float n_x = 0;
	float n_z = 0;
	double inf = .0, sup = .0, esq = .0, dir = .0, cima = .0, baixo =.0;

	if (y - 1 > 0) {
		if ((*grid[g])(x, y - 1)->active) {
			n_x++;
			inf = (*grid[g])(x, y - 1)->temp_nup1*delta_z;
		}
	}

	if (y + 1 < grid[g]->getHeight()) {
		if ((*grid[g])(x, y + 1)->active) {
			n_x++;
			sup = (*grid[g])(x, y + 1)->temp_nup1 * delta_z;
		}
	}

	if (x - 1 > 0) {
		if ((*grid[g])(x - 1, y)->active) {
			n_x++;
			esq = (*grid[g])(x - 1, y)->temp_nup1 * delta_z;
		}
	}

	if (x + 1 < grid[g]->getWidth()) {
		if ((*grid[g])(x + 1, y)->active) {
			n_x++;
			dir = (*grid[g])(x + 1, y)->temp_nup1 * delta_z;
		}
	}

	if ( g < NGRIDS-1) {
		if (grid[g + 1]->operator()(x, y)->active) {
			n_z++;
			cima = grid[g + 1]->operator()(x, y)->temp_nup1*delta_x;
		}
	}

	if (g > 0) {
		if (grid[g - 1]->operator()(x, y)->active) {
			n_z++;
			baixo = grid[g - 1]->operator()(x, y)->temp_nup1 * delta_x;
		}
	}

	(*grid[g])(x, y)->temp_nup1 = ((*grid[g])(x, y)->material->getThermalConst() * (*grid[g])(x, y)->temp*delta_x*delta_z/delta_t + inf + sup + esq + dir + cima + baixo) / (n_x*delta_z + n_z*delta_x + (*grid[g])(x, y)->material->getThermalConst()*delta_x*delta_z/delta_t);
}

void CSimulator::saveStudy() {
	temperatureStudy.push_back(grid[gridStudy]->getTemp(positionStudy));
}

void CSimulator::updateActualTime() {
	actual_time += delta_t;
	timeStudy.push_back(actual_time);
}

void CSimulator::changeRightMaterial() {
	actualMaterial++;
	if (actualMaterial == materiais.size())
		actualMaterial = 0;
}

void CSimulator::changeLeftMaterial() {
	actualMaterial--;
	if (actualMaterial == 0)
		actualMaterial = materiais.size()-1;
}

void CSimulator::studyPosition(sf::Vector2i pos, int _gridStudy) {
	actual_time = 0.0;
	gridStudy = _gridStudy;
	temperatureStudy.clear();
	timeStudy.clear();
	positionStudyVector = (sf::Vector2f)pos;
	positionStudy = (int)pos.x + (int)pos.y * grid[gridStudy]->getWidth();
	std::cout << "posicao " << positionStudy << " - " << pos.x << " / " << pos.y << std::endl;
}

void CSimulator::plot() {
	std::string name = "Temperature_versus_time";

	std::ofstream outdata; //save data
	outdata.open((name + ".dat").c_str());
	outdata << "# time Temperature " << std::endl;
	for (int i = 0; i < temperatureStudy.size(); i++)
		outdata << timeStudy[i] << " " << temperatureStudy[i] << std::endl;

	
	grafico->plot(name+".dat", "time", "temperature", name);
}

void CSimulator::replot() {
	std::string name = "Temperature_versus_time";

	std::ofstream outdata; //save data
	outdata.open((name + ".dat").c_str());
	outdata << "# time Temperature " << std::endl;
	for (int i = 0; i < temperatureStudy.size(); i++)
		outdata << timeStudy[i] << " " << temperatureStudy[i] << std::endl;

	grafico->replot(name + ".dat");
}

void CSimulator::set_ActualTemperature(double newTemperature) {
	if (newTemperature > Tmax)
		Tmax = newTemperature;
	if (newTemperature < Tmin)
		Tmin = newTemperature;
	actualTemperature = newTemperature;
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