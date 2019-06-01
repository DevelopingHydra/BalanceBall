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
	pidController{},
	isControllerEnabled{ true }
{
}

void Simulator::update(bool force = false)
{
	if (this->isRunning || force) {
		bool isBallAboveSeesaw = this->isBallOnSeesaw();

		sf::Vector2f ballVelocity = this->calcAccelerationOfBall(isBallAboveSeesaw);
		std::cout << "ball force: " << ballVelocity.x << std::endl;
		this->ball.applyForce(ballVelocity);

		std::cout << this->seesaw;
		std::cout << this->ball;
		this->ball.update();

		if (isBallAboveSeesaw) {
			if (this->isControllerEnabled) {
				float newAngle = this->pidController.calculateAngle(this->ball.getPosition().x, this->currentScreenSize.x / 2);
				if (newAngle != 0)
					this->seesaw.changeAngle(newAngle);
			}

			// update the position of ball, because the ball is definitely on the seesaw
			this->ball.setPosition(this->calcGuidedBallPosition());
		}

		if (this->ball.isOutOfBounds(this->currentScreenSize)) {
			std::cout << "ERROR, ball out of bounds" << std::endl;
			this->isRunning = false;
		}
	}
}

sf::Vector2f Simulator::calcGuidedBallPosition() {
	Line ballVertical = Line{
		sf::Vector2f{this->ball.getPosition().x, 0.0f},
		sf::Vector2f{this->ball.getPosition().x, (float)this->currentScreenSize.y}
	};

	Line seesawParallel = this->seesaw.getCenterLine();

	sf::Vector2f intersection = seesawParallel.cross(ballVertical);
	intersection.y -= this->ball.getRadius() + this->seesaw.getShape()->getLocalBounds().height  * abs(sin(this->seesaw.getAngle()*M_PI / 180));

	std::cout << "--> intersection point: [" << intersection.x << ", " << intersection.y << "]" << std::endl;

	return intersection;
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
	this->isRunning = false;
	this->isControllerEnabled = false;
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
	case 73: // arrow
		this->seesaw.changeAngle(10);
		break;
	case 74: // arrow
		this->seesaw.changeAngle(-10);
		break;
	case 15:
		this->isRunning = !this->isRunning;
		std::cout << "Pressed PAUSE" << std::endl;
		break;
	case 18:
		if (!isRunning) {
			this->update(true);
		}
		break;
	case 2:
		this->isControllerEnabled = !this->isControllerEnabled;
		break;
	default:
		std::cout << "!!! unrecognized key code!\t>" << (int)keyCode << "<" << std::endl;
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

Ball & Simulator::getBall()
{
	return this->ball;
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



