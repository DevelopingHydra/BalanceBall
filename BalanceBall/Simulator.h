#pragma once

#include "SFML\Graphics.hpp"
#include <memory>

#include "Ball.h"

class Simulator
{
public:
	Simulator(unsigned int canvasWidth, unsigned int canvasHeight);
	~Simulator();

	void onWindowResized(unsigned int newWidth, unsigned int newHeight);
	void update();

	std::vector<std::shared_ptr<sf::Shape>> getShapes();

private:
	std::vector<std::shared_ptr<sf::Shape>> drawables;

	Ball ball;

	unsigned int canvasWidth, canvasHeight;
};

