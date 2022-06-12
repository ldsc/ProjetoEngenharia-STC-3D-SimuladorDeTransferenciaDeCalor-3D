#include "CMaterialCorrelacao.h"

CMaterialCorrelacao::CMaterialCorrelacao(std::string fileName){
    std::string str_temp;
    int r, g, b, alpha;
    name = fileName;

    QDir dir; std::string path = dir.absolutePath().toStdString();

    std::ifstream file(path+"/materiais//"+fileName);
    if (file.is_open()){
        file >> str_temp; file >> r; file >> g; file >> b; file >> alpha;
        color = QColor(r, g, b, alpha);
        file >> str_temp; file >> cp;
        file >> str_temp; file >> rho;
        file >> str_temp; file >> str_temp; /// texto explicando a conta
        file >> str_temp; file >> C0_k;   file >> C1_k;   file >> C2_k;
    }
    else {
        std::cout<<"can't open file!" << std::endl;
    }
}

double CMaterialCorrelacao::getThermalConst(double T) {
    double k   = C0_k   + C1_k   * T + C2_k  * T * T;
    return rho * cp/k;
}

double CMaterialCorrelacao::getK(double T) {
    double k = C0_k   + C1_k   * T + C2_k  * T * T;
    return k<0 ? C0_k : k;
}
