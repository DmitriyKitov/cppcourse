#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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
    Ball ball = {10, color, pos, speed};
    balls.push_back(ball);
}

int main()
{
    int width = 1280;
    int height = 720;
    sf::RenderWindow window(sf::VideoMode(width, height), "Balls");

    std::vector<Ball> balls;
    addBall(balls, sf::Color(0xFF, 0x0, 0x0), sf::Vector2f(100, 100), sf::Vector2f(500, -650));
    addBall(balls, sf::Color(0x0, 0xFF, 0x0), sf::Vector2f(200, 300), sf::Vector2f(-400, 200));

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
    }
}