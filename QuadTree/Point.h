#ifndef POINT
#define POINT

#include <SFML/System/Vector2.hpp>

class Point
{
	float x, y;
	public:
	Point(float, float);

	Point(sf::Vector2f);

	float getX() { return x; };

	float getY() { return y; };
};

#endif