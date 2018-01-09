#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

void init(sf::Texture &textureCat, sf::Texture &textureRedPoint, sf::Sprite &cat, sf::Sprite &redPoint, sf::Vector2f center)
{
    textureCat.loadFromFile("cat.png", sf::IntRect(0, 0, 38, 35));
    cat.setTexture(textureCat);
    cat.setPosition(center);
    cat.setOrigin(18, 19);

    textureRedPoint.loadFromFile("pointer.png", sf::IntRect(0, 0, 32, 32));
    redPoint.setTexture(textureRedPoint);
    redPoint.setOrigin(16, 16);
}

void update(const sf::Vector2f &mousePosition, sf::Clock &clock, sf::Sprite &cat, sf::Sprite &redPoint)
{
    redPoint.setPosition(mousePosition);
    const sf::Vector2f mousePositionDelta = mousePosition - cat.getPosition();
    float deltaTime = clock.restart().asSeconds();
    float distancePointCat = std::hypot(mousePositionDelta.x, mousePositionDelta.y);
    sf::Vector2f direction = {mousePositionDelta.x / distancePointCat, mousePositionDelta.y / distancePointCat};
    float speedMotionMax = 90.0;
    float speedMotion = speedMotionMax * deltaTime;
    if (distancePointCat > 0.5)
    {
        cat.setPosition(cat.getPosition() + direction * speedMotion);
        if (redPoint.getPosition().x != cat.getPosition().x)
        {
            if (redPoint.getPosition().x < cat.getPosition().x)
            {
                cat.setScale(-1, 1);
            }
            if (redPoint.getPosition().x > cat.getPosition().x)
            {
                cat.setScale(1, 1);
            }
        }
    }
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
        case sf::Event::MouseButtonReleased:
            mousePosition = {float(event.mouseButton.x), float(event.mouseButton.y)};
            break;
        default:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, sf::Sprite &cat, sf::Sprite &redPoint)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(cat);
    window.draw(redPoint);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Cat and point",
        sf::Style::Default, settings);

    sf::Clock clock;

    sf::Vector2f center = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};

    sf::Texture textureCat;
    sf::Sprite cat;
    sf::Texture textureRedPoint;
    sf::Sprite redPoint;

    sf::Vector2f mousePosition = {center};

    init(textureCat, textureRedPoint, cat, redPoint, center);
    while (window.isOpen())
    {
        pollEvent(window, mousePosition);
        update(mousePosition, clock, cat, redPoint);
        redrawFrame(window, cat, redPoint);
    }
}