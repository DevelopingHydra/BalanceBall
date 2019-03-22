#include "Ball.h"

Ball::Ball(sf::Vector2u screenSize) :shape{ }
{
	this->shape.setPosition(screenSize.x / 2, screenSize.y / 2);
	this->onScreenResized(screenSize, screenSize);
}

Ball::~Ball()
{
}

void Ball::onScreenResized(sf::Vector2u oldSize, sf::Vector2u newSize)
{
	this->shape.setRadius(std::min(newSize.x, newSize.y) / 10);
	this->shape.setPosition(oldSize.x / newSize.x, oldSize.y / newSize.y);
}

void Ball::applyForce(sf::Vector2f force)
{
	this->acceleration += force;
}

void Ball::update()
{
	this->shape.move(this->speed.x, this->speed.y);
	this->speed += this->acceleration;
}

sf::CircleShape Ball::getShape()
{
	return this->shape;
}
