#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({700, 750}), "house");

    window.clear();

    sf::RectangleShape side;
    side.setPosition({100, 450});
    side.setSize({500, 275});
    side.setFillColor(sf::Color(77, 46, 11));
    window.draw(side);

    sf::RectangleShape door;
    door.setPosition({150, 525});
    door.setSize({100, 200});
    door.setFillColor(sf::Color(24, 23, 23));
    window.draw(door);

    sf::ConvexShape roof;
    roof.setPosition({350, 300});
    roof.setPointCount(4);
    roof.setPoint(0, {-150, 0});
    roof.setPoint(1, {150, 0});
    roof.setPoint(2, {325, 150});
    roof.setPoint(3, {-325, 150});
    roof.setFillColor(sf::Color(93, 30, 23));
    window.draw(roof);

    sf::CircleShape smoke1(25);
    smoke1.setPosition(450, 188);
    smoke1.setFillColor(sf::Color(191, 191, 191));
    window.draw(smoke1);

    sf::CircleShape smoke2(30);
    smoke2.setPosition(463, 138);
    smoke2.setFillColor(sf::Color(191, 191, 191));
    window.draw(smoke2);

    sf::CircleShape smoke3(44);
    smoke3.setPosition(488, 80);
    smoke3.setFillColor(sf::Color(191, 191, 191));
    window.draw(smoke3);

    sf::CircleShape smoke4(50);
    smoke4.setPosition(550, 25);
    smoke4.setFillColor(sf::Color(191, 191, 191));
    window.draw(smoke4);

    sf::RectangleShape flue1;
    flue1.setPosition({425, 225});
    flue1.setSize({75, 50});
    flue1.setFillColor(sf::Color(59, 56, 56));
    window.draw(flue1);

    sf::RectangleShape flue2;
    flue2.setPosition({438, 275});
    flue2.setSize({49, 75});
    flue2.setFillColor(sf::Color(59, 56, 56));
    window.draw(flue2);

    window.display();

    sf::sleep(sf::seconds(5));
}