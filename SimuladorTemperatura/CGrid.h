#ifndef CGRID_HPP
#define CGRID_HPP

#include <vector>
#include <string>
#include "CCell.h"
#include <iostream>

class CGrid {
private:
    int width, height;
    std::vector<CCell> grid;
public:
    CGrid() {
        width = 0;
        height = 0;
    }

    CGrid(int _width, int _height) : width{_width}, height{_height}{
        grid.resize(width * height);
    }
    CGrid(int _width, int _height, double temperature) {
        resetSize(_width, _height, temperature);
    }
    void resetGrid(double temperature);

    void printGrid();
    void resetSize(int _width, int _height, double temperature);

    void draw_rec(int x, int y, double size, double temperature, bool isSourceActive, std::string _material);
    void draw_cir(int x, int y, double size, double temperature, bool isSourceActive, std::string _material);
    void draw(int x, double temperature, bool active, bool isSource, std::string _material);

    int getSize() { return width * height; }

    void updateIteration();
    void updateSolver();
    void startIteration();

    int getWidth() { return width;}
    int getHeight() { return height; }
    double maxErroIteration();

    double getTemp(int position) { return grid[position].temp_nup1; }

    void update_Temp_nup1(int x, int y, double temp) { grid[x + y * width].temp_nup1 = temp; }

    double maxTemp();
    double minTemp();

    bool isActive(int x){ return grid[x].active;}

    CCell* operator () (int x, int y) { return &grid[y * width + x]; }
    CCell* operator [] (int x) { return &grid[x]; }

};
#endif
