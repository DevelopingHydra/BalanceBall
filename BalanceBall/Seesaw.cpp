#include "Seesaw.h"
#include <string>

Seesaw::Seesaw(sf::Vector2u screenSize, float max_angle) : screenSize{ screenSize }, max_angle{ max_angle }
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
}

const std::shared_ptr<sf::Shape> Seesaw::getShape()
{
	return this->rect;
}

void Seesaw::changeAngle(float change)
{
	float newAngle = this->angle + change;
	if (newAngle > this->max_angle || newAngle < -this->max_angle) {
		throw std::exception("angle change exceed max angle");
	}

	this->angle = newAngle;
	this->rect->rotate(change);
}

void Seesaw::setMaxAngle(float maxAngle)
{
	this->max_angle = maxAngle;
}

const std::ostream & operator<<(std::ostream & strm, Seesaw & seesaw)
{
	return strm << "SEESAW:\tpos: {" << seesaw.getShape()->getPosition().x << "," << seesaw.getShape()->getPosition().y << "}"
		<< "angle: " << seesaw.angle
		<< " - orig: {" << seesaw.getShape()->getOrigin().x << ", " << seesaw.getShape()->getOrigin().y << "}\n";
}
