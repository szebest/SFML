#include "Barrier.h"

void Barrier::update()
{

}

void Barrier::process(sf::Event event)
{

}

Barrier::Barrier(const int& x, const int& y, const sf::Texture& tex) : withSprite(x, y)
{
	sprite.getSprite().setPosition(sf::Vector2f(x, y));
	sprite.getSprite().setTexture(tex);
}