#include "Simulator.h"
#include <iostream>
#define _USE_MATH_DEFINES 
#include <math.h>

#include "Line.h"
#include "FileManager.h"
#include "PID.h"

Simulator::Simulator(sf::Vector2u screenSize) :
	currentScreenSize_{ screenSize },
	ball_{ screenSize },
	seesaw_{ screenSize, FileManager::get_instance().read_settings_seesaw() },
	isRunning{ true },
	//pidController{ PID{ FileManager::get_instance().read_settings_PID()} },
	isControllerEnabled_{ true }
{
	PID pid{ FileManager::get_instance().read_settings_PID() };
	//std::unique_ptr<IController> controller;
	//controller = std::make_unique<PID>(pid);
	this->pidController_ = std::make_unique<PID>(PID{ FileManager::get_instance().read_settings_PID() });
}

void Simulator::update(bool force = false)
{
	if (this->isRunning || force) {
		bool isBallAboveSeesaw = this->is_ball_on_seesaw();

		sf::Vector2f ballVelocity = this->calc_acceleration_of_ball(isBallAboveSeesaw);
		std::cout << "ball force: " << ballVelocity.x << std::endl;
		this->ball_.apply_force(ballVelocity);

		std::cout << this->seesaw_;
		std::cout << this->ball_;
		this->ball_.update();

		if (isBallAboveSeesaw) {
			if (this->isControllerEnabled_) {
				float newAngle = this->pidController_->calculate_angle(this->ball_.get_position().x, this->currentScreenSize_.x / 2);
				if (newAngle != 0)
					this->seesaw_.change_angle(newAngle);
			}

			// update the position of ball, because the ball is definitely on the seesaw
			this->ball_.set_position(this->calc_guided_ball_position());
		}

		if (this->ball_.is_out_of_bounds(this->currentScreenSize_)) {
			std::cout << "ERROR, ball out of bounds" << std::endl;
			this->isRunning = false;
		}
	}
}

sf::Vector2f Simulator::calc_guided_ball_position() {
	Line ballVertical = Line{
		sf::Vector2f{this->ball_.get_position().x, 0.0f},
		sf::Vector2f{this->ball_.get_position().x, (float)this->currentScreenSize_.y}
	};

	Line seesawParallel = this->seesaw_.get_center_line();

	sf::Vector2f intersection = seesawParallel.cross(ballVertical);
	intersection.y -= this->ball_.get_radius() + this->seesaw_.get_shape()->getLocalBounds().height  * abs(sin(this->seesaw_.get_angle()*M_PI / 180));

	std::cout << "--> intersection point: [" << intersection.x << ", " << intersection.y << "]" << std::endl;

	return intersection;
}

bool Simulator::is_ball_on_seesaw()
{
	Line seesawParallel = this->seesaw_.get_center_line();

	return this->ball_.get_position().x > seesawParallel.get_point_a().x && this->ball_.get_position().x < seesawParallel.get_point_b().x;
}

sf::Vector2f Simulator::calc_acceleration_of_ball(bool includeGravity) {
	if (this->is_ball_on_seesaw()) {
		float ballAccelerationMagnitude = gravity.y * sin(this->seesaw_.get_angle()*M_PI / 180);
		return sf::Vector2f{
			ballAccelerationMagnitude * (float)cos(this->seesaw_.get_angle()*M_PI / 180),
			0
		};
	}
	else {
		return sf::Vector2f{
			0,
			gravity.y
		};
	}
}

void Simulator::reset_simulation()
{
	this->ball_.reset(this->currentScreenSize_);
	this->seesaw_.reset(this->currentScreenSize_);
	this->pidController_->reset();
	this->isRunning = false;
	this->isControllerEnabled_ = false;
	std::cout << "Resetting simulation" << std::endl;
}

void Simulator::on_key_pressed(char keyCode)
{
	switch (keyCode) {
	case 17: // 'r'
		this->reset_simulation();
		break;
	case 72: // arrow right
		this->push_Ball_right();
		break;
	case 71: // arrow left
		this->push_ball_left();
		break;
	case 73: // arrow
		this->seesaw_.change_angle(10);
		break;
	case 74: // arrow
		this->seesaw_.change_angle(-10);
		break;
	case 15:
		this->isRunning = !this->isRunning;
		std::cout << "Pressed PAUSE" << std::endl;
		break;
	case 18:
		if (!isRunning) {
			this->update(true);
		}
		break;
	case 2:
		this->isControllerEnabled_ = !this->isControllerEnabled_;
		break;
	default:
		std::cout << "!!! unrecognized key code!\t>" << (int)keyCode << "<" << std::endl;
	}
}

std::shared_ptr<sf::Shape> Simulator::get_ball_shape()
{
	return this->ball_.get_shape();
}

std::shared_ptr<sf::Shape> Simulator::get_seesaw_shape()
{
	return this->seesaw_.get_shape();
}

void Simulator::push_ball_left()
{
	this->ball_.apply_force({ -5,0 });
	std::cout << "push ball left" << std::endl;
}

void Simulator::push_Ball_right()
{
	this->ball_.apply_force({ 5,0 });
	std::cout << "push ball right" << std::endl;
}



