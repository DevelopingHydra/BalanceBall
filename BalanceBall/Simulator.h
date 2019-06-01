#pragma once

#include "SFML\Graphics.hpp"
#include <memory>

#include "Ball.h"
#include "Seesaw.h"
#include "IController.h"

class Simulator
{
public:
	Simulator(sf::Vector2u screenSize);

	void update(bool force);
	void reset_simulation();
	void on_key_pressed(char keyCode);

	std::shared_ptr<sf::Shape> get_ball_shape();
	std::shared_ptr<sf::Shape> get_seesaw_shape();

	bool isRunning;

	sf::Vector2f calc_guided_ball_position(); // todo make private
private:
	const sf::Vector2f gravity{ 0, 9.81f }; // positive, because of coordinate system
	Ball ball_;
	Seesaw seesaw_;
	std::unique_ptr<IController> pidController_;

	sf::Vector2u currentScreenSize_;
	bool isControllerEnabled_;

	void push_ball_left();
	void push_Ball_right();
	sf::Vector2f calc_acceleration_of_ball(bool includeGravity);
	bool is_ball_on_seesaw();
};

