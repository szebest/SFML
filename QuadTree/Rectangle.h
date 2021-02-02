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
};

#endif
