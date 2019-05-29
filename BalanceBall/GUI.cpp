#include "GUI.h"
#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

GUI::GUI()
	:window{ sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Balance-ball", sf::Style::Titlebar | sf::Style::Close },
	simulator{ {WINDOW_WIDTH, WINDOW_HEIGHT} }
{
	this->window.setVisible(false);
	this->window.setFramerateLimit(30);
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
	//const sf::Time millisecondsBetweenFrames = sf::milliseconds(1000 / this->targetFramerate);

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
				//case sf::Event::Resized:
				//	this->simulator.onWindowResized({ event.size.width, event.size.height });
				//	break;
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

		sf::sleep(sf::Time{ sf::milliseconds(100) });
	}
}

void GUI::renderAllOjbects()
{
	this->simulator.update();
	this->window.draw(*this->simulator.getBall());
	this->window.draw(*this->simulator.getSeesaw());
}
