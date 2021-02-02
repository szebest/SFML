#ifndef QUADTREE
#define QUADTREE

#include <vector>
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
};

#endif