#ifndef CGRID_HPP
#define CGRID_HPP

#include <vector>
#include "CCell.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

class CGrid {
public:
	CGrid() {
		width = 0;
		height = 0;
	}

	CGrid(int _width, int _height) : width{_width}, height{_height}{
		grid.resize(width * height);
	}

	CCell* operator () (int x, int y) { return &grid[y * width + x]; }
	CCell* operator [] (int x) { return &grid[x]; }
	void resetGrid(double temperature);
	
	void printGrid();
	void resetSize(int _width, int _height, double temperature);

	void draw(sf::Vector2f pos, sf::Vector2f size, double temperature);
	int getSize() { return width * height; }

	void updateIteration();
	void updateSolver();
	void startIteration();

	int getWidth() { return width;}
	int getHeight() { return height; }
	double maxErroIteration();

	void update_Temp_nup1(int x, int y, double temp) { grid[x + y * width].temp_nup1 = temp; }

	double maxTemp();

private:
	int width, height;
	std::vector<CCell> grid;

};
#endif