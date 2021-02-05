#ifndef BARRIER
#define BARRIER

#include "withSprite.h"

class Barrier : public withSprite
{
public:
	void update() override;

	void process(sf::Event event) override;

	virtual void save(std::ostream& os) override
	{
		os << "Barrier " << x << " " << y << '\n';
	}

	Barrier(const int& x, const int& y, const sf::Texture& tex);
};

#endif 