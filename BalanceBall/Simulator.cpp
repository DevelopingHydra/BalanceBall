#include "Simulator.h"
#include <iostream>

Simulator::Simulator(sf::Vector2u screenSize)
	:currentScreenSize{ screenSize },
	ball{ screenSize },
	seesaw{ screenSize, 45, 10 },
	isRunning{ true },
	pidController{}
{
}

Simulator::~Simulator()
{
}

void Simulator::update()
{
	if (this->isRunning) {

		sf::Vector2f ballVelocity = sf::Vector2f{
			gravity.y * sin(this->seesaw.getAngle()) * (-1),
			//gravity.y * cos(this->seesaw.angle)
			0
		};
		std::cout << "ball force: " << ballVelocity.x << "\n";
		this->ball.applyForce(ballVelocity);

		float newAngle = this->pidController.calculateAngle(this->ball.getPosition().x, 800 / 2); // todo width
		if (newAngle != 0)
			this->seesaw.changeAngle(newAngle);

		std::cout << this->seesaw;
		std::cout << this->ball;
		this->ball.update();
		//this->seesaw.update();

		if (this->ball.isOutOfBounds(this->currentScreenSize)) {
			std::cout << "ERROR, ball out of bounds\n";
			this->isRunning = false;
		}
	}
}

void Simulator::resetSimulation()
{
	this->ball.reset(this->currentScreenSize);
	this->seesaw.reset(this->currentScreenSize);
	this->isRunning = true;
	std::cout << "Resetting simulation\n";
}

void Simulator::onKeyPressed(char keyCode)
{
	switch (keyCode) {
	case 17: // 'r'
		this->resetSimulation();
		break;
	case 72: // arrow right
		this->pushBallRight();
		break;
	case 71: // arrow left
		this->pushBallLeft();
		break;
	case 73:
		this->seesaw.changeAngle(10);
		break;
	case 74:
		this->seesaw.changeAngle(-10);
		break;
	default:
		std::cout << "!!! unrecognized key code!\n";
	}
}

std::shared_ptr<sf::Shape> Simulator::getBall()
{
	return this->ball.getShape();
}

std::shared_ptr<sf::Shape> Simulator::getSeesaw()
{
	return this->seesaw.getShape();
}

void Simulator::pushBallLeft()
{
	this->ball.applyForce({ -5,0 });
	std::cout << "push ball left\n";
}

void Simulator::pushBallRight()
{
	this->ball.applyForce({ 5,0 });
	std::cout << "push ball right\n";
}



