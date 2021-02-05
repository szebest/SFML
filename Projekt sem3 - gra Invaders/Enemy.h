#ifndef ENEMY
#define ENEMY

#include "Struktury.h"
#include "Defines.h"
#include "Entity.h"

class Enemy : public Entity
{
	enum enemyType
	{
		firstEnemy,
		secondEnemy,
		thirdEnemy,
		unknown
	} type;

protected:
	static sf::Clock zegar;
	static sf::Clock deployBulletClock;
	bool left;
	static float timeToUpdatePosition;
	int points;
public:
	void process(sf::Event event) override;

	void update() override;

	virtual void save(std::ostream& os) override
	{
		os << "Enemy " << x << " " << y << " " << dirx << " " << timeToUpdatePosition << " " << points << '\n';
	}

	Enemy(Lista* wskNaObiekty, sf::Texture& texture, const int& _x, const int& _y, const float& updateTime, const float& velocity, const int& value);

	friend class GameManager;
};

#endif 