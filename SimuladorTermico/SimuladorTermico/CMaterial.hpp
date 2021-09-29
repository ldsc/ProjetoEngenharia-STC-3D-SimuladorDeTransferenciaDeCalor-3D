#ifndef	CMATERIAL_HPP
#define CMATERIAL_HPP
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class CMaterial {
public:
	CMaterial() {}
	CMaterial(double _cp, double _k, double _rho, sf::Color _color, std::string _name) : cp{ _cp }, k{ _k }, rho{ _rho }, color{ _color }, name{ _name } { }
	double getThermalConst(){ return rho * cp / k; }
	sf::Color getColor() { return color; }
	std::string getName() { return name; };

	double thermalConst;
	std::string name;
	//void startThermal() { thermalConst = rho * cp / k; }
	double cp, k, rho;
	sf::Color color;
};
#endif
