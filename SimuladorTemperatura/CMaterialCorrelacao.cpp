#include "CMaterialCorrelacao.h"

CMaterialCorrelacao::CMaterialCorrelacao(std::string fileName){
    std::string strTemporaria;
    int r, g, b, alpha;

    std::ifstream file("C://Users//nicholas//Desktop//ProjetoEngenharia//Projeto-TCC-SimuladorDifusaoTermica//SimuladorTemperatura//materiais//"+fileName);
    if (file.is_open()){
        std::getline(file, name);

        file >> r; file >> g; file >> b; file >> alpha;
        color = QColor(r, g, b, alpha);

        file >> C0_rho; file >> C1_rho;
        file >> C0_cp;  file >> C1_cp;  file >> C2_cp;
        file >> C0_k;   file >> C1_k;   file >> C2_k;
    }
    else{
        std::cout<<"can't open file!" << std::endl;
    }
}

double CMaterialCorrelacao::getThermalConst(double T) {
    double rho = C0_rho - C1_rho * (T-298);
    double cp  = C0_cp  + C1_cp  * T - C2_cp * T * T;
    double k   = C0_k   + C1_k   * T + C2_k  * T * T;
    return rho * cp / k;
}
