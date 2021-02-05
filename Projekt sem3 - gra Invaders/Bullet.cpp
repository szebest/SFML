#include "Bullet.h"
#include "defines.h"
#include "Holder.h"
#include "Barrier.h"

Bullet::Bullet(const sf::Texture& texture, const int& _x, const int& _y, const int& _ydir, bool whoShot) : shotByPlayer(whoShot), diry(_ydir), withSprite(_x, _y)
{
	sprite.getSprite().setTexture(texture);
	sprite.getSprite().setPosition(_x, _y);
}

void Bullet::update()
{
	move(0, diry);
}

void Bullet::process(sf::Event event)
{

}