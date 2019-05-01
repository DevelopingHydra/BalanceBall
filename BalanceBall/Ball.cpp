#include "Ball.h"
#include <iostream>
#include <memory>

Ball::Ball(sf::Vector2u screenSize) :shape{ }
{
	this->shape = std::make_shared<sf::CircleShape>(sf::CircleShape());
	this->reset(screenSize);
	this->shape->setFillColor(sf::Color::Blue);
}

Ball::~Ball()
{
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


bool Ball::isOutOfBounce(sf::Vector2u screenSize)
{
	auto pos = shape->getPosition();
	return pos.x < 0 || pos.x > screenSize.x || pos.y < 0 || pos.y > screenSize.y;
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
