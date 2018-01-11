#include "main.hpp"

void Clock::init(sf::RenderWindow &window)
{
    initMainClock();
    initCenterCircle();
    initDotsAndNumbers(window);
    initHands();
}

void Clock::initMainClock()
{
    this->clockRadius = CLOCK_RADIUS;
    this->clockX = CLOCK_X;
    this->clockY = CLOCK_Y;

    this->mainClock.setRadius(this->clockRadius);
    this->mainClock.setPointCount(360U);
    this->mainClock.setPosition(this->clockX, this->clockY);
    this->mainClock.setOutlineThickness(1.0f);
    this->mainClock.setOutlineColor(sf::Color::Black);
    this->mainClock.setFillColor(sf::Color::White);
}

void Clock::initCenterCircle()
{
    this->centerRadius = CENTER_RADIUS;

    this->centerX = CENTER_X;
    this->centerY = CENTER_Y;

    this->centerCircle.setRadius(this->centerRadius);
    this->centerCircle.setPointCount(360);
    this->centerCircle.setPosition(this->centerX - this->centerRadius, this->centerY - this->centerRadius);
    this->centerCircle.setFillColor(sf::Color::Black);
}

void Clock::initDotsAndNumbers(sf::RenderWindow &window)
{
    int x, y, x1, y1, n = 6;
    float angle = 0;
    assert(this->font.loadFromFile("arial.ttf"));

    this->npc_text.resize(12);
    for (int i = 0; i < 60; i++)
    {
        x = (this->clockRadius - 10) * std::cos(angle);
        y = (this->clockRadius - 10) * std::sin(angle);
        x1 = (this->clockRadius - 30) * std::sin(angle);
        y1 = (this->clockRadius - 30) * std::cos(angle);

        if (i % 5 == 0)
        {
            if (n == 0)
            {
                n = 12;
            }
            this->dot[i] = sf::CircleShape(3);
            this->npc_text[i / 5].setFont(this->font);
            this->npc_text[i / 5].setString(std::to_string(n));
            this->npc_text[i / 5].setPosition(x1 + window.getSize().x / 2, y1 + window.getSize().y / 2);
            this->npc_text[i / 5].setOrigin(this->npc_text[i / 5].getGlobalBounds().width / 2, this->npc_text[i / 5].getGlobalBounds().height / 2);
            this->npc_text[i / 5].setFillColor(sf::Color(0, 0, 0));
            this->npc_text[i / 5].setCharacterSize(24);
            n--;
        }
        else
        {
            this->dot[i] = sf::CircleShape(1);
        }
        this->dot[i].setFillColor(sf::Color::Black);
        this->dot[i].setOrigin(this->dot[i].getGlobalBounds().width / 2, this->dot[i].getGlobalBounds().height / 2);
        this->dot[i].setPosition(x + window.getSize().x / 2, y + window.getSize().y / 2);

        angle = angle + ((2 * M_PI) / 60);
    }
}

void Clock::initHands()
{

    this->hourHandLength = HOUR_HAND_LENGHT;
    this->minuteHandLength = MINUTE_HAND_LENGHT;
    this->secondHandLength = SECOND_HAND_LENGHT;

    this->hourHandWidth = HOUR_HAND_WIDTH;
    this->minuteHandWidth = MINUTE_HAND_WIDTH;
    this->secondHandWidth = SECOND_HAND_WIDTH;

    this->hourHand.setPosition(this->centerX, this->centerY - this->hourHandWidth / 2);
    this->hourHand.setSize(sf::Vector2f(this->hourHandLength, this->hourHandWidth));
    this->hourHand.setFillColor(sf::Color::Black);

    this->minuteHand.setPosition(this->centerX, this->centerY - this->minuteHandWidth / 2);
    this->minuteHand.setSize(sf::Vector2f(this->minuteHandLength, this->minuteHandWidth));
    this->minuteHand.setFillColor(sf::Color::Black);

    this->secondHand.setPosition(this->centerX, this->centerY - this->secondHandWidth / 2);
    this->secondHand.setSize(sf::Vector2f(this->secondHandLength, this->secondHandWidth));
    this->secondHand.setFillColor(sf::Color::Red);
}

void Clock::update()
{
    getTime();
    updateClock();
}

void Clock::getTime()
{
    time_t t;
    struct tm *t_m;
    t = time(NULL);
    t_m = localtime(&t);

    this->second = t_m->tm_sec;
    this->minute = t_m->tm_min;
    this->hour = t_m->tm_hour;
}

void Clock::updateClock()
{
    this->hourHandAngle = (this->hour / 12.0f) * 360.0f - 90.0f;
    this->minuteHandAngle = (this->minute / 60.0f) * 360.0f - 90.0f;
    this->secondHandAngle = (this->second / 60.0f) * 360.0f - 90.0f;
    this->hourHand.setRotation(this->hourHandAngle);
    this->minuteHand.setRotation(this->minuteHandAngle);
    this->secondHand.setRotation(this->secondHandAngle);
}

void Clock::draw(sf::RenderWindow &window)
{
    window.draw(this->mainClock);
    window.draw(this->centerCircle);
    window.draw(this->hourHand);
    window.draw(this->minuteHand);
    window.draw(this->secondHand);
    for (int i = 0; i < 60; i++)
    {
        window.draw(this->dot[i]);
    }
    for (auto &text : this->npc_text)
        window.draw(text);
}