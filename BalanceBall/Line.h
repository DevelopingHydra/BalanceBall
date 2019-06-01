#pragma once

#include "SFML\Graphics.hpp"

class Line
{
public:
	Line(sf::Vector2f pointA, sf::Vector2f pointB);

	sf::Vector2f cross(Line other);

	const sf::Vector2f& get_point_a() const;
	const sf::Vector2f& get_point_b() const;

private:
	sf::Vector2f point_a_;
	sf::Vector2f point_b_;
};

