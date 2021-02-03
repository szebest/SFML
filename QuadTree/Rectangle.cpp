#include "Rectangle.h"

Rectangle::Rectangle(Point _p, float _width, float _height) : p(_p), width(_width), height(_height)
{

}

Rectangle::Rectangle(float _x, float _y, float _width, float _height) : p(_x, _y), width(_width), height(_height)
{

}

bool Rectangle::contains(Point point)
{
	return	(point.getX() >= p.getX() &&
			point.getX() < p.getX() + width &&
			point.getY() >= p.getY() &&
			point.getY() < p.getY() + height);
}

bool Rectangle::overlap(Rectangle other)
{
	if (p.getX() >= other.getPoint().getX() + other.getWidth() ||
		other.getPoint().getX() >= p.getX() + width)
		return false;

	if (p.getY() >= other.getPoint().getY() + other.getHeight() ||
		other.getPoint().getY() >= p.getY() + height)
		return false;

	return true;
}