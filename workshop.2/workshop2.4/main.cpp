#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include <cassert>
#include <ctime>

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

struct Ball
{
    float radius = 10;
    sf::Color color;
    sf::Vector2f pos;
    sf::Vector2f speed;
};

void addBall(std::vector<Ball> &balls, sf::Color color, const sf::Vector2f &pos, sf::Vector2f speed)
{
    Ball ball = {40, color, pos, speed};
    balls.push_back(ball);
}

float dist(const sf::Vector2f &a, const sf::Vector2f &b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

float dot(const sf::Vector2f &a, const sf::Vector2f &b)
{
    return a.x * b.x + a.y * b.y;
}

sf::Vector2f sca_mul(const sf::Vector2f &a, float n)
{
    return sf::Vector2f(a.x * n, a.y * n);
}

void calc_speed(const sf::Vector2f &v1, const sf::Vector2f &v2, sf::Vector2f &w1, sf::Vector2f &w2, const sf::Vector2f &c1, const sf::Vector2f &c2)
{
    w1 = v1 - sca_mul(c1 - c2, dot(v1 - v2, c1 - c2) / dot(c1 - c2, c1 - c2));
    w2 = v2 - sca_mul(c2 - c1, dot(v2 - v1, c2 - c1) / dot(c2 - c1, c2 - c1));
}

struct PRNG
{
    std::mt19937 engine;
};

void initGenerator(PRNG &generator)
{
    const unsigned seed = unsigned(std::time(nullptr));
    generator.engine.seed(seed);
}

unsigned random(PRNG &generator, unsigned minValue, unsigned maxValue)
{
    assert(minValue < maxValue);
    std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);
    return distribution(generator.engine);
}

sf::Vector2f rnd_speed(PRNG &generator)
{
    unsigned min = 5;
    unsigned max = 400;
    return {float(random(generator, min, max)), float(random(generator, min, max))};
}

sf::Color rnd_color1(PRNG &generator, const std::vector<sf::Color> &pal)
{
    return pal[random(generator, 0, pal.size() - 1)];
}

sf::Color color_mix(const sf::Color &a, const sf::Color &b)
{
    return sf::Color(a.r + b.r / 2, a.g + b.g / 2, a.b + b.b / 2);
}

sf::Color rnd_color2(PRNG &generator, const std::vector<sf::Color> &pal)
{
    return color_mix(rnd_color1(generator, pal), rnd_color1(generator, pal));
}

int main()
{
    int width = 1280;
    int height = 720;
    sf::RenderWindow window(sf::VideoMode(width, height), "Balls");

    PRNG generator;
    initGenerator(generator);

    std::vector<sf::Color> pal;
    pal.push_back(sf::Color(0x66, 0x66, 0x0));
    pal.push_back(sf::Color(0x99, 0x0, 0x0));
    pal.push_back(sf::Color(0x99, 0x66, 0xCC));
    pal.push_back(sf::Color(0xCC, 0x99, 0x66));
    pal.push_back(sf::Color(0xCC, 0xFF, 0x33));
    pal.push_back(sf::Color(0xFF, 0x66, 0x66));
    pal.push_back(sf::Color(0xFF, 0xFF, 0x66));
    pal.push_back(sf::Color(0x33, 0x99, 0x33));

    std::vector<Ball> balls;
    addBall(balls, rnd_color2(generator, pal), sf::Vector2f(100, 100), rnd_speed(generator));
    addBall(balls, rnd_color2(generator, pal), sf::Vector2f(200, 300), rnd_speed(generator));
    addBall(balls, rnd_color2(generator, pal), sf::Vector2f(600, 600), rnd_speed(generator));
    addBall(balls, rnd_color2(generator, pal), sf::Vector2f(700, 100), rnd_speed(generator));

    sf::Clock clock;

    while (window.isOpen())
    {
        pollEvents(window);
        window.clear();

        for (int i = 0; i < balls.size(); i++)
        {
            sf::CircleShape shape(balls[i].radius);
            shape.setPosition(balls[i].pos);
            shape.setOrigin(balls[i].radius, balls[i].radius);
            shape.setFillColor(balls[i].color);
            window.draw(shape);
        }

        window.display();

        float dt = clock.restart().asSeconds();

        for (int i = 0; i < balls.size(); i++)
        {
            balls[i].pos += balls[i].speed * dt;

            if (balls[i].pos.x < balls[i].radius)
            {
                balls[i].pos.x = balls[i].radius;
                balls[i].speed.x *= -1;
            }
            else if (balls[i].pos.x > width - balls[i].radius)
            {
                balls[i].pos.x = width - balls[i].radius;
                balls[i].speed.x *= -1;
            }

            if (balls[i].pos.y < balls[i].radius)
            {
                balls[i].pos.y = balls[i].radius;
                balls[i].speed.y *= -1;
            }
            else if (balls[i].pos.y > height - balls[i].radius)
            {
                balls[i].pos.y = height - balls[i].radius;
                balls[i].speed.y *= -1;
            }
        }

        for (size_t fi = 0; fi < balls.size(); ++fi)
        {
            for (size_t si = fi + 1; si < balls.size(); ++si)
            {
                if (dist(balls[fi].pos, balls[si].pos) < balls[fi].radius + balls[si].radius)
                {
                    sf::Vector2f w1;
                    sf::Vector2f w2;
                    calc_speed(balls[fi].speed, balls[si].speed, w1, w2, balls[fi].pos, balls[si].pos);
                    balls[fi].speed = w1;
                    balls[si].speed = w2;
                }
            }
        }
    }
}