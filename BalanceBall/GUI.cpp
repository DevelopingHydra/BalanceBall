#include "GUI.h"
#include <iostream>

GUI::GUI() :window{ sf::VideoMode(800,500), "Balance-ball" }, simulator{ {800,500} }
{
	this->window.setVisible(false);
	this->simulator.resetSimulation();
}

GUI::~GUI()
{
}

void GUI::show()
{
	this->window.setVisible(true);
	this->renderLoop();
}

void GUI::renderLoop()
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				this->simulator.onWindowResized({ event.size.width, event.size.height });
				break;
			case sf::Event::KeyReleased:
				this->simulator.onKeyPressed(event.key.code);
				break;
			default:
				break;
			}
		}

		window.clear(sf::Color::White);
		this->renderAllOjbects();
		window.display();
	}
}

void GUI::renderAllOjbects()
{
	this->simulator.update();
	this->window.draw(this->simulator.getBall());
}
