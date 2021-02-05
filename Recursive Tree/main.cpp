#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <iostream>

#define M_PI 3.14159265358979323846

#define WIDTH 1600
#define HEIGHT 900

#define FRAMETIME 16666

using namespace std;

void draw(float len, float angle, sf::Vector2f& point, sf::RenderWindow& window) {
	//calculate the offset between the first and second point
	float x = cos(angle * M_PI / 180.f) * len;
	float y = sin(angle * M_PI / 180.f) * len;
	//apply the position of the first point
	sf::Vertex linia2[2];
	linia2[0].position = point;
	linia2[0].color = sf::Color::White;
	//calculate the position of the second point
	point = { point.x + x, point.y + y };
	//apply the position of the second point
	linia2[1].position = point;
	linia2[1].color = sf::Color::White;
	//draw the line
	window.draw(linia2, 2, sf::Lines);
}

void rotate(float& angle, float rotation) {
	//apply the rotation
	angle += rotation;
	//Keep it in the range from -360 to 360 degrees
	if (angle >= 360)
		angle -= 360;
	if (angle <= -360)
		angle += 360;
}

void drawTree(float length, float mini, float angle, float rotation, sf::Vector2f startingPosition, sf::RenderWindow& window) {
	//exit condtion
	if (mini < 0)
		mini *= -1;
	if (length < mini) 
		return;
	else {
		//draw the line
		draw(length, angle, startingPosition, window);
		//rotate
		rotate(angle, rotation);
		//recursion
		drawTree(length / 4 * 3, mini, angle, rotation, startingPosition, window);
		//rotate 2 times in the other direction
		rotate(angle, -2*rotation);
		//recursion
		drawTree(length / 4 * 3, mini, angle, rotation, startingPosition, window);
		//rotate back
		rotate(angle, rotation);
	}
}

int main()
{
    float r_time=0;
    sf::Clock zegar;
    sf::Clock zegar2;


	float rotation = 0;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        if (zegar2.getElapsedTime().asMicroseconds() >= FRAMETIME - r_time) {
            zegar2.restart();
            zegar.restart();

			rotation += 1;

            window.clear();

			drawTree(250, 4, -90, rotation, {WIDTH / 2, HEIGHT * 0.95},  window);

            window.display();

            r_time=zegar.getElapsedTime().asMicroseconds();

			std::cout << r_time << std::endl;
        }
    }

    return 0;
}
