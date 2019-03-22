#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main(void) {
	std::cout << "test";
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.);
	shape.setFillColor(sf::Color::Green);
	sf::VideoMode test = sf::VideoMode().getDesktopMode();

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
		window.draw(shape);
		window.display();
	}

	return 0;
}

void createWindow() {
	sf::VideoMode desktopMode = sf::VideoMode().getDesktopMode();

	sf::RenderWindow window(sf::VideoMode(desktopMode.width / 2, desktopMode.height / 2), "BlanceBall GUI");

}