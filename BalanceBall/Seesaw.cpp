#include "Seesaw.h"
#include <string>
#include <iostream>

#define _USE_MATH_DEFINES 
#include <math.h>

Seesaw::Seesaw(sf::Vector2u screenSize, float max_angle, float max_angle_diff) :
	screenSize{ screenSize },
	max_angle{ max_angle },
	max_angle_diff{ max_angle_diff }
{
	this->rect = std::make_shared<sf::RectangleShape>(sf::RectangleShape({ 0,0 }));
	this->reset(screenSize);
	this->rect->setFillColor(sf::Color::Red);
}

Seesaw::~Seesaw()
{
}

void Seesaw::update()
{

}

void Seesaw::reset(sf::Vector2u screenSize)
{
	this->rect->setSize({ 0.8f * screenSize.x, 0.05f * screenSize.y });
	//this->rect->setPosition((screenSize.x - rect->getSize().x) / 2.f, screenSize.y * 0.75f);
	//this->rect->setOrigin(rect->getSize().x / 2.f + rect->getPosition().x, rect->getSize().y / 2.f + rect->getPosition().y);
	this->rect->setOrigin(rect->getSize().x / 2.f, rect->getSize().y / 2.f);
	this->rect->setPosition(screenSize.x / 2.f, screenSize.y * 0.75f);
	this->rect->setRotation(0);
	this->angle = 0;
}

const std::shared_ptr<sf::Shape> Seesaw::getShape()
{
	return this->rect;
}

void Seesaw::changeAngle(float change)
{
	if (change > this->max_angle_diff || change < -this->max_angle_diff) { // todo betrag
		std::cout << "\tERROR:\tangle change exceeds max angle change --> clipping" << std::endl;
		if (change > this->max_angle_diff)
			change = this->max_angle_diff;
		else if (change < -this->max_angle_diff)
			change = -this->max_angle_diff;
	}

	float newAngle = this->angle + change;

	if (newAngle > this->max_angle || newAngle < -this->max_angle) { // todo betrag
		//throw std::exception("angle change exceed max angle");
		std::cout << "\tERROR:\tangle exceeds max angle --> clipping" << std::endl;
		if (newAngle > this->max_angle)
			newAngle = this->max_angle;
		else if (newAngle < -this->max_angle)
			newAngle = -this->max_angle;
	}

	this->angle = newAngle;
	this->rect->setRotation(this->angle);
}

void Seesaw::setMaxAngle(float maxAngle)
{
	this->max_angle = maxAngle;
}

const float Seesaw::getAngle()
{
	return this->angle;
}

const Line Seesaw::getCenterLine()
{
	float dy = (float)sin(this->angle*M_PI / 180)*this->rect->getLocalBounds().width / 2;
	float dx = (float)cos(this->angle*M_PI / 180)*this->rect->getLocalBounds().width / 2;
	sf::Vector2f seesawRight = this->rect->getPosition() + sf::Vector2f{ dx,dy };
	sf::Vector2f seesawLeft = this->rect->getPosition() - sf::Vector2f{ dx,dy };

	return Line{ seesawLeft,seesawRight };
}

const std::ostream & operator<<(std::ostream & strm, Seesaw & seesaw)
{
	return strm << "SEESAW:\tpos: {" << seesaw.getShape()->getPosition().x << "," << seesaw.getShape()->getPosition().y << "}"
		<< " - angle: " << seesaw.angle
		<< " - orig: {" << seesaw.getShape()->getOrigin().x << ", " << seesaw.getShape()->getOrigin().y << "}" << std::endl;
}
