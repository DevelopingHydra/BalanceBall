#pragma once

#include "SFML\Graphics.hpp"
#include <memory>

#include "IGameObject.h"

class Ball :public IGameObject 
{
public:
	Ball(sf::Vector2u screenSize);
	~Ball();

	void applyForce(sf::Vector2f force);

	// Inherited via IGameObject
	//virtual void onScreenResized(sf::Vector2u oldSize, sf::Vector2u newSize) override;
	virtual void update() override;
	virtual void reset(sf::Vector2u screenSize) override;
	virtual const std::shared_ptr<sf::Shape> getShape() override;
	friend const std::ostream & operator<<(std::ostream & strm,  Ball &ball);

	bool isOutOfBounce(sf::Vector2u screenSize);

private:
	std::shared_ptr<sf::CircleShape> shape;
	sf::Vector2f speed;
	sf::Vector2f acceleration;


};

