#include "Ball.h"
#include <iostream>
#include <memory>

Ball::Ball(sf::Vector2u screenSize) :shape{ }
{
	this->shape = std::make_shared<sf::CircleShape>(sf::CircleShape());
	this->reset(screenSize);
	this->shape->setFillColor(sf::Color::Blue);
}

void Ball::applyForce(sf::Vector2f force)
{
	this->acceleration += force;
}

void Ball::update()
{
	this->shape->move(this->speed);
	this->speed += this->acceleration;
	this->acceleration = { 0,0 };
}

void Ball::reset(sf::Vector2u screenSize)
{
	this->shape->setPosition(screenSize.x / 2.f, screenSize.y / 2.f);
	this->shape->setRadius(screenSize.x / 40.f);
	this->acceleration = { 0,0 };
	this->speed = { 0,0 };
}

bool Ball::isOutOfBounds(sf::Vector2u screenSize)
{
	auto pos = shape->getPosition();
	return pos.x < 0 || pos.x > screenSize.x || pos.y < 0 || pos.y > screenSize.y;
}

void Ball::amplifyForce(float factor)
{
	this->acceleration *= factor;
}

bool Ball::isMovingLeft()
{
	return this->acceleration.x < 0;
}

const sf::Vector2f Ball::getPosition()
{
	return this->shape->getPosition();
}

void Ball::setYPosition(float newY)
{
	this->shape->setPosition(this->shape->getPosition().x, newY);
}

const std::shared_ptr<sf::Shape> Ball::getShape()
{
	return this->shape;
}

const std::ostream & operator<<(std::ostream & strm, Ball & ball)
{
	return strm << "BALL:\tacc: {" << ball.acceleration.x << "," << ball.acceleration.y << "} - speed: {"
		<< ball.speed.x << "," << ball.speed.y
		<< "} - pos: {" << ball.getShape()->getPosition().x << "," << ball.getShape()->getPosition().y << "}\n";
}
