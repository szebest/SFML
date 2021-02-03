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

void QuadTree::divide()
{
	float x = rect.getPoint().getX();
	float y = rect.getPoint().getY();
	float w = rect.getWidth();
	float h = rect.getHeight();
	northWest = new QuadTree(Rectangle(x + w / 2, y, w / 2, h / 2), capacity);
	northEast = new QuadTree(Rectangle(x, y, w / 2, h / 2), capacity);
	southWest = new QuadTree(Rectangle(x + w / 2, y + h / 2, w / 2, h / 2), capacity);
	southEast = new QuadTree(Rectangle(x, y + h / 2, w / 2, h / 2), capacity);
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

std::vector<Point> QuadTree::getPointsInsideRange(Rectangle _rect)
{
	std::vector<Point> p;

	if (!rect.overlap(_rect))
		return p;

	for (int i = 0; i < points.size(); i++)
		if (_rect.contains(points[i]))
			p.push_back(points[i]);

	if (northEast == nullptr)
		return p;

	std::vector<Point> nw = northWest->getPointsInsideRange(northWest->getRect());
	std::vector<Point> ne = northEast->getPointsInsideRange(northEast->getRect());
	std::vector<Point> sw = southWest->getPointsInsideRange(southWest->getRect());
	std::vector<Point> se = southEast->getPointsInsideRange(southEast->getRect());

	p.insert(p.end(), nw.begin(), nw.end());
	p.insert(p.end(), ne.begin(), ne.end());
	p.insert(p.end(), sw.begin(), sw.end());
	p.insert(p.end(), se.begin(), se.end());

	return p;
}

void QuadTree::drawRectangles(sf::RenderWindow& window)
{
	sf::RectangleShape r;
	r.setPosition(sf::Vector2f(rect.getPoint().getX(), rect.getPoint().getY()));
	r.setSize(sf::Vector2f(rect.getWidth(), rect.getHeight()));
	r.setFillColor(sf::Color::Transparent);
	r.setOutlineColor(sf::Color::Blue);
	r.setOutlineThickness(1);

	window.draw(r);

	if (northEast == nullptr)
		return;

	northWest->drawRectangles(window);
	northEast->drawRectangles(window);
	southWest->drawRectangles(window);
	southEast->drawRectangles(window);
}