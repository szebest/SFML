#include "withSprite.h"

sf::FloatRect withSprite::getBounds()
{
	return sprite.getGlobalBounds();
}

void withSprite::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void withSprite::move(float x_offset, float y_offset)
{
	x += x_offset;
	y += y_offset;
	sprite.move(x_offset, y_offset);
}