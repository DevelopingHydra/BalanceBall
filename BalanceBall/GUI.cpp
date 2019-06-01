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
	this->robotoFont = sf::Font{};
	if (!this->robotoFont.loadFromFile(cwd + "/../resources/fonts/Roboto-Medium.ttf")) {
		throw std::runtime_error{ "Unable to load font" };
	}

	infoText = sf::Text{};
	infoText.setFont(robotoFont);
	infoText.setString("Push Ball: arrow keys left/right\nMove seesaw: Arrow keys up/down\nPause: p\nSingle step (while paused): s\ndisable controller: c");
	infoText.setCharacterSize(14);
	infoText.setFillColor(sf::Color::Black);
	infoText.setPosition(10, 10);

	pauseText = sf::Text{};
	pauseText.setFont(robotoFont);
	pauseText.setString("PAUSED");
	pauseText.setCharacterSize(18);
	pauseText.setFillColor(sf::Color::Red);
	pauseText.setPosition(WINDOW_WIDTH/2-pauseText.getLocalBounds().width/2, 50);


	this->window.setVisible(false);
	this->window.setFramerateLimit(30);
	this->simulator.resetSimulation();
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
		this->window.draw(this->infoText);
		if (!this->simulator.isRunning) {
			this->window.draw(pauseText);
		}
		window.display();

		sf::sleep(sf::Time{ sf::milliseconds(100) });
	}
}

void GUI::renderAllOjbects()
{
	this->simulator.update(false);
	this->window.draw(*this->simulator.getSeesawShape());

	// for debugging
	// todo: remove later
	//Line seesawCenter = simulator.getSeesaw().getCenterLine();
	//sf::ConvexShape convex;
	//convex.setFillColor(sf::Color::Cyan);
	//convex.setPointCount(4);
	//convex.setPoint(0, seesawCenter.getPointA());
	//convex.setPoint(1, seesawCenter.getPointA() + sf::Vector2f{ 0, 10 });
	//convex.setPoint(2, seesawCenter.getPointB() + sf::Vector2f{ 0, 10 });
	//convex.setPoint(3, seesawCenter.getPointB());
	//this->window.draw(convex);

	this->window.draw(*this->simulator.getBallShape()); // draw ball

	//auto ballShape = this->simulator.getBallShape();
	//sf::CircleShape bb(2.0f);
	//bb.setFillColor(sf::Color::Yellow);
	//bb.setPosition(this->simulator.getBall().getPosition());
	//this->window.draw(bb);

	//sf::Vector2f intersection = this->simulator.calcGuidedBallPosition();
	//sf::CircleShape bb2(5.0f);
	//bb2.setFillColor(sf::Color::Green);
	//bb2.setPosition(intersection);
	//this->window.draw(bb2);

	//sf::CircleShape bb3(5.0f);
	//bb3.setFillColor(sf::Color::Black);
	//bb3.setPosition(WINDOW_WIDTH / 2, intersection.y);
	//this->window.draw(bb3);

}
