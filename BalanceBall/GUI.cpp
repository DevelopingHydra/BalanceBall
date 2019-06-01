#include "GUI.h"
#include <iostream>
#include <filesystem>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

GUI::GUI() :
	window{ sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Balance-ball", sf::Style::Titlebar | sf::Style::Close },
	simulator{ {WINDOW_WIDTH, WINDOW_HEIGHT} }
{
	std::string cwd = std::experimental::filesystem::current_path().string();
	this->roboto_font = sf::Font{};
	if (!this->roboto_font.loadFromFile(cwd + "/../resources/fonts/Roboto-Medium.ttf")) {
		throw std::runtime_error{ "Unable to load font" };
	}

	info_text = sf::Text{};
	info_text.setFont(roboto_font);
	info_text.setString("Push Ball: arrow keys left/right\nMove seesaw: Arrow keys up/down\nPause: p\nSingle step (while paused): s\ndisable controller: c");
	info_text.setCharacterSize(14);
	info_text.setFillColor(sf::Color::Black);
	info_text.setPosition(10, 10);

	pause_text = sf::Text{};
	pause_text.setFont(roboto_font);
	pause_text.setString("PAUSED");
	pause_text.setCharacterSize(18);
	pause_text.setFillColor(sf::Color::Red);
	pause_text.setPosition(WINDOW_WIDTH/2-pause_text.getLocalBounds().width/2, 50);


	this->window.setVisible(false);
	this->window.setFramerateLimit(30);
	this->simulator.reset_simulation();
}

void GUI::show()
{
	this->window.setVisible(true);
	this->render_loop();
}

void GUI::render_loop()
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
				this->simulator.on_key_pressed(event.key.code);
				break;
			default:
				break;
			}
		}

		window.clear(sf::Color::White);
		this->render_all_ojbects();
		this->print_text();
		window.display();

		sf::sleep(sf::Time{ sf::milliseconds(100) });
	}
}

void GUI::render_all_ojbects()
{
	this->simulator.update(false);
	this->window.draw(*this->simulator.get_seesaw_shape());
	this->window.draw(*this->simulator.get_ball_shape());
}

void GUI::print_text()
{
	this->window.draw(this->info_text);
	if (!this->simulator.isRunning) {
		this->window.draw(pause_text);
	}
}
