#include "Rectangle.h"

Rectangle::Rectangle(Point _p, float _width, float _height) : p(_p), width(_width), height(_height)
{

}

Rectangle::Rectangle(float _x, float _y, float _width, float _height) : p(_x, _y), width(_width), height(_height)
{

}