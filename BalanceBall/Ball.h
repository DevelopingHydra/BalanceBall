#pragma once

#include "SFML\Graphics.hpp"

class Ball
{
public:
	Ball(sf::Vector2u screenSize);
	~Ball();

	void onScreenResized(sf::Vector2u oldSize, sf::Vector2u newSize);
	void applyForce(sf::Vector2f force);
	void update();

	sf::CircleShape getShape();

private:
	sf::CircleShape shape;
	sf::Vector2f speed;
	sf::Vector2f acceleration;
};

