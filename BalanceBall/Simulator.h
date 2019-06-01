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

	void update(bool force);
	void resetSimulation();
	void onKeyPressed(char keyCode);

	std::shared_ptr<sf::Shape> getBallShape();
	std::shared_ptr<sf::Shape> getSeesawShape();

	bool isRunning;
	Seesaw& getSeesaw(); // todo remove
	Ball& getBall(); // todo remove

	sf::Vector2f calcGuidedBallPosition(); // todo make private
private:
	const sf::Vector2f gravity{ 0, 9.81f }; // positive, because of draw-coordinate system
	Ball ball;
	Seesaw seesaw;
	PID pidController;

	sf::Vector2u currentScreenSize;
	bool isControllerEnabled;

	void pushBallLeft();
	void pushBallRight();
	sf::Vector2f calcAccelerationOfBall(bool includeGravity);
	bool isBallOnSeesaw();
};

