#include "Ball.h"
#include <iostream>

Ball::Ball(sf::Vector2u screenSize) :shape{  }
{
	this->reset(screenSize);
	this->shape.setFillColor(sf::Color::Blue);
}

Ball::~Ball()
{
}

void Ball::onScreenResized(sf::Vector2u oldSize, sf::Vector2u newSize)
{
	this->shape.setRadius(std::min(newSize.x, newSize.y) / 10.0f);
	this->shape.setPosition((float)oldSize.x / newSize.x, (float)oldSize.y / newSize.y);
}

void Ball::applyForce(sf::Vector2f force)
{
	this->acceleration += force;
}

void Ball::update()
{
	this->shape.move(this->speed);
	//this->shape.setPosition(shape.getPosition() + this->speed);
	this->speed += this->acceleration;
	this->acceleration = { 0,0 };

	//std::cout << acceleration.x << "," << acceleration.y << " - "
	//	<< speed.x << "," << speed.y << " - " << shape.getPosition().x << "," << shape.getPosition().y << "\n";
}

void Ball::reset(sf::Vector2u screenSize)
{
	this->shape.setPosition(screenSize.x / 2, screenSize.y / 2);
	this->acceleration = { 0,0 };
	this->speed = { 0,0 };
	this->onScreenResized(screenSize, screenSize);
}

sf::CircleShape Ball::getShape()
{
	return this->shape;
}
