#ifndef	CMATERIAL_HPP
#define CMATERIAL_HPP
#include <iostream>

class CMaterial {
public:
	CMaterial() {}
	CMaterial(double _cp, double _k, double _rho, int _color) : cp{ _cp }, k{ _k }, rho{ _rho }, color{ _color } {startThermal(); } 
	double getThermalConst(){ return rho * cp / k; }
	int getColor() { return color; }

	double thermalConst;

	void startThermal() { thermalConst = rho * cp / k; }
	double cp, k, rho;
	int color;
};
#endif
