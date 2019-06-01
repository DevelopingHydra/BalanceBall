#include "Ball.h"
#include <iostream>
#include <memory>

Ball::Ball(sf::Vector2u screenSize) :shape_{ }
{
	this->shape_ = std::make_shared<sf::CircleShape>(sf::CircleShape());
	this->reset(screenSize);
	this->shape_->setFillColor(sf::Color::Blue);
}

void Ball::apply_force(sf::Vector2f force)
{
	this->acceleration_ += force;
}

void Ball::update()
{
	this->shape_->move(this->speed_);
	this->speed_ += this->acceleration_;
	this->acceleration_ = { 0,0 };
}

void Ball::reset(sf::Vector2u screenSize)
{
	this->shape_->setRadius(screenSize.x / 40.f);
	auto radius = this->shape_->getRadius();
	this->shape_->setPosition(screenSize.x / 2.f - radius, screenSize.y / 2.f - radius);
	this->acceleration_ = { 0,0 };
	this->speed_ = { 0,0 };
}

bool Ball::is_out_of_bounds(sf::Vector2u screenSize)
{
	auto pos = this->get_position();
	return pos.x < 0 || pos.x > screenSize.x || pos.y < 0 || pos.y > screenSize.y;
}

bool Ball::is_moving_left()
{
	return this->acceleration_.x < 0;
}

const sf::Vector2f Ball::get_position()
{
	float radius = this->shape_->getRadius();
	return this->shape_->getPosition() + sf::Vector2f{ radius,radius };
}

float Ball::get_radius()
{
	return this->shape_->getRadius();
}

void Ball::set_position(sf::Vector2f newPos)
{
	float radius = this->shape_->getRadius();
	this->shape_->setPosition(newPos - sf::Vector2f{ radius,radius });
}

const std::shared_ptr<sf::Shape> Ball::get_shape()
{
	return this->shape_;
}

const std::ostream & operator<<(std::ostream & strm, Ball & ball)
{
	return strm << "BALL:\tacc: {" << ball.acceleration_.x << "," << ball.acceleration_.y << "} - speed: {"
		<< ball.speed_.x << "," << ball.speed_.y
		<< "} - pos: {" << ball.get_shape()->getPosition().x << "," << ball.get_shape()->getPosition().y << "}" << std::endl;
}
