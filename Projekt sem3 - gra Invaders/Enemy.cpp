#include "Enemy.h"
#include "ObiektGraficzny.h"
#include "Bullet.h"
#include "Holder.h"

#include <iostream>

float Enemy::timeToUpdatePosition = 0.0f;

sf::Clock Enemy::deployBulletClock;

sf::Clock Enemy::zegar;

void Enemy::process(sf::Event event)
{

}

void Enemy::update()
{
	if (zegar.getElapsedTime().asMicroseconds() >= timeToUpdatePosition)
	{
		List* tmp = wskNaObiekty->get();
		while (tmp)
		{
			Enemy* enemyObject = dynamic_cast<Enemy*>(tmp->obj);

			if (enemyObject)
			{
				enemyObject->move(dirx, 0);
			}

			tmp = tmp->next;
		}
		zegar.restart();
	}

	if (deployBulletClock.getElapsedTime().asMilliseconds() >= 600 + rand() % 100 - 50 && rand()% 100 == 0)
	{
		ObiektGraficzny* pocisk = new Bullet(holder::get().textures.get("bullet"), x, y, 12, false);
		wskNaObiekty->add(pocisk);

		deployBulletClock.restart();
	}

}

Enemy::Enemy(Lista* wskNaObiekt, sf::Texture& texture, const int& _x, const int& _y, const float& updateTime, const float& velocity, const int& value) : Entity(velocity, wskNaObiekt, _x, _y), points(value)
{
	switch (value)
	{
	case 30:
	{
		type = enemyType::firstEnemy;
	} break;
	case 60:
	{
		type = enemyType::secondEnemy;
	} break;
	case 90:
	{
		type = enemyType::thirdEnemy;
	} break;
	case 120:
	{
		type = enemyType::thirdEnemy;
	} break;
	default:
	{
		type = enemyType::unknown;
	} break;
	}

	left = velocity > 0 ? false : true;
	timeToUpdatePosition = updateTime;

	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(_x - texture.getSize().x / 2, _y - texture.getSize().y / 2));
}