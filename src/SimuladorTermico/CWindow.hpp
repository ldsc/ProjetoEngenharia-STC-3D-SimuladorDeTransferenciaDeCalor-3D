#ifndef CWINDOW_HPP
#define CWINDOW_HPP

#include <SFML/Graphics.hpp>
#include "CSimulator.hpp"
#include <iostream>
#include <windows.h>

class CWindow {
public:
	CWindow( int _width, int _height);
	void Run();
	void printStudy();

private: // variables
	int height, width;
	sf::RenderWindow window;
	sf::RenderTexture canvas;
	sf::Sprite sprite;
	CSimulator simulation;
	bool runningSimulator = false;

private: // functions
	sf::Vector2f case_LShift(sf::Vector2f recSize);
	sf::Vector2f case_LCtrl(sf::Vector2f recSize);
	sf::Color getRGB(double temp);

	void printMenu(sf::Vector2f recSize);
};

#endif