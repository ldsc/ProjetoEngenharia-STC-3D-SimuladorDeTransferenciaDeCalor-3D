#include "CMaterial.hpp"

double CMaterial::getThermalConst(double T) {
	double rho=0, cp=0, k=0;
	if (name == "aluminum") {
		rho = 2.753 - 0.000223 * (T - 298);
		k = 76.64 + 0.2633 * T - 2 * T * T * 1.0e-4;
		cp = 0.7473 + 2 * T * 1.0e-4 + 5 * T * T * 1.0e-7;
	}
	else if (name == "cooper") {
		rho = 7.262 - 0.000486 * (T - 298);
		k = 7.925 + 0.1375 - 6 * T * T * 1.0e-5;
		cp = 0.353 + 3 * T * 1.0e-4 - T * T * 1.0e-7;
	}
	else if (name == "iron") {
		rho = 8.02 - 0.000501 * (T - 298);
		k = 10.33 + 15.4 * T / 1000 - 7 * T * T * 1.0e-7;
		cp = 0.593 + 4.8 * T * 1.0e-5;
	}
	else if (name == "magnesium") {
		rho = 1.8 - 0.000143 * (T - 298);
		k = 156;
		cp = 1.88 - 5.22 * T * 1.0e-4;
	}
	else if (name == "nickel") {
		rho = 8.7 - 0.000458 * (T - 298);
		k = 27.2;
		cp = 0.675;
	}
	return rho * cp / k;
}

double CMaterial::getThermalConst() {
	double rho = 0, cp = 0, k = 0;
	if (name == "aluminum") {
		rho = 2.753;
		k = 76.64;
		cp = 0.7473;
	}
	else if (name == "cooper") {
		rho = 7.262;
		k = 0.0001;
		cp = 0.353;
	}
	else if (name == "iron") {
		rho = 8.02;
		k = 10.33;
		cp = 0.593;
	}
	else if (name == "magnesium") {
		rho = 1.8;
		k = 156;
		cp = 1.88;
	}
	else if (name == "nickel") {
		rho = 8.7;
		k = 27.2;
		cp = 0.675;
	}
	return rho * cp / k;
}

sf::Color CMaterial::getColor() {
	if (name == "aluminum")
		return sf::Color(100, 12, 50, 255);
	else if (name == "cooper")
		return sf::Color(12, 155, 10, 255);
	else if (name == "iron")
		return sf::Color(100, 100, 100, 255);
	else if (name == "magnesium")
		return sf::Color(0, 0, 255, 255);
	else if (name == "nickel")
		return sf::Color(100, 0, 255, 255);
}