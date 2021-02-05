#ifndef PARTICLE
#define PARTICLE

#include "includes.h"
#include "withSPrite.h"
#include "Struktury.h"

class Particle : public withSprite
{
protected:
	sf::Vector2f direction;
	sf::Clock zegar;
	float lifeDuration;
public:
	Particle(const sf::Texture& tex, const sf::Color& kolor, const float& dirx, const float& diry, const int& _x, const int& _y, const float& _lifeDuration);

	void process(sf::Event event) override;

	void update() override;

	friend class GameManager;
};

#endif 