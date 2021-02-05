#ifndef WITHSPRITE
#define WITHSPRITE

#include "includes.h"
#include "ObiektGraficzny.h"
#include "Animation.h"

//TODO pozbyæ siê wirtualnego dziedziczenia
class withSprite : public ObiektGraficzny
{
protected:
	Animation sprite;
public:
	withSprite(const int& x, const int& y) : ObiektGraficzny(x, y)
	{

	}

	virtual void save(std::ostream& os) override
	{

	}

	sf::FloatRect getBounds();

	void draw(sf::RenderWindow& window) override;

	virtual void move(float x_offset, float y_offset);

	friend class GameManager;
};

#endif
