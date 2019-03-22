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

	void renderLoop();
	void renderAllOjbects();
};
