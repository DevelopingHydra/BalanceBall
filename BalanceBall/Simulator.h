#pragma once

#include "SFML\Graphics.hpp"
#include <memory>

#include "Ball.h"

class Simulator
{
public:
	Simulator(sf::Vector2u screenSize);
	~Simulator();

	void onWindowResized(sf::Vector2u newScreenSize);
	void update();
	void resetSimulation();
	void onKeyPressed(char keyCode);

	std::vector<std::shared_ptr<sf::Shape>> getShapes();

private:
	std::vector<std::shared_ptr<sf::Shape>> drawables;

	const sf::Vector2f gravity{ 0, -9.81f };
	Ball ball;

	sf::Vector2u currentScreenSize;

	void pushBallLeft();
	void pushBallRight();
};

