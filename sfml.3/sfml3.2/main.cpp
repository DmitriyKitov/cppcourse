#include <sfml/graphics.hpp>
#include <cmath>

struct Eye
{
    sf::ConvexShape white;
    sf::ConvexShape apple;
    sf::Vector2f position;
    float rotation = 0;
};

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

void drawEllipse(sf::ConvexShape &ellipse, float radiusX, float radiusY)
{
    constexpr int pointCount = 360;
    ellipse.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            radiusX * std::sin(angle),
            radiusY * std::cos(angle)};
        ellipse.setPoint(pointNo, point);
    }
}

void initEyes(Eye &leftEye, Eye &rightEye)
{
    leftEye.position = {300, 300};
    rightEye.position = {500, 300};

    leftEye.white.setPosition(leftEye.position);
    drawEllipse(leftEye.white, 80, 160);

    rightEye.white.setPosition(rightEye.position);
    drawEllipse(rightEye.white, 80, 160);

    leftEye.apple.setPosition(leftEye.position);
    leftEye.apple.setFillColor(sf::Color(0, 0, 0));
    drawEllipse(leftEye.apple, 20, 40);

    rightEye.apple.setPosition(rightEye.position);
    rightEye.apple.setFillColor(sf::Color(0, 0, 0));
    drawEllipse(rightEye.apple, 20, 40);
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
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

sf::Vector2f toEuclidian(float radiusX, float radiusY, float angle)
{
    return {
        radiusX * float(cos(angle)),
        radiusY * float(sin(angle))};
}

void update(const sf::Vector2f &mousePosition, Eye &leftEye, Eye &rightEye)
{
    const sf::Vector2f leftEyeDelta = mousePosition - leftEye.position;
    leftEye.rotation = atan2(leftEyeDelta.y, leftEyeDelta.x);

    const sf::Vector2f rightEyeDelta = mousePosition - rightEye.position;
    rightEye.rotation = atan2(rightEyeDelta.y, rightEyeDelta.x);

    constexpr float rotationRadiusX = 40;
    constexpr float rotationRadiusY = 80;

    const sf::Vector2f leftEyeOffset = toEuclidian(rotationRadiusX, rotationRadiusY, leftEye.rotation);
    leftEye.apple.setPosition(leftEye.position + leftEyeOffset);

    const sf::Vector2f rightEyeOffset = toEuclidian(rotationRadiusX, rotationRadiusY, rightEye.rotation);
    rightEye.apple.setPosition(rightEye.position + rightEyeOffset);
}

void redrawFrame(sf::RenderWindow &window, Eye &leftEye, Eye &rightEye)
{
    window.clear();
    window.draw(leftEye.white);
    window.draw(leftEye.apple);
    window.draw(rightEye.white);
    window.draw(rightEye.apple);
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
        "eye movement behind the mouse", sf::Style::Default, settings);

    Eye leftEye;
    Eye rightEye;
    sf::Vector2f mousePosition;

    initEyes(leftEye, rightEye);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, leftEye, rightEye);
        redrawFrame(window, leftEye, rightEye);
    }
}