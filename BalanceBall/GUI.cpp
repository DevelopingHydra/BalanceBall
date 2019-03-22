#include "GUI.h"
#include <iostream>

GUI::GUI()
{
	this->initialize();
}

GUI::~GUI()
{
}

void GUI::show()
{
	this->window.setVisible(true);
	this->renderLoop();
}

void GUI::initialize()
{
	sf::VideoMode desktopMode = sf::VideoMode().getDesktopMode();
	sf::RenderWindow window_(sf::VideoMode(desktopMode.width / 2, desktopMode.height / 2), "BlanceBall GUI");
	this->window = window_;
	this->renderLoop();

	std::cout << window.isOpen();
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
			case sf::Event::KeyReleased:
				break;
			default:
				break;
			}
		}

		window.clear();
		window.display();
	}
}
