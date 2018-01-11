#include <SFML/Graphics.hpp>
#include <windows.h>
#include <string>
#include <cmath>

void initClock(sf::CircleShape &clock, float clockRadius, float clockX, float clockY)
{
	clock.setPosition(clockX, clockY);
	clock.setOutlineThickness(1.0f);
	clock.setOutlineColor(sf::Color::Black);
	clock.setFillColor(sf::Color::White);
}

void pollEvent(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}

void redrawFrame(sf::RenderWindow &window, sf::CircleShape centerCircle, sf::RectangleShape hourHand, sf::RectangleShape minuteHand, sf::RectangleShape secondHand, sf::CircleShape clock)
{
	window.clear(sf::Color::White);
	window.draw(clock);
	window.draw(centerCircle);
	window.draw(hourHand);
	window.draw(minuteHand);
	window.draw(secondHand);
}
int main()
{
	const int screenWidth = 800;
	const int screenHeight = 800;
	int x, y, x1, y1, n = 6;
	float angle = 0.0;
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		//error
	}

	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight, 32), "Clock");

	float clockRadius = 350;
	float clockX = (screenWidth - 2 * clockRadius) / 2;
	float clockY = (screenHeight - 2 * clockRadius) / 2;

	float centerX = clockX + clockRadius;
	float centerY = clockY + clockRadius;

	sf::CircleShape clock(clockRadius, 360U);

	initClock(clock, clockRadius, clockX, clockY);

	float centerRadius = 20;

	sf::CircleShape centerCircle = sf::CircleShape(centerRadius, 360);
	centerCircle.setPosition(centerX - centerRadius, centerY - centerRadius);
	centerCircle.setFillColor(sf::Color::Black);

	float hourHandLength = (10.0f / 16.0f) * clockRadius;
	float minuteHandLength = (14.0f / 16.0f) * clockRadius;
	float secondHandLength = (15.0f / 16.0f) * clockRadius;

	float hourHandWidth = 6.0f;
	float minuteHandWidth = 6.0f;
	float secondHandWidth = 3.0f;

	float hour = 0.0f;
	float minute = 0.0f;
	float second = 0.0f;

	float hourHandAngle = 0.0f;
	float minuteHandAngle = 0.0f;
	float secondHandAngle = 0.0f;

	std::vector<sf::Text> npc_text(12);
	sf::CircleShape dot[60];
	for (int i = 0; i < 60; i++)
	{
		x = (clockRadius - 10) * std::cos(angle);
		y = (clockRadius - 10) * std::sin(angle);
		x1 = (clockRadius - 30) * std::sin(angle);
		y1 = (clockRadius - 30) * std::cos(angle);

		if (i % 5 == 0)
		{
			if (n == 0)
				n = 12;
			dot[i] = sf::CircleShape(3);
			npc_text[i / 5].setFont(font);
			npc_text[i / 5].setString(std::to_string(n));
			npc_text[i / 5].setPosition(x1 + window.getSize().x / 2, y1 + window.getSize().y / 2);
			npc_text[i / 5].setOrigin(npc_text[i / 5].getGlobalBounds().width / 2, npc_text[i / 5].getGlobalBounds().height / 2);
			npc_text[i / 5].setFillColor(sf::Color(0, 0, 0));
			npc_text[i / 5].setCharacterSize(24);
			n--;
		}
		else
			dot[i] = sf::CircleShape(1);
		dot[i].setFillColor(sf::Color::Black);
		dot[i].setOrigin(dot[i].getGlobalBounds().width / 2, dot[i].getGlobalBounds().height / 2);
		dot[i].setPosition(x + window.getSize().x / 2, y + window.getSize().y / 2);

		angle = angle + ((2 * M_PI) / 60);
	}

	sf::RectangleShape hourHand;
	hourHand.setPosition(centerX, centerY - hourHandWidth / 2);
	hourHand.setSize(sf::Vector2f(hourHandLength, hourHandWidth));
	hourHand.setFillColor(sf::Color::Black);

	sf::RectangleShape minuteHand;
	minuteHand.setPosition(centerX, centerY - minuteHandWidth / 2);
	minuteHand.setSize(sf::Vector2f(minuteHandLength, minuteHandWidth));
	minuteHand.setFillColor(sf::Color::Black);

	sf::RectangleShape secondHand;
	secondHand.setPosition(centerX, centerY - secondHandWidth / 2);
	secondHand.setSize(sf::Vector2f(secondHandLength, secondHandWidth));
	secondHand.setFillColor(sf::Color::Red);

	while (window.isOpen())
	{
		// save the current system time (using windows.h)
		SYSTEMTIME systime;
		GetLocalTime(&systime);
		second = systime.wSecond;
		minute = systime.wMinute + second / 60;
		hour = systime.wHour + minute / 60;

		// change the angle of the hour, minute and second hand
		hourHandAngle = (hour / 12.0f) * 360.0f - 90.0f;
		minuteHandAngle = (minute / 60.0f) * 360.0f - 90.0f;
		secondHandAngle = (second / 60.0f) * 360.0f - 90.0f;
		hourHand.setRotation(hourHandAngle);
		minuteHand.setRotation(minuteHandAngle);
		secondHand.setRotation(secondHandAngle);

		pollEvent(window);
		redrawFrame(window, centerCircle, hourHand, minuteHand, secondHand, clock);
		for (int i = 0; i < 60; i++)
		{
			window.draw(dot[i]);
		}
		for (auto &text : npc_text)
			window.draw(text);
		window.display();
	}

	return 0;
}