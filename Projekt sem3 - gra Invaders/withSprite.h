#ifndef WITHSPRITE
#define WITHSPRITE

#include "includes.h"
#include "ObiektGraficzny.h"

//TODO pozby� si� wirtualnego dziedziczenia
class withSprite : public ObiektGraficzny
{
protected:
	sf::Sprite sprite;
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
