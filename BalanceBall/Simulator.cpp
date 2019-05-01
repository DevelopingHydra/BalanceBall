#include "Simulator.h"
#include <iostream>

Simulator::Simulator(sf::Vector2u screenSize)
	:currentScreenSize{ screenSize }, ball{ screenSize }, seesaw{ screenSize, 45 }, isRunning{ true }
{
}

Simulator::~Simulator()
{
}

void Simulator::update()
{
	if (this->isRunning) {
		std::cout << this->seesaw;
		std::cout << this->ball;

		//this->ball.applyForce(gravity);

		this->ball.update();

		if (this->ball.isOutOfBounce(this->currentScreenSize)) {
			std::cout << "ERROR, ball out of bounce\n";
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



