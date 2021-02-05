#ifndef OBIEKTGRAFICZNY
#define OBIEKTGRAFICZNY

#include "includes.h"

class ObiektGraficzny
{
protected:
	int x, y;
public:
	virtual void process(sf::Event event) = 0;

	virtual void draw(sf::RenderWindow& window) = 0;

	virtual void update() = 0;

	virtual void save(std::ostream& os) = 0;

	ObiektGraficzny(const int& _x, const int& _y) : x(_x), y(_y)
	{

	}

	ObiektGraficzny() : x(0), y(0)
	{

	}

	friend class GameManager;
};

#endif