#pragma once

#include <SFML/Graphics.hpp>
#include "Simulator.h"

class GUI
{
public:
	GUI();

	void show();

private:
	sf::RenderWindow window;
	Simulator simulator;

	sf::Font roboto_font;
	sf::Text info_text;
	sf::Text pause_text;

	const int target_framerate_ = 30;

	void render_loop();
	void render_all_ojbects();
	void print_text();
};
