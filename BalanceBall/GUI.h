#pragma once

#include <SFML/Graphics.hpp>
#include "Simulator.h"

class GUI
{
public:
	GUI();

	void show();

private:
	sf::RenderWindow window;
	Simulator simulator;

	sf::Font robotoFont;
	sf::Text infoText;
	sf::Text pauseText;

	const int targetFramerate = 30;

	void renderLoop();
	void renderAllOjbects();
};
