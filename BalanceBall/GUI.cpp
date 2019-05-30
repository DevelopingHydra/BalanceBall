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
	this->simulator.update(false);
	this->window.draw(*this->simulator.getSeesawShape());

	// for debugging
	// todo: remove later
	Line seesawCenter = simulator.getSeesaw().getCenterLine();
	sf::ConvexShape convex;
	convex.setFillColor(sf::Color::Cyan);
	convex.setPointCount(4);
	convex.setPoint(0, seesawCenter.getPointA());
	convex.setPoint(1, seesawCenter.getPointA() + sf::Vector2f{0, 30});
	convex.setPoint(2, seesawCenter.getPointB() + sf::Vector2f{ 0, 30 });
	convex.setPoint(3, seesawCenter.getPointB());
	this->window.draw(convex);

	this->window.draw(*this->simulator.getBallShape());

	auto ballShape = this->simulator.getBallShape();
	sf::CircleShape bb(2.0f);
	bb.setFillColor(sf::Color::Yellow);
	bb.setPosition(this->simulator.getBall().getPosition());
	this->window.draw(bb);

	auto ball = this->simulator.getBall();
	Line ballVertical = Line{
		sf::Vector2f{ball.getPosition().x, 0.0f},
		sf::Vector2f{ball.getPosition().x, (float)WINDOW_HEIGHT}
	};

	Line seesawParallel = this->simulator.getSeesaw().getCenterLine();

	sf::Vector2f intersection = seesawParallel.cross(ballVertical);
	sf::CircleShape bb2(5.0f);
	bb2.setFillColor(sf::Color::Green);
	bb2.setPosition(intersection);
	this->window.draw(bb2);

	sf::CircleShape bb3(5.0f);
	bb3.setFillColor(sf::Color::Black);
	bb3.setPosition(WINDOW_WIDTH/2, intersection.y);
	this->window.draw(bb3);
	
}
