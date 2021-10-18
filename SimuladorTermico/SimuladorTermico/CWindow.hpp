#ifndef CWINDOW_HPP
#define CWINDOW_HPP

#include <SFML/Graphics.hpp>
#include "CSimulator.hpp"
#include <iostream>
#include <windows.h>
#include <string>
#include <omp.h>

class CWindow {
public:
	CWindow(int _width, int _height);
	void Run();
	void printStudy();

private: // variables

	int mat = 0;
	int height, width;
	int distance_of_draws = 10;
	sf::RenderWindow window;
	sf::RenderTexture canvas;
	sf::Sprite sprite;
	CSimulator simulation;
	sf::Vector2i studyCoordinates;

	bool runningSimulator = false;
	bool isSourceActive = false;
	int currentGrid = 0;

private: // functions
	sf::Vector2f case_LShift(sf::Vector2f recSize);
	sf::Vector2f case_LCtrl(sf::Vector2f recSize);
	sf::Color getRGB(double temp);

	void printMenu(sf::Vector2f recSize);
	void paint();
	void paintStudyPoint();
};

#endif