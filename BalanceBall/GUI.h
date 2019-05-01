#pragma once

#include <SFML/Graphics.hpp>
#include "Simulator.h"

class GUI
{
public:
	GUI();
	~GUI();

	void show();

private:
	sf::RenderWindow window;
	Simulator simulator;

	const int targetFramerate = 30;

	void renderLoop();
	void renderAllOjbects();
};
