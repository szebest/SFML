#ifndef PLAYER
#define PLAYER

#include "ObiektGraficzny.h"
#include "Entity.h"
#include "Bullet.h"

class Player : public Entity
{
	bool moving = false;
	bool shoot = false;
	bool strzal = false;

	sf::Clock shootCooldown;
public:
	void process(sf::Event event) override;

	void update() override;

	virtual void save(std::ostream& os) override
	{
		os << "Player " << x << " " << y << " " << dirx << " " << '\n';
	}

	Player(Lista* wskNaObiekty, const sf::Texture& texture, const int& _x, const int& _y, const float& velocity);

	friend class GameManager;
};

#endif 