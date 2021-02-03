#ifndef QUADTREE
#define QUADTREE

#include <vector>
#include <SFML/Graphics.hpp>
#include "Rectangle.h"
#include "Point.h"

class QuadTree
{
	int capacity;
	Rectangle rect;
	QuadTree* northWest=nullptr;
	QuadTree* northEast=nullptr;
	QuadTree* southWest=nullptr;
	QuadTree* southEast=nullptr;
	std::vector<Point> points;

	void divide();
	public:
	QuadTree(Rectangle, int);

	~QuadTree();

	void insert(Point);

	std::vector<Point> getPointsInsideRange(Rectangle);

	void drawRectangles(sf::RenderWindow &window);

	Rectangle getRect() { return rect; }
};

#endif