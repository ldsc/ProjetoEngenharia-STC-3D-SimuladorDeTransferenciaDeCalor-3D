#include <iostream>
#include "CWindow.hpp"

int main() {
	CWindow window(400, 400);
	// 1 px = 0.26 mm = 2.6*10.0e-4
	window.Run();
	 
	return 0;
}