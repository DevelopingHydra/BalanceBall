#pragma once

#include "SFML\Graphics.hpp"
#include <memory>

#include "IGameObject.h"
#include "PID.h"

class Seesaw :public IGameObject
{
public:
	Seesaw(sf::Vector2u screenSize, float max_angle, float max_angle_diff);
	~Seesaw();

	// Inherited via IGameObject
	//virtual void onScreenResized(sf::Vector2u oldSize, sf::Vector2u newSize) override;
	virtual void update() override;
	virtual void reset(sf::Vector2u screenSize) override;
	virtual const std::shared_ptr<sf::Shape> getShape() override;
	friend const std::ostream & operator<<(std::ostream & strm, Seesaw &seesaw);

	void changeAngle(float change);
	void setMaxAngle(float maxAngle);

	const float getAngle();

private:
	std::shared_ptr<sf::RectangleShape> rect;
	sf::Vector2u screenSize;

	float max_angle;
	float max_angle_diff;
	float angle;

};

