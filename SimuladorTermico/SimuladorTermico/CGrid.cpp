#include "CGrid.hpp"

void CGrid::printGrid() {
	for (int i = 0; i < width; i++) {
		for (int k = 0; k < height; k++)
			std::cout << grid[k * width + i].temp << "  ";
		std::cout << std::endl;
	}
}

void CGrid::resetSize(int _width, int _height, double temperature) {
	width = _width;
	height = _height;
	grid.resize(width * height);
	for (int i = 0; i < width * height; i++)
		grid[i].temp = temperature;
}

void CGrid::resetGrid(double temperature) {
	for (int i = 0; i < width * height; i++) {
		grid[i].active = false;
		grid[i].temp = temperature;
		grid[i].temp_nup1 = temperature;
	}
}

void CGrid::draw(sf::Vector2f pos, sf::Vector2f size, double _temperature, bool isSourceActive, CMaterial *_material) {

	int start_x = (pos.x >= 0) ? ((int)pos.x) : 0;
	int start_y = (pos.y >= 0) ? ((int)pos.y) : 0;
	int max_x = ((pos.x + (int)size.x) >= width) ? width : ((int)pos.x + (int)size.x);
	int max_y = ((pos.y + (int)size.y) >= height) ? height : ((int)pos.y + (int)size.y);

	for (int i = start_x; i < max_x; i++){
		for (int k = start_y; k < max_y; k++) {
			grid[k * width + i].active = true;
			grid[k * width + i].temp = _temperature;
			grid[k * width + i].source = isSourceActive;
			grid[k * width + i].material = _material;
		}
	}
}

void CGrid::updateIteration() {
	for (int i = 0; i < width * height; i++)
		grid[i].temp_nu = grid[i].temp_nup1;
}

void CGrid::updateSolver() {
	for (int i = 0; i < width * height; i++)
		grid[i].temp = grid[i].temp_nup1;
}

double CGrid::maxErroIteration() {
	double erro = 0.0;
	double erro_posicao = 0.0;
	for (int i = 0; i < width * height; i++) {
		erro_posicao = grid[i].temp_nup1 - grid[i].temp_nu;
		erro = abs(erro_posicao) > erro ? erro_posicao : erro;
	}
	return erro;
}

void CGrid::startIteration() {
	for (int i = 0; i < width * height; i++)
		grid[i].temp_nup1 = grid[i].temp;
}

double CGrid::maxTemp() {
	double maxTemp = 0;
	for (int i = 0; i < width * height; i++)
		maxTemp = maxTemp < grid[i].temp ? grid[i].temp : maxTemp;
	return maxTemp;
}

double CGrid::minTemp() {
	double minTemp = 1000000;
	for (int i = 0; i < width * height; i++)
		minTemp = minTemp > grid[i].temp ? grid[i].temp : minTemp;
	return minTemp;
}