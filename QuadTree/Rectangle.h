#ifndef RECTANGLE
#define RECTANGLE

#include "Point.h"

class Rectangle
{
	Point p;
	float width, height;
	public:
	Rectangle(Point, float, float);

	Rectangle(float, float, float, float);

	bool contains(Point);

	bool overlap(Rectangle);

	Point getPoint() { return p; }

	float getWidth() { return width; }

	float getHeight() { return height; }
};

#endif
