#pragma once

#include "SFML\Graphics.hpp"
#include <memory>

#include "IGameObject.h"
#include "PID.h"
#include "Line.h"
#include "Seesaw_settings.h"

class Seesaw :public IGameObject
{
public:
	Seesaw(sf::Vector2u screenSize, Seesaw_settings settings);

	// Inherited via IGameObject
	virtual void update() override;
	virtual void reset(sf::Vector2u screenSize) override;
	virtual const std::shared_ptr<sf::Shape> get_shape() override;
	friend const std::ostream & operator<<(std::ostream & strm, Seesaw &seesaw);

	void change_angle(float change);

	const float get_angle();
	const Line get_center_line();

private:
	std::shared_ptr<sf::RectangleShape> rect;
	sf::Vector2u screenSize;

	float width_;
	float max_angle_;
	float max_angle_diff_;
	float angle_;

};

