#include "Particle.h"

Particle::Particle(const sf::Texture& tex, const sf::Color& kolor, const float& dirx, const float& diry, const int& _x, const int& _y, const float& _lifeDuration) : direction(dirx, diry), lifeDuration(_lifeDuration), withSprite(_x, _y)
{
	sprite.getSprite().setTexture(tex);
	sprite.getSprite().setPosition(sf::Vector2f(_x - tex.getSize().x / 2, _y - tex.getSize().y / 2));
	sprite.getSprite().setColor(kolor);
}

void Particle::process(sf::Event event)
{

}

void Particle::update()
{
	move(direction.x, direction.y);
}