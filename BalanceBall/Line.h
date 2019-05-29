#pragma once

#include "SFML\Graphics.hpp"

class Line
{
public:
	Line(sf::Vector2f pointA, sf::Vector2f pointB);

	sf::Vector2f cross(Line other);

	const sf::Vector2f& getPointA();
	const sf::Vector2f& getPointB();

private:
	sf::Vector2f pointA;
	sf::Vector2f pointB;
};

