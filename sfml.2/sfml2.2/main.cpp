#include <sfml/graphics.hpp>
#include <sfml/window.hpp>
#include <cmath>

int main()
{
    constexpr int pointCount = 200;
    sf::Clock clock;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({600, 600}), "Polar rose",
        sf::Style::Default, settings);

    sf::ConvexShape rose;
    const sf::Vector2f position = {300, 300};
    rose.setFillColor(sf::Color(120, 12, 220));

    rose.setPointCount(pointCount);

    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        float roseRadius = 200 * sin(6 * angle);
        sf::Vector2f point = {
            roseRadius * std::sin(angle),
            roseRadius * std::cos(angle)};
        rose.setPoint(pointNo, point);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        float time = clock.getElapsedTime().asSeconds();
        float rotationRadius = 100;
        const float period = 2;
        const float wavePhase = time * float(2 * M_PI);
        const float x = rotationRadius * std::cos(wavePhase / period);
        const float y = rotationRadius * std::sin(wavePhase / period);
        const sf::Vector2f offset = {x, y};

        rose.setPosition(position + offset);

        window.clear();
        window.draw(rose);
        window.display();
    }
}