#include "Simulator.h"
#include <iostream>

Simulator::Simulator(sf::Vector2u screenSize)
	:currentScreenSize{ screenSize }, ball{ screenSize }
{
}

Simulator::~Simulator()
{
}

void Simulator::onWindowResized(sf::Vector2u newScreenSize)
{
	this->ball.onScreenResized(this->currentScreenSize, newScreenSize);

	this->currentScreenSize = newScreenSize;
}

void Simulator::update()
{
	//this->ball.applyForce(gravity);

	this->ball.update();
}

void Simulator::resetSimulation()
{
	this->ball.reset(this->currentScreenSize);
	std::cout << "Resetting simulation\n";
}

void Simulator::onKeyPressed(char keyCode)
{
	switch (keyCode) {
	case 17:
		this->resetSimulation();
		break;
	case 72:
		this->pushBallRight();
		break;
	case 71:
		this->pushBallLeft();
		break;
	default:
		std::cout << "!!! unrecognized key code!\n";
	}
}

sf::CircleShape Simulator::getBall()
{
	return this->ball.getShape();
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



