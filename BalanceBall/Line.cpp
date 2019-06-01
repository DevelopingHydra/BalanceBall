#include "Line.h"

Line::Line(sf::Vector2f pointA, sf::Vector2f pointB):
	point_a_{pointA},
	point_b_{pointB}
{
}

// according to: https://www.geeksforgeeks.org/program-for-point-of-intersection-of-two-lines/
sf::Vector2f Line::cross(Line other)
{
	// Line AB represented as a1x + b1y = c1 
	float a1 = this->point_b_.y - this->point_a_.y;
	float b1 = this->point_a_.x - this->point_b_.x;
	float c1 = a1 * (this->point_a_.x) + b1 * (this->point_a_.y);

	// Line CD represented as a2x + b2y = c2 
	float a2 = other.point_b_.y - other.point_a_.y;
	float b2 = other.point_a_.x - other.point_b_.x;
	float c2 = a2 * (other.point_a_.x) + b2 * (other.point_b_.y);

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

const sf::Vector2f& Line::get_point_a() const
{
	return this->point_a_;
}

const sf::Vector2f & Line::get_point_b() const
{
	return this->point_b_;
}
