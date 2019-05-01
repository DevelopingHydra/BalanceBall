#pragma once

#include <SFML\Graphics.hpp>
#include <memory>

class IGameObject
{
public:
	//virtual void onScreenResized(sf::Vector2u oldSize, sf::Vector2u newSize) = 0;
	virtual void update() = 0;
	virtual void reset(sf::Vector2u screenSize) = 0;

	virtual const std::shared_ptr<sf::Shape> getShape() = 0;
};

