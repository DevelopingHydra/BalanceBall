#include "Line.h"

Line::Line(sf::Vector2f pointA, sf::Vector2f pointB):
	pointA{pointA},
	pointB{pointB}
{
}

// according to: https://www.geeksforgeeks.org/program-for-point-of-intersection-of-two-lines/
sf::Vector2f Line::cross(Line other)
{
	// Line AB represented as a1x + b1y = c1 
	float a1 = this->pointB.y - this->pointA.y;
	float b1 = this->pointA.x - this->pointB.x;
	float c1 = a1 * (this->pointA.x) + b1 * (this->pointA.y);

	// Line CD represented as a2x + b2y = c2 
	float a2 = other.pointB.y - other.pointA.y;
	float b2 = other.pointA.x - other.pointB.x;
	float c2 = a2 * (other.pointA.x) + b2 * (other.pointB.y);

	float determinant = a1 * b2 - a2 * b1;

	if (determinant == 0)
	{
		// The lines are parallel. This is simplified 
		// by returning a pair of FLT_MAX 
		return sf::Vector2f(FLT_MAX, FLT_MAX);
	}
	else
	{
		float x = (b2*c1 - b1 * c2) / determinant;
		float y = (a1*c2 - a2 * c1) / determinant;
		return sf::Vector2f(x, y);
	}
}

const sf::Vector2f& Line::getPointA()
{
	return this->pointA;
}

const sf::Vector2f & Line::getPointB()
{
	return this->pointB;
}
