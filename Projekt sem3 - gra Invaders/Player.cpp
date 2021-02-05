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
	sprite.update();

	if (moving)
		move(dirx, 0);

	if (sprite.getSprite().getPosition().x + sprite.getSprite().getTextureRect().width >= WIDTH || sprite.getSprite().getPosition().x <= 0)
		move(-dirx, 0);

	if (shoot && shootCooldown.getElapsedTime().asMicroseconds() >= 16666 * 50)
	{
		ObiektGraficzny* pocisk = new Bullet(holder::get().textures.get("bullet"), x - holder::get().textures.get("bullet").getSize().x / 2, y - sprite.getSprite().getTexture()->getSize().y, -8, true);
		wskNaObiekty->add(pocisk);
		shoot = false;
		strzal = true;
		shootCooldown.restart();
	}
}

Player::Player(Lista* wskNaObiekty, const sf::Texture& texture, const int& _x, const int& _y, const float& velocity) : Entity(abs(velocity), wskNaObiekty, _x, _y)
{
	sprite.addFrame(sf::IntRect(0, 0, 99, 61));
	sprite.addFrame(sf::IntRect(100, 0, 99, 61));
	sprite.setFrameTime(sf::seconds(0.5));

	sprite.getSprite().setTexture(texture);
	sprite.getSprite().setPosition(sf::Vector2f(_x - texture.getSize().x / 4, _y - texture.getSize().y / 2));
}