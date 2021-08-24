#ifndef CTHERMAL_HPP
#define CTHERMAL_HPP

class CThermal {
public:
	CThermal() {}
	CThermal(double _cp, double _k, double _rho, double _ti) : cp{ _cp }, k{ _k }, rho{ _rho }, ti{ _ti }{}
	double cp = 1, k = 100, rho = 1600, ti = 0.0;
	double Tmax = 1000, Tmin = 300;
	double constante() { return rho * cp / k; }
	double difusividadeTermica() { return 1153 * 10.0e-7; }
	double actualTemperature = 300;
};
#endif