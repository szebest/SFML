#include "QuadTree.h"

QuadTree::QuadTree(Rectangle _rect, int _capacity) : rect(_rect), capacity(_capacity)
{

}

QuadTree::~QuadTree()
{
	delete northWest;
	delete northEast;
	delete southWest;
	delete southEast;
}

void QuadTree::insert(Point p)
{
	if (!rect.contains(p))
		return;

	if (points.size() < capacity && northEast == nullptr)
	{
		points.push_back(p);
		return;
	}

	if (northEast == nullptr)
		divide();

	northWest->insert(p);
	northEast->insert(p);
	southWest->insert(p);
	southEast->insert(p);
}

void QuadTree::divide()
{
	float x = rect.getPoint().getX();
	float y = rect.getPoint().getY();
	float w = rect.getWidth();
	float h = rect.getHeight();
	northWest = new QuadTree(Rectangle(x + w/2, y, w/2, h/2), capacity);
	northEast = new QuadTree(Rectangle(x, y, w/2, h/2), capacity);
	southWest = new QuadTree(Rectangle(x + w/2, y + h/2, w/2, h/2), capacity);
	southEast = new QuadTree(Rectangle(x, y + h/2, w/2, h/2), capacity);
}