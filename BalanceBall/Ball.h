#pragma once

#include "SFML\Graphics.hpp"
#include <memory>

#include "IGameObject.h"

class Ball :public IGameObject 
{
public:
	Ball(sf::Vector2u screenSize);

	void apply_force(sf::Vector2f force);

	// Inherited via IGameObject
	virtual void update() override;
	virtual void reset(sf::Vector2u screenSize) override;
	virtual const std::shared_ptr<sf::Shape> get_shape() override;
	friend const std::ostream & operator<<(std::ostream & strm,  Ball &ball);

	bool is_out_of_bounds(sf::Vector2u screenSize);
	bool is_moving_left();

	const sf::Vector2f get_position();
	float get_radius();
	void set_position(sf::Vector2f newPos);

private:
	std::shared_ptr<sf::CircleShape> shape_;
	sf::Vector2f speed_;
	sf::Vector2f acceleration_;


};

