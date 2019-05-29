#include "Simulator.h"
#include <iostream>
#include <math.h>

const float PI = 3.141592653589793238463; // todo

Simulator::Simulator(sf::Vector2u screenSize) :
	currentScreenSize{ screenSize },
	ball{ screenSize },
	seesaw{ screenSize, 45, 45 / 2 },
	isRunning{ true },
	pidController{}
{
}

void Simulator::update()
{
	if (this->isRunning) {

		sf::Vector2f ballVelocity = this->calcAccelerationOfBall();
		std::cout << "ball force: " << ballVelocity.x << "\n";
		this->ball.applyForce(ballVelocity);

		// update angle of seesaw
		float newAngle = this->pidController.calculateAngle(this->ball.getPosition().x, this->currentScreenSize.x / 2);
		if (newAngle != 0)
			this->seesaw.changeAngle(newAngle);

		// update Y position of ball
		this->ball.setYPosition(this->calcBallYPosition());

		std::cout << this->seesaw;
		std::cout << this->ball;
		this->ball.update();
		//this->seesaw.update(); // unused

		if (this->ball.isOutOfBounds(this->currentScreenSize)) {
			std::cout << "ERROR, ball out of bounds\n";
			this->isRunning = false;
		}
	}
}

float calcBallYPosition() {
	// use seesaw vector as geradengleichung
	// then input the x and get the y of this line
	// subtract the width/2 of seesaw and ball radius from that
}

sf::Vector2f Simulator::calcAccelerationOfBall() {
	float ballAccelerationMagnitude = gravity.y * sin(this->seesaw.getAngle()*PI / 180);
	return sf::Vector2f{
		ballAccelerationMagnitude * cos(this->seesaw.getAngle()*PI / 180),
		//ballAccelerationMagnitude*sin(this->seesaw.getAngle()*PI / 180) // not used
		0
	};
}

void Simulator::resetSimulation()
{
	this->ball.reset(this->currentScreenSize);
	this->seesaw.reset(this->currentScreenSize);
	this->pidController.reset();
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



