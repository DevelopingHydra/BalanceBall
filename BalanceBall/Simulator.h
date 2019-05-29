#pragma once

#include "SFML\Graphics.hpp"
#include <memory>

#include "Ball.h"
#include "Seesaw.h"
#include "PID.h"

class Simulator
{
public:
	Simulator(sf::Vector2u screenSize);
	~Simulator();

	void onWindowResized(sf::Vector2u newScreenSize);
	void update();
	void resetSimulation();
	void onKeyPressed(char keyCode);

	std::shared_ptr<sf::Shape> getBall();
	std::shared_ptr<sf::Shape> getSeesaw();
private:
	const sf::Vector2f gravity{ 0, 9.81f }; // positive, because of draw-coordinate system
	Ball ball;
	Seesaw seesaw;
	PID pidController;

	sf::Vector2u currentScreenSize;
	bool isRunning;

	void pushBallLeft();
	void pushBallRight();
};

