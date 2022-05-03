Sugestões de mudanças  código:

1)
A classe CMaterial pode ser apenas de interface, virtual e pura;
Teria de retirar de lá os atributos name e color
e mover para herdeira CMaterialInterpolacao.
Até porque você criou
    std::string name;
    QColor color;
    de novo dentro da classe herdeira!

Exemplo:
class CMaterial {
public:
    CMaterial() = default;
    virtual double getThermalConst(double T) = 0;
    virtual double getK(double T) = 0;
    virtual double getCp() = 0;
    virtual double getRho() = 0;
    virtual QColor getColor()   = 0;
    virtual std::string getName()   = 0;
};
Na prática não poderá criar um objeto CMaterial, apenas CMaterialInterpolacao.
Ou ponteiro para CMaterial.

2) CSimuladorTemperatura.cpp correção a ser feita
tem if...else if.. mas não contempla todas as POSSIBILIDADES, de não for o if nem o else como fica?
CMaterial* CSimuladorTemperatura::chooseMaterialType(std::string name, std::string type){
    std::ifstream file(dir.absolutePath().toStdString()+"/materiais//"+name);

    if (type == "correlacao" || type == "constante")
        return new CMaterialCorrelacao(name);
    else if (type == "interpolacao")
        return new CMaterialInterpolacao(name);
    else  // COLOQUEI ESTE ELSE PARA COMPLETAR AS POSSIBILIDADES E ELIMINAR MSG WARNING
        return new CMaterialInterpolacao(name);
}

3) Criar um arquivo INSTALL com todas as instruções para compilar e instalar.
Instruções para instalar a biblioteca Qt, o Qt creator, a classe QCustomPlot e QPdfWriter.


