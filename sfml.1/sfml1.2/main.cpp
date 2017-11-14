#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({495, 270}), "initials");

    window.clear();

    //draw D

    sf::CircleShape d1(105);
    d1.setPosition({105, 30});
    window.draw(d1);

    sf::CircleShape d2(75);
    d2.setPosition({135, 60});
    d2.setFillColor(sf::Color(0, 0, 0));
    window.draw(d2);

    sf::RectangleShape d3;
    d3.setSize({30, 210});
    d3.setPosition({180, 30});
    window.draw(d3);

    sf::RectangleShape d4;
    d4.setSize({75, 210});
    d4.setPosition({105, 30});
    d4.setFillColor(sf::Color(0, 0, 0));
    window.draw(d4);

    //draw K

    sf::RectangleShape k1;
    k1.setSize({30, 210});
    k1.setPosition({30, 30});
    window.draw(k1);

    sf::RectangleShape k2;
    k2.setSize({30, 148});
    k2.setRotation(45);
    k2.setPosition({135, 30});
    window.draw(k2);

    sf::RectangleShape k3;
    k3.setSize({30, 148});
    k3.setRotation(-45);
    k3.setPosition({30, 135});
    window.draw(k3);

    //draw S

    sf::CircleShape s1(60);
    s1.setPosition({345, 30});
    window.draw(s1);

    sf::CircleShape s2(30);
    s2.setPosition({375, 60});
    s2.setFillColor(sf::Color(0, 0, 0));
    window.draw(s2);

    sf::RectangleShape s3;
    s3.setSize({60, 90});
    s3.setPosition({405, 60});
    s3.setFillColor(sf::Color(0, 0, 0));
    window.draw(s3);

    sf::RectangleShape s4;
    s4.setSize({60, 30});
    s4.setPosition({405, 30});
    window.draw(s4);

    sf::CircleShape s5(60);
    s5.setPosition({345, 120});
    window.draw(s5);

    sf::CircleShape s6(30);
    s6.setPosition({375, 150});
    s6.setFillColor(sf::Color(0, 0, 0));
    window.draw(s6);

    sf::RectangleShape s7;
    s7.setSize({60, 60});
    s7.setPosition({345, 150});
    s7.setFillColor(sf::Color(0, 0, 0));
    window.draw(s7);

    sf::RectangleShape s8;
    s8.setSize({60, 30});
    s8.setPosition({345, 210});
    window.draw(s8);

    sf::RectangleShape s9;
    s7.setSize({30, 60});
    s7.setPosition({405, 150});
    s7.setRotation(110);
    s7.setFillColor(sf::Color(0, 0, 0));
    window.draw(s7);

    window.display();

    sf::sleep(sf::seconds(5));
}