#include "CSimuladorTemperatura.h"

void CSimuladorTemperatura::resetSize(int width, int height) {
    grid.resize(NGRIDS);
    this->width = width;
    this->height = height;
    for (int i = 0; i < NGRIDS; i++)
        grid[i] = new CGrid(width, height, 0.0);
}

void CSimuladorTemperatura::resetGrid() {
    for (int i = 0; i < NGRIDS; i++)
        grid[i]->resetGrid(0.0);
}

void CSimuladorTemperatura::createListOfMaterials() {
    ///*
    std::string matName;
    QDirIterator it(dir.absolutePath()+"//materiais", {"*.txt"}, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        matName = it.fileName().toStdString();
        materiais[matName] = chooseMaterialType(matName);
    }
    for(auto const& imap: materiais)
        name_materiais.push_back(imap.first);
}

CMaterial* CSimuladorTemperatura::chooseMaterialType(std::string name){
    std::ifstream file(dir.absolutePath().toStdString()+"/materiais//"+name);

    std::string type;
    std::getline(file, type);
    file.close();
    if (type == "correlacao")
        return new CMaterialCorrelacao(name);
    else
        return new CMaterialInterpolacao(name);
}

void CSimuladorTemperatura::addGrid(){
    NGRIDS++;
    grid.push_back(new CGrid(width, height, 0.0));
}

void CSimuladorTemperatura::delGrid(int _grid){
    NGRIDS--;
    grid.erase(grid.begin()+_grid);
}

std::string CSimuladorTemperatura::openMaterial(std::string nameFile){
    std::ifstream file(nameFile);

    std::string type;
    std::string name;
    std::getline(file, type);
    std::getline(file, name);
    std::cout<<name<<std::endl;

    file.close();
    if (type == "correlacao")
        materiais[name] = new CMaterialCorrelacao(nameFile);
    else
        materiais[name] = new CMaterialInterpolacao(nameFile);
    name_materiais.push_back(name);
    return name;
}


void CSimuladorTemperatura::run_sem_paralelismo() {
    for (int g = 0; g < NGRIDS; g++){
        grid[g]->startIteration();
        solverByGrid(g);
    }
}

void CSimuladorTemperatura::run_paralelismo_por_grid() {
    omp_set_num_threads(NGRIDS);
    #pragma omp parallel
    {
        grid[omp_get_thread_num()]->startIteration();
        solverByGrid(omp_get_thread_num());
    }
}

void CSimuladorTemperatura::run_paralelismo_total() {
    for (int g=0;g<NGRIDS;g++)
        grid[g]->startIteration();

    omp_set_num_threads(MAX_THREADS);
    #pragma omp parallel
    {
    solverByThread(omp_get_thread_num());
    }
    for (int g = 0; g < NGRIDS; g++)
        grid[g]->updateSolver();
}

void CSimuladorTemperatura::solverByGrid(int g) {
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

void CSimuladorTemperatura::solverByThread(int thread_num) {
    double erro = 1, _erro;
    int iter = 0;
    int x, y;
    while (erro > MIN_ERRO && iter <= MAX_ITERATION) {
        for (int g = 0; g < NGRIDS; g++) {
            for (int i = thread_num; i < grid[g]->getSize(); i+=MAX_THREADS) {
                x = i % grid[g]->getWidth();
                y = i / grid[g]->getWidth();

                (*grid[g])(x, y)->temp_nu = (*grid[g])(x, y)->temp_nup1;
                _erro = calculatePointIteration(x, y, g);
                erro = erro < _erro ? _erro : erro;
            }
        }
        iter++;
    }
}

double CSimuladorTemperatura::calculatePointIteration(int x, int y, int g) {
    if (!(*grid[g])(x,y)->active)
        return 0.0;
    if ((*grid[g])(x, y)->source)
        return 0.0;
    float n_x = 0;
    float n_z = 0;
    double inf = .0, sup = .0, esq = .0, dir = .0, cima = .0, baixo =.0;
    double thermalConstant;

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
            cima = (*grid[g + 1])(x, y)->temp_nup1*delta_x;
        }
    }

    if (g > 0) {
        if (grid[g - 1]->operator()(x, y)->active) {
            n_z++;
            baixo = (*grid[g - 1])(x, y)->temp_nup1 * delta_x;
        }
    }

    thermalConstant = (*grid[g])(x, y)->material->getThermalConst((*grid[g])(x, y)->temp_nup1);

    (*grid[g])(x, y)->temp_nup1 = (thermalConstant * (*grid[g])(x, y)->temp*delta_x*delta_z/delta_t + inf + sup + esq + dir + cima + baixo) / (n_x*delta_z + n_z*delta_x + thermalConstant *delta_x*delta_z/delta_t);
    return (*grid[g])(x, y)->temp_nup1 - (*grid[g])(x, y)->temp_nu;
}

std::string CSimuladorTemperatura::saveGrid(std::string nameFile) {
    std::ofstream file(nameFile);
    int sizeGrid = grid[0]->getSize();
    file << NGRIDS <<"\n";
    for (int g = 0; g < NGRIDS; g++) {
        for (int i = 0; i < sizeGrid; i++) {
            if((*grid[g])[i]->active){
                file << i << " " << g << " ";
                file << (*grid[g])[i]->temp << " ";
                file << (*grid[g])[i]->active << " ";
                file << (*grid[g])[i]->source << " ";
                file << (*grid[g])[i]->material->getName() << "\n";
            }
        }
    }
    file.close();
    return "Arquivo salvo!";
}

std::string CSimuladorTemperatura::openGrid(std::string nameFile) {

    std::ifstream file(nameFile);

    std::string _name;
    int i, g;
    double _temperature;
    int _active, _source;
    std::string _strGrids;
    std::getline(file, _strGrids);

    NGRIDS = std::stoi(_strGrids);
    grid.resize(NGRIDS);
    for(int gg = 0; gg<NGRIDS; gg++)
        grid[gg] = new CGrid(width, height, 0.0);
    while(file >> i >> g >> _temperature >> _active >> _source >> _name){
            grid[g]->draw(i, _temperature, _active, _source, _name);
    }

    file.close();
    return "Arquivo carregado!";
}

void CSimuladorTemperatura::setActualTemperature(double newTemperature) {
    if (newTemperature > Tmax)
        Tmax = newTemperature;
    if (newTemperature < Tmin)
        Tmin = newTemperature;
    actualTemperature = newTemperature;
}

void CSimuladorTemperatura::changeMaterialPropertiesStatus() {
    materialPropertiesStatus = materialPropertiesStatus ? false : true;
}

double CSimuladorTemperatura::getProps(double temperature, std::string material){
    return materiais[material]->getThermalConst(temperature);
}

QColor CSimuladorTemperatura::getColor(std::string material){
    return materiais[material]->getColor();
}

double CSimuladorTemperatura::maxTemp() {
    double maxErro = 0;
    double tempErro = 0;
    for (int i = 0; i < NGRIDS; i++) {
        tempErro = grid[i]->maxTemp();
        maxErro = maxErro < tempErro ? tempErro : maxErro;
    }
    return maxErro;
}

double CSimuladorTemperatura::minTemp() {
    double minErro = 0;
    double tempErro = 0;
    for (int i = 0; i < NGRIDS; i++) {
        tempErro = grid[i]->minTemp();
        minErro = minErro > tempErro ? tempErro : minErro;
    }
    return minErro;
}
