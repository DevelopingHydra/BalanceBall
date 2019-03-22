#pragma once

#include <SFML/Graphics.hpp>

class GUI
{
public:
	GUI();
	~GUI();

	void show();

private:
	sf::RenderWindow window;
	void initialize();
	void renderLoop();
};
