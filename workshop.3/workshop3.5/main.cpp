#include "main.hpp"

int main()
{
	sf::RenderWindow window;
	createWindow(window);

	Clock clock;

	init(clock, window);

	while (window.isOpen())
	{
		pollEvents(window);
		update(clock);
		redrawFrame(window, clock);
	}
}

void init(Clock &clock, sf::RenderWindow &window)
{
	clock.init(window);
}

void pollEvents(sf::RenderWindow &window)
{
	sf::Event event{};
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		{
			window.close();
			break;
		}
		default:
		{
			break;
		}
		}
	}
}

void update(Clock &clock)
{
	clock.update();
}

void redrawFrame(sf::RenderWindow &window, Clock &clock)
{
	window.clear(sf::Color::White);
	clock.draw(window);
	window.display();
}

void createWindow(sf::RenderWindow &window)
{
	sf::VideoMode videoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
	sf::ContextSettings settings;
	settings.antialiasingLevel = ANTIALIASING_LEVEL;
	window.create(videoMode, WINDOW_TITLE, sf::Style::Default, settings);
	window.setFramerateLimit(MAX_FPS);
}