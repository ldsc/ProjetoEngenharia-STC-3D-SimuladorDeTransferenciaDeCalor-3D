#ifndef CGNUPLOT_HPP
#define CGNUPLOT_HPP

#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#define GNUPLOT_NAME "C:\\Program\" \"Files\\gnuplot\\bin\\gnuplot -p"
#else 
#define GNUPLOT_NAME "gnuplot"
#endif

class CGnuplot {
private:
	FILE* pipe;
public:
	void plot(std::string name, std::string xlabel, std::string ylabel, std::string saveName);
	void replot(std::string name);
	void semilog(std::string name, std::string xlabel, std::string ylabel, std::string saveName);
};
#endif