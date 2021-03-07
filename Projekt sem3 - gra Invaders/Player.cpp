#include "Player.h"
#include "holder.h"
#include <vector>
#include <iostream>

void Player::process(sf::Event event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		moving = true;
		dirx = -abs(dirx);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		moving = true;
		dirx = abs(dirx);
	}
	else
		moving = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		shoot = true;
	else
		shoot = false;
}

void Player::update()
{
	if (moving)
		move(dirx, 0);

	if (sprite.getPosition().x + sprite.getTextureRect().width >= WIDTH || sprite.getPosition().x <= 0)
		move(-dirx, 0);

	if (shoot && shootCooldown.getElapsedTime().asMicroseconds() >= 16666 * 50)
	{
		ObiektGraficzny* pocisk = new Bullet(holder::get().textures.get("bullet"), x + sprite.getTexture()->getSize().x / 2 - holder::get().textures.get("bullet").getSize().x / 2, y - sprite.getTexture()->getSize().y, -8, true);
		wskNaObiekty->add(pocisk);
		shoot = false;
		strzal = true;
		shootCooldown.restart();
	}
}

Player::Player(Lista* wskNaObiekty, const sf::Texture& texture, const int& _x, const int& _y, const float& velocity) : Entity(abs(velocity), wskNaObiekty, _x, _y)
{
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(_x, _y));
}