#include <sfml/graphics.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

void init(sf::ConvexShape &pointer)
{
    pointer.setPosition({400, 300});
    pointer.setFillColor(sf::Color(0xFF, 0xFF, 0));
    pointer.setPointCount(7);
    pointer.setPoint(0, {0, 60});
    pointer.setPoint(1, {60, 0});
    pointer.setPoint(2, {0, -60});
    pointer.setPoint(3, {0, -30});
    pointer.setPoint(4, {-60, -30});
    pointer.setPoint(5, {-60, 30});
    pointer.setPoint(6, {0, 30});
    pointer.setOutlineColor(sf::Color(0, 0, 0));
    pointer.setOutlineThickness(2);
    pointer.setRotation(-80);
}

void pollEvent(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}
void updateRotation(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, float dt)
{
    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    float angle = atan2(delta.y, delta.x);
    if (angle < 0)
    {
        angle += 2 * M_PI;
    }
    angle = toDegrees(angle);
    const float maxRotation = 90 * dt;
    const float rotation = std::abs((angle - pointer.getRotation()));
    if (angle != pointer.getRotation())
    {

        if (angle > pointer.getRotation())
        {
            if ((angle - 180) > pointer.getRotation())
            {
                pointer.setRotation(pointer.getRotation() - std::min(maxRotation, rotation));
            }
            else
            {
                pointer.setRotation(pointer.getRotation() + std::min(maxRotation, rotation));
            }
        }
        else
        {
            if ((angle + 180) < pointer.getRotation())
            {
                pointer.setRotation(pointer.getRotation() + std::min(maxRotation, rotation));
            }
            else
            {
                pointer.setRotation(pointer.getRotation() - std::min(maxRotation, rotation));
            }
        }
    }
}

void updatePosition(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, float dt)
{
    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    const auto deltaLength = static_cast<float>(std::sqrt(std::pow(delta.x, 2) + std::pow(delta.y, 2)));
    sf::Vector2f direction = {0, 0};
    if (deltaLength != 0)
    {
        direction = {delta.x / deltaLength, delta.y / deltaLength};
    }
    const float speed = 20 * dt;
    pointer.setPosition(pointer.getPosition() + direction * speed);
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(pointer);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "pointer follows mouse", sf::Style::Default, settings);

    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;
    sf::Clock clock;

    init(pointer);
    while (window.isOpen())
    {
        pollEvent(window, mousePosition);
        float dt = clock.restart().asSeconds();
        updateRotation(mousePosition, pointer, dt);
        updatePosition(mousePosition, pointer, dt);
        redrawFrame(window, pointer);
    }
}