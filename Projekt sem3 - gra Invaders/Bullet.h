#ifndef BULLET
#define BULLET

#include "Struktury.h"
#include "withSprite.h"
#include "Enemy.h"

class Bullet : public withSprite
{
protected:
	float diry;
	bool shotByPlayer;
public:
	Bullet(const sf::Texture& texture, const int& _x, const int& _y, const int& _ydir, bool whoShot);

	void update() override;

	virtual void save(std::ostream& os) override
	{
		os << "Bullet " << x << " " << y << " " << diry << '\n';
	}

	void process(sf::Event event) override;

	friend class GameManager;
};

#endif 