#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <iostream>

#define WIDTH 1600
#define HEIGHT 900

#define FRAMETIME 16666

using namespace std;

int main()
{
    float r_time=0;
    sf::Clock zegar;
    sf::Clock zegar2;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        if (zegar2.getElapsedTime().asMicroseconds() >= FRAMETIME - r_time) {
            zegar2.restart();
            zegar.restart();

            window.clear();

            window.display();

            r_time=zegar.getElapsedTime().asMicroseconds();
        }
    }

    return 0;
}
