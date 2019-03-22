#include "Simulator.h"

Simulator::Simulator(unsigned int canvasWidth, unsigned int canvasHeight) :canvasWidth{ canvasWidth }, canvasHeight{ canvasHeight }, ball{ {canvasWidth, canvasHeight} }
{
}

Simulator::~Simulator()
{
}

void Simulator::onWindowResized(unsigned int newWidth, unsigned int newHeight)
{
	this->ball.onScreenResized({ this->canvasWidth, this->canvasHeight }, { newWidth, newHeight });

	this->canvasWidth = newWidth;
	this->canvasHeight = newHeight;
}

void Simulator::update()
{
	this->ball.update();
}

std::vector<std::shared_ptr<sf::Shape>> Simulator::getShapes()
{
	return this->drawables;
}
