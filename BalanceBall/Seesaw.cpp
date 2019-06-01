#include "Seesaw.h"
#include <string>
#include <iostream>

#define _USE_MATH_DEFINES 
#include <math.h>

Seesaw::Seesaw(sf::Vector2u screenSize, Seesaw_settings settings) :
	screenSize{ screenSize },
	max_angle_{ settings.max_alpha },
	max_angle_diff_{ settings.max_diff_alpha},
	width_{settings.width}
{
	this->rect = std::make_shared<sf::RectangleShape>(sf::RectangleShape({ 0,0 }));
	this->reset(screenSize);
	this->rect->setFillColor(sf::Color::Red);
}

void Seesaw::update()
{

}

void Seesaw::reset(sf::Vector2u screenSize)
{
	this->rect->setSize({ this->width_*300, 0.05f * screenSize.y });
	//this->rect->setPosition((screenSize.x - rect->getSize().x) / 2.f, screenSize.y * 0.75f);
	//this->rect->setOrigin(rect->getSize().x / 2.f + rect->getPosition().x, rect->getSize().y / 2.f + rect->getPosition().y);
	this->rect->setOrigin(rect->getSize().x / 2.f, rect->getSize().y / 2.f);
	this->rect->setPosition(screenSize.x / 2.f, screenSize.y * 0.75f);
	this->rect->setRotation(0);
	this->angle_ = 0;
}

const std::shared_ptr<sf::Shape> Seesaw::get_shape()
{
	return this->rect;
}

void Seesaw::change_angle(float change)
{
	if (change > this->max_angle_diff_ || change < -this->max_angle_diff_) { // todo betrag
		std::cout << "\tERROR:\tangle change exceeds max angle change --> clipping" << std::endl;
		if (change > this->max_angle_diff_)
			change = this->max_angle_diff_;
		else if (change < -this->max_angle_diff_)
			change = -this->max_angle_diff_;
	}

	float newAngle = this->angle_ + change;

	if (newAngle > this->max_angle_ || newAngle < -this->max_angle_) { // todo betrag
		//throw std::exception("angle change exceed max angle");
		std::cout << "\tERROR:\tangle exceeds max angle --> clipping" << std::endl;
		if (newAngle > this->max_angle_)
			newAngle = this->max_angle_;
		else if (newAngle < -this->max_angle_)
			newAngle = -this->max_angle_;
	}

	this->angle_ = newAngle;
	this->rect->setRotation(this->angle_);
}

const float Seesaw::get_angle()
{
	return this->angle_;
}

const Line Seesaw::get_center_line()
{
	float dy = (float)sin(this->angle_*M_PI / 180)*this->rect->getLocalBounds().width / 2;
	float dx = (float)cos(this->angle_*M_PI / 180)*this->rect->getLocalBounds().width / 2;
	sf::Vector2f seesawRight = this->rect->getPosition() + sf::Vector2f{ dx,dy };
	sf::Vector2f seesawLeft = this->rect->getPosition() - sf::Vector2f{ dx,dy };

	return Line{ seesawLeft,seesawRight };
}

const std::ostream & operator<<(std::ostream & strm, Seesaw & seesaw)
{
	return strm << "SEESAW:\tpos: {" << seesaw.get_shape()->getPosition().x << "," << seesaw.get_shape()->getPosition().y << "}"
		<< " - angle: " << seesaw.angle_
		<< " - orig: {" << seesaw.get_shape()->getOrigin().x << ", " << seesaw.get_shape()->getOrigin().y << "}" << std::endl;
}
