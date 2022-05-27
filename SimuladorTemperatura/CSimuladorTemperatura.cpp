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
    QDirIterator it(dir.absolutePath()+"//materiais", {"*.correlacao", "*.constante", "*.interpolacao"}, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        matName = it.fileName().toStdString();
        QFileInfo fi(it.fileName());
        std::string type = fi.suffix().toStdString();
        materiais[matName] = chooseMaterialType(matName, type);
    }
    for(auto const& imap: materiais)
        name_materiais.push_back(imap.first);
}

CMaterial* CSimuladorTemperatura::chooseMaterialType(std::string name, std::string type){
    std::ifstream file(dir.absolutePath().toStdString()+"/materiais//"+name);

    if (type == "correlacao" || type == "constante")
        return new CMaterialCorrelacao(name);
    else if (type == "interpolacao")
        return new CMaterialInterpolacao(name);
    else  // COLOQUEI ESTE ELSE PARA COMPLETAR AS POSSIBILIDADES E ELIMINAR MSG WARNING
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

void CSimuladorTemperatura::openMaterial(QString nameFile){
    QFileInfo fi(nameFile);

    std::string matName = fi.fileName().toStdString();
    std::string type = fi.suffix().toStdString();

    materiais[matName] = chooseMaterialType(matName, type);
    name_materiais.push_back(matName);
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
    double erro, _erro;
    int iter = 0;
    while (iter <= MAX_ITERATION) {
        erro = 0.0;
        grid[g]->updateIteration(); /// atualizo temp_nu para calcular o erro da iteracao
        for (int i = 0; i < grid[g]->getWidth(); i++)
            for (int k = 0; k < grid[g]->getHeight(); k++)
                calculatePointIteration(i, k, g);
        _erro = grid[g]->maxErroIteration();
        erro = erro < _erro ? _erro : erro;
        iter++;
        if (erro < MIN_ERRO && iter >= MIN_ITERATION)
            break;
    }
    grid[g]->updateSolver();
}

void CSimuladorTemperatura::solverByThread(int thread_num) {
    double erro, _erro;
    int iter = 0;
    int x, y;
    do {
        erro = 0.0;
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
        if (erro < MIN_ERRO && iter >= MIN_ITERATION)
            break;
    } while (iter < MAX_ITERATION);
    std::cout<<"iteracoes: " << iter << " - erro: " << erro << std::endl;
}

double CSimuladorTemperatura::calculatePointIteration(int x, int y, int g) {
    if (!(*grid[g])(x,y)->active)
        return 0.0;
    if ((*grid[g])(x, y)->source)
        return 0.0;

    float T_esq = .0, T_dir = .0, T_sup = .0, T_inf = .0, T_cim = .0, T_bai = .0;
    float k_esq = .0, k_dir = .0, k_sup = .0, k_inf = .0, k_cim = .0, k_bai = .0;
    float C1, C2;

    float k1;
    float k2 = (*grid[g])(x, y)->material->getK((*grid[g])(x, y)->temp_nup1);

    float temp_iter_anterior = (*grid[g])(x, y)->temp_nup1;
    if (y - 1 > 0) {
        if ((*grid[g])(x, y - 1)->active) {
            k1 = (*grid[g])(x, y - 1)->material->getK((*grid[g])(x, y - 1)->temp_nup1);
            k_inf = 2*k1*k2/(k1+k2);
            T_inf = (*grid[g])(x, y - 1)->temp_nup1;
        }
    }

    if (y + 1 < grid[g]->getHeight()) {
        if ((*grid[g])(x, y + 1)->active) {
            k1 = (*grid[g])(x, y + 1)->material->getK((*grid[g])(x, y + 1)->temp_nup1);
            k_sup = 2*k1*k2/(k1+k2);
            T_sup = (*grid[g])(x, y + 1)->temp_nup1;
        }
    }

    if (x - 1 > 0) {
        if ((*grid[g])(x - 1, y)->active) {
            k1 = (*grid[g])(x - 1, y)->material->getK((*grid[g])(x - 1, y)->temp_nup1);
            k_esq = 2*k1*k2/(k1+k2);
            T_esq = (*grid[g])(x - 1, y)->temp_nup1;
        }
    }

    if (x + 1 < grid[g]->getWidth()) {
        if ((*grid[g])(x + 1, y)->active) {
            k1 = (*grid[g])(x + 1, y)->material->getK((*grid[g])(x + 1, y)->temp_nup1);
            k_dir = 2*k1*k2/(k1+k2);
            T_dir = (*grid[g])(x + 1, y)->temp_nup1;
        }
    }

    if ( g < NGRIDS-1) {
        if (grid[g + 1]->operator()(x, y)->active) {
            k1 = (*grid[g + 1])(x, y)->material->getK((*grid[g + 1])(x, y)->temp_nup1);
            k_cim = 2*k1*k2/(k1+k2);
            T_cim = (*grid[g + 1])(x, y)->temp_nup1;
        }
    }

    if (g > 0) {
        if (grid[g - 1]->operator()(x, y)->active) {
            k1 = (*grid[g - 1])(x, y)->material->getK((*grid[g - 1])(x, y)->temp_nup1);
            k_bai = 2*k1*k2/(k1+k2);
            T_bai = (*grid[g - 1])(x, y)->temp_nup1;
        }
    }

    C2 = (delta_z*delta_z*delta_x*delta_x/delta_t) * (*grid[g])(x, y)->material->getCp() * (*grid[g])(x, y)->material->getRho();
    C1 = 1/(C2 + delta_z*delta_z*(k_esq+k_dir) + delta_z*delta_z*(k_sup+k_inf) + delta_x*delta_x*(k_cim+k_bai));
    (*grid[g])(x, y)->temp_nup1 = C1*(C2*(*grid[g])(x, y)->temp + delta_z*delta_z*(k_esq*T_esq+k_dir*T_dir) + delta_z*delta_z*(k_sup*T_sup+k_inf*T_inf) + delta_x*delta_x*(k_cim*T_cim+k_bai*T_bai));

    return abs((*grid[g])(x, y)->temp_nup1 - temp_iter_anterior);
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
            Tmax = Tmax < _temperature ? _temperature : Tmax;
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
