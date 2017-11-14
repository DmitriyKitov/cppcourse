#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({120, 320}), "traffic light");

    window.clear();
    sf::RectangleShape body;
    body.setSize({100, 300});
    body.setPosition({10, 10});
    body.setFillColor(sf::Color(0x60, 0x60, 0x60));
    window.draw(body);

    sf::CircleShape green(40);
    green.setPosition({20, 20});
    green.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(green);

    sf::CircleShape yellow(40);
    yellow.setPosition({20, 120});
    yellow.setFillColor(sf::Color(0xFF, 0xFF, 0x0));
    window.draw(yellow);

    sf::CircleShape red(40);
    red.setPosition({20, 220});
    red.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(red);

    window.display();

    sf::sleep(sf::seconds(5));
}