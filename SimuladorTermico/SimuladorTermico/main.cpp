#include "CWindow.hpp"
#include <iostream>
#include <omp.h>
// 1 px = 0.26 mm = 2.6*10.0e-4

int main() {
	std::cout << "Maximo de paralelismo permitido aqui: " << omp_get_max_threads() << std::endl;
	std::cin.get();

	CWindow window(400, 400);
	window.Run();

	return 0;
}