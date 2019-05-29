#include "Simulator.h"
#include <iostream>
#define _USE_MATH_DEFINES 
#include <math.h>

#include "Line.h"

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
		bool isBallAboveSeesaw = this->isBallOnSeesaw();

		sf::Vector2f ballVelocity = this->calcAccelerationOfBall(isBallAboveSeesaw);
		std::cout << "ball force: " << ballVelocity.x << std::endl;
		this->ball.applyForce(ballVelocity);

		if (isBallAboveSeesaw) {
			float newAngle = this->pidController.calculateAngle(this->ball.getPosition().x, this->currentScreenSize.x / 2);
			if (newAngle != 0)
				this->seesaw.changeAngle(newAngle);

			// update Y position of ball, because the ball is definitely on the seesaw
			this->ball.setYPosition(this->calcBallYPosition());
		}

		std::cout << this->seesaw;
		std::cout << this->ball;
		this->ball.update();
		//this->seesaw.update(); // unused

		if (this->ball.isOutOfBounds(this->currentScreenSize)) {
			std::cout << "ERROR, ball out of bounds" << std::endl;
			this->isRunning = false;
		}
	}
}

float Simulator::calcBallYPosition() {
	Line ballVertical = Line{
		sf::Vector2f{this->ball.getPosition().x, 0.0f},
		sf::Vector2f{this->ball.getPosition().x, (float)this->currentScreenSize.y}
	};

	Line seesawParallel = this->seesaw.getCenterLine();

	sf::Vector2f intersection = seesawParallel.cross(ballVertical);
	//intersection.y -= this->ball.getRadius() + this->seesaw.getShape()->getLocalBounds().height *sin(this->seesaw.getAngle()*M_PI / 180);

	std::cout << "--> intersection point: [" << intersection.x << ", " << intersection.y << "]" << std::endl;

	return intersection.y;
}

bool Simulator::isBallOnSeesaw()
{
	Line seesawParallel = this->seesaw.getCenterLine();

	return this->ball.getPosition().x > seesawParallel.getPointA().x && this->ball.getPosition().x < seesawParallel.getPointB().x;
}

sf::Vector2f Simulator::calcAccelerationOfBall(bool includeGravity) {
	if (this->isBallOnSeesaw()) {
		float ballAccelerationMagnitude = gravity.y * sin(this->seesaw.getAngle()*M_PI / 180);
		return sf::Vector2f{
			ballAccelerationMagnitude * (float)cos(this->seesaw.getAngle()*M_PI / 180),
			0
		};
	}
	else {
		return sf::Vector2f{
			0,
			gravity.y
		};
	}
}

void Simulator::resetSimulation()
{
	this->ball.reset(this->currentScreenSize);
	this->seesaw.reset(this->currentScreenSize);
	this->pidController.reset();
	this->isRunning = true;
	std::cout << "Resetting simulation" << std::endl;
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
		std::cout << "!!! unrecognized key code!" << std::endl;
	}
}

std::shared_ptr<sf::Shape> Simulator::getBallShape()
{
	return this->ball.getShape();
}

std::shared_ptr<sf::Shape> Simulator::getSeesawShape()
{
	return this->seesaw.getShape();
}

Seesaw & Simulator::getSeesaw()
{
	return this->seesaw;
}

void Simulator::pushBallLeft()
{
	this->ball.applyForce({ -5,0 });
	std::cout << "push ball left" << std::endl;
}

void Simulator::pushBallRight()
{
	this->ball.applyForce({ 5,0 });
	std::cout << "push ball right" << std::endl;
}



