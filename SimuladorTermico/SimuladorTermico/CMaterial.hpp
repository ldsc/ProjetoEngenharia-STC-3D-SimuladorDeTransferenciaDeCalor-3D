#ifndef	CMATERIAL_HPP
#define CMATERIAL_HPP
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class CMaterial {
public:
	CMaterial(std::string _name) : name{ _name } { }
	double getThermalConst();
	double getThermalConst(double T);

	sf::Color getColor();// { return color; }
	std::string getName() { return name; }
	void setName(std::string _name) { name = _name; }

private:
	std::string name;
};
#endif
