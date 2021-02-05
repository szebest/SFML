#ifndef ANIMATION
#define ANIMATION

#include "includes.h"
#include <vector>

class Animation
{
	sf::Clock zegar;
	sf::Time frameTime;
	sf::Sprite sprite;
	std::vector<sf::IntRect> bounds;
	int currFrame = 0;
public:
	sf::Sprite& getSprite() { return sprite; }

	void addFrame(sf::IntRect rect)
	{
		bounds.push_back(rect);
		sprite.setTextureRect(bounds[currFrame]);
	}

	void setFrameTime(sf::Time time)
	{
		frameTime = time;
	}

	void setTexture(const sf::Texture& tex)
	{
		sprite.setTexture(tex);
	}

	void update()
	{
		if (zegar.getElapsedTime() >= frameTime && bounds.size() > 0)
		{
			currFrame++;
			if (currFrame == bounds.size())
				currFrame = 0;
			
			sprite.setTextureRect(bounds[currFrame]);

			zegar.restart();
		}
	}

	Animation(const int& x, const int& y, const sf::Time& czas, const sf::Texture& tex) : frameTime(czas)
	{
		sprite.setTexture(tex);
		sprite.setPosition(x, y);
	}

	Animation()
	{

	}

	friend class Enemy;
};

#endif

