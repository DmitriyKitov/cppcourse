#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <conio.h>
#include <time.h>

struct Clock
{
    sf::Font font;

    sf::CircleShape mainClock;

    sf::CircleShape centerCircle;

    std::vector<sf::Text> npc_text;
    sf::CircleShape dot[60];

    sf::RectangleShape hourHand;
    sf::RectangleShape minuteHand;
    sf::RectangleShape secondHand;

    float clockRadius = 0;
    float clockX = 0;
    float clockY = 0;

    float centerX = 0;
    float centerY = 0;

    float centerRadius = 0;

    float hourHandLength = 0;
    float minuteHandLength = 0;
    float secondHandLength = 0;

    float hourHandWidth = 0;
    float minuteHandWidth = 0;
    float secondHandWidth = 0;

    float hour = 0;
    float minute = 0;
    float second = 0;

    float hourHandAngle = 0;
    float minuteHandAngle = 0;
    float secondHandAngle = 0;

    void init(sf::RenderWindow &window);

    void initMainClock();

    void initCenterCircle();

    void initDotsAndNumbers(sf::RenderWindow &window);

    void initHands();

    void update();

    void getTime();

    void updateClock();

    void draw(sf::RenderWindow &window);
};