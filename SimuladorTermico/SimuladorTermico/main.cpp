#include "CWindow.hpp"
#include <iostream>
#include <omp.h>
// 1 px = 0.26 mm = 2.6*10.0e-4

int main() {
	CWindow window(300, 300);
	window.Run();

	return 0;
}