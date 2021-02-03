#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>

#include "QuadTree.h"
#include "Functions.h"

#define WIDTH 1600
#define HEIGHT 900

#define FRAMETIME 16666

using namespace std;

int main()
{
	srand(time(NULL));
    float r_time=0;
    sf::Clock zegar;
    sf::Clock zegar2;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML");

	QuadTree q(Rectangle(0, 0, WIDTH, HEIGHT), 4);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					q.insert(Point((sf::Vector2f)sf::Mouse::getPosition(window)));
				}
			}
        }

        if (zegar2.getElapsedTime().asMicroseconds() >= FRAMETIME - r_time) {
            zegar2.restart();
            zegar.restart();

			std::vector<Point> points = q.getPointsInsideRange(Rectangle(0, 0, WIDTH, HEIGHT));

            window.clear(sf::Color::Black);

			for (int i = 0; i < points.size(); i++)
			{
				sf::Vertex point(sf::Vector2f(points[i].getX(), points[i].getY()), sf::Color::White);
				window.draw(&point, 1, sf::Points);
			}

			q.drawRectangles(window);

            window.display();

            r_time=zegar.getElapsedTime().asMicroseconds();
        }
    }

    return 0;
}
