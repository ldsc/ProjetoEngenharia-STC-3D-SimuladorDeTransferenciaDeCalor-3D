#include "CGrid.h"

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
        grid[i].active = false;
        grid[i].source = false;
        grid[i].temp = temperature;
        grid[i].temp_nup1 = temperature;
        grid[i].material = new CMaterial("ar");
    }
}

void CGrid::draw_rec(int x, int y, double size, double _temperature, bool isSourceActive, CMaterial* _material, bool eraser) {
    int start_x = (x - size / 2 >= 0) ? x - size / 2 : 0;
    int start_y = (y - size / 2 >= 0) ? y - size / 2 : 0;
    int max_x   = (x + size / 2 >= width)  ? width  : x - size/2 + size;
    int max_y   = (y + size / 2 >= height) ? height : y - size/2 + size;
    double temperatura = eraser?0:_temperature;

    for (int i = start_x; i < max_x; i++){
        for (int k = start_y; k < max_y; k++) {
            grid[k * width + i].active = !eraser;
            grid[k * width + i].temp = temperatura;
            grid[k * width + i].source = isSourceActive;
            grid[k * width + i].material = _material;
        }
    }
}

void CGrid::draw_cir(int x, int y, double radius, double _temperature, bool isSourceActive, CMaterial* _material, bool eraser) {
    /// vou montar um quadrado, e analisar se o cada ponto dessa regiao faz parte do circulo
    int start_x = (x - (int)radius >= 0) ? ((int)x - (int)radius) : 0;
    int start_y = (y - (int)radius >= 0) ? ((int)y - (int)radius) : 0;
    int max_x   = (x + (int)radius >= width)  ? width  : ((int)x + (int)radius);
    int max_y   = (y + (int)radius >= height) ? height : ((int)y + (int)radius);
    double temperatura = eraser?0:_temperature;

    for (int i = start_x; i < max_x; i++) {
        for (int k = start_y; k < max_y; k++) {
            if (((i*1.0 - x) * (i*1.0 - x) + (k*1.0 - y) * (k*1.0 - y)) < radius * radius) {
                grid[k * width + i].active = !eraser;
                grid[k * width + i].temp = temperatura;
                grid[k * width + i].source = isSourceActive;
                grid[k * width + i].material = _material;
            }
        }
    }
}

void CGrid::draw(int x, double _temperature, bool active, bool isSource, std::string _material) {
    grid[x].temp = _temperature;
    grid[x].active = active;
    grid[x].source = isSource;
    if (active)
        grid[x].material = new CMaterialCorrelacao(_material+".txt");
    else
        grid[x].material = new CMaterial("ar");
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
