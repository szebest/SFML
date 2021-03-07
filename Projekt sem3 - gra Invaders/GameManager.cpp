#include "GameManager.h"
#include "Enemy.h"
#include "Player.h"
#include "Button.h"
#include "Holder.h"
#include "Defines.h"
#include "Funkcje.h"
#include <sstream>
#include <fstream>

#include <iostream>

GameManager::GameManager(Window* ptr) : ptrToWindow(ptr)
{
	holder::get().sounds.add("click");

	createMenu();

	state = GameState::Menu;

	score = 0;
	hp = 3;
}

GameManager::~GameManager()
{

}

void GameManager::createGame(int* score, int* hp, const int& x, const int& y)
{
	drawable.usun();

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			sf::Texture& tex = j == 3 ? holder::get().textures.get("enemy1") : j == 2 ? holder::get().textures.get("enemy2") : holder::get().textures.get("enemy3");

			drawable.add(new Enemy(&drawable, tex, 100 + 125 * i, 100 + 100 * j, 1000000, 50, 30 * (4 - j)));
		}
	}

	drawable.add(new Player(&drawable, holder::get().textures.get("player"), x, y, 5));
	drawable.add(new Text("Punkty: ", holder::get().fonts.get("arial"), 32, sf::Color::Red, 80, 32, score, true));
	drawable.add(new Text("Hp: ", holder::get().fonts.get("arial"), 32, sf::Color::Red, WIDTH - 160, 32, hp, true));
}

void GameManager::createMenu()
{
	drawable.usun();
	drawable.add(new Button("Start", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 200, 200, 60, ButtonType::SelectMenu, NULL, sf::Color::White));
	drawable.add(new Button("Exit", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 300, 200, 60, ButtonType::ExitGame, NULL, sf::Color::White));
}

void GameManager::createPause()
{
	drawable.usun();
	drawable.add(new Button("Return", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 200, 200, 60, ButtonType::ResumeGame, NULL, sf::Color::White));
	drawable.add(new Button("Menu", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 300, 200, 60, ButtonType::Menu, NULL, sf::Color::White));
	drawable.add(new Button("Save", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 400, 200, 60, ButtonType::SaveGame, NULL, sf::Color::White));
	drawable.add(new Button("Exit", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 500, 200, 60, ButtonType::ExitGame, NULL, sf::Color::White));
}

void GameManager::createSelectMenu()
{
	drawable.usun();
	drawable.add(new Button("New Game", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 200, 200, 60, ButtonType::StartGame, NULL, sf::Color::White));
	drawable.add(new Button("Load Game", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 300, 200, 60, ButtonType::LoadGame, NULL, sf::Color::White));
	drawable.add(new Button("Return", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 400, 200, 60, ButtonType::Menu, NULL, sf::Color::White));
}

void GameManager::gameOverScreen()
{
	drawable.usun();
	drawable.add(new Button("Return to menu", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 600, 250, 60, ButtonType::Menu, NULL, sf::Color::White));
	drawable.add(new Text("Game Over", holder::get().fonts.get("arial"), 64, sf::Color::Red, WIDTH / 2, 200, NULL, true));
}

void GameManager::checkCollisions()
{
	List* tmp = drawable.get();
	while (tmp)
	{
		Bullet* bulletObject = dynamic_cast<Bullet*>(tmp->obj);

		if (bulletObject)
		{
			List* tmp2 = drawable.get();
			while (tmp2)
			{
				if (tmp != tmp2)
				{
					Enemy* enemyObject = dynamic_cast<Enemy*>(tmp2->obj);
					if (enemyObject)
					{
						if (bulletObject->getBounds().intersects(enemyObject->getBounds()) && bulletObject->shotByPlayer)
						{
							enemyObject->timeToUpdatePosition *= 0.94;
							score += enemyObject->points;
							drawable.erase(bulletObject);
							drawable.erase(enemyObject);

							addSound(holder::get().sounds.get("explosion"));

							return;
						}
					}
					else
					{
						Bullet* otherBulletObject = dynamic_cast<Bullet*>(tmp2->obj);
						if (otherBulletObject)
						{
							if (bulletObject->getBounds().intersects(otherBulletObject->getBounds()) && bulletObject->shotByPlayer != otherBulletObject->shotByPlayer)
							{
								drawable.erase(bulletObject);
								drawable.erase(otherBulletObject);

								addSound(holder::get().sounds.get("explosion"));

								return;
							}
						}
						else
						{
							Player* playerObject = dynamic_cast<Player*>(tmp2->obj);
							if (playerObject)
							{
								if (bulletObject->getBounds().intersects(playerObject->getBounds()) && !bulletObject->shotByPlayer)
								{
									drawable.erase(bulletObject);
									hp--;

									addSound(holder::get().sounds.get("hurt"));

									return;
								}
							}
						}
					}
				}

				tmp2 = tmp2->next;
			}

			if (bulletObject)
			{
				if (bulletObject->y >= HEIGHT - bulletObject->sprite.getTexture()->getSize().y || bulletObject->y <= 0)
				{
					drawable.erase(bulletObject);

					return;
				}
			}
		}

		tmp = tmp->next;
	}
}

void GameManager::checkButtonInput()
{
	List* tmp = drawable.get();
	while (tmp)
	{
		Button* buttonObject = dynamic_cast<Button*>(tmp->obj);
		if (buttonObject)
		{
			if (buttonObject->getWasPressed())
			{
				addSound(holder::get().sounds.get("click"));

				switch (buttonObject->getButtonType())
				{
				case ButtonType::StartGame: //Starting the game
				{
					score = 0;
					hp = 3;

					createGame(&score, &hp);

					state = GameState::Playing;
				} break;
				case ButtonType::ExitGame: //Exiting the game
				{
					drawable.usun();
					ptrToWindow->window.close();
				} break;
				case ButtonType::ResumeGame:
				{
					drawable.usun();
					drawable = temporary;
					temporary.wyzeruj();
					state = GameState::Playing;
				} break;
				case ButtonType::Menu:
				{
					drawable.usun();
					createMenu();
					score = 0;
					hp = 3;
					state = GameState::Menu;
				} break;
				case ButtonType::SelectMenu:
				{
					drawable.usun();
					createSelectMenu();
				} break;
				case ButtonType::LoadGame: //load
				{
					state = GameState::Playing;
					loadGame(SAVE_FILE_GAME);
				} break;
				case ButtonType::SaveGame: //save
				{
					saveGame(SAVE_FILE_GAME);
				} break;
				default:
				{
					
				} break;
				}

				return;
			}
		}

		tmp = tmp->next;
	}
}

void GameManager::checkEnemies()
{
	bool atLeastOneEnemy = false;
	List* tmp = drawable.get();
	while (tmp)
	{
		Enemy* enemyObject = dynamic_cast<Enemy*>(tmp->obj);

		if (enemyObject)
		{
			atLeastOneEnemy = true;
			if (enemyObject->x >= WIDTH * 0.9 || enemyObject->x <= WIDTH * 0.1)
			{
				List* tmp2 = drawable.get();
				while (tmp2)
				{
					Enemy* object = dynamic_cast<Enemy*>(tmp2->obj);

					if (object)
					{
						object->dirx = enemyObject->x >= WIDTH * 0.9 ? -abs(enemyObject->dirx) : abs(enemyObject->dirx);
						if ((enemyObject->x >= WIDTH * 0.9 && !object->left) || enemyObject->x <= WIDTH * 0.1 && object->left)
						{
							object->move(0, abs(enemyObject->dirx) / 2);
							object->left = !object->left;
						}
					}

					tmp2 = tmp2->next;
				}
			}

			if (enemyObject->y >= HEIGHT / 2) //Game Lost
			{
				state = GameState::GameOver;
				gameOverScreen();
				break;
			}
		}

		tmp = tmp->next;
	}

	if (!atLeastOneEnemy && state == GameState::Playing) //Won Game
	{
		createGame(&score, &hp);

		hp = std::min(hp + 1, 3);
	}

	if (hp == 0 && state == GameState::Playing)
	{
		gameOverScreen();
		state = GameState::GameOver;
	}
}

void GameManager::addSound(const sf::SoundBuffer& buffer)
{
	sf::Sound sound;
	sound.setBuffer(buffer);
	sounds.push_back(sound);
	sounds[sounds.size() - 1].play();
}

void GameManager::checkSounds()
{
	List* tmp = drawable.get();
	while (tmp)
	{
		Player* playerObject = dynamic_cast<Player*>(tmp->obj);

		if (playerObject)
		{
			if (playerObject->strzal == true)
			{
				addSound(holder::get().sounds.get("shoot"));
				playerObject->strzal = false;
			}
		}

		tmp = tmp->next;
	}

	for (int i = 0; i < sounds.size(); i++)
	{
		if (sounds[i].getStatus() == sf::Sound::Stopped)
		{
			sounds.erase(sounds.begin() + i);

			i = sounds.size();
		}
	}
}

void GameManager::saveGame(const std::string& filePath)
{
	std::ofstream plik(filePath);

	plik << score << " " << hp << '\n';

	List* tmp = temporary.get();
	while (tmp)
	{
		tmp->obj->save(plik);

		tmp = tmp->next;
	}

	plik.close();
}

void GameManager::loadGame(const std::string& filePath)
{
	drawable.usun();

	std::ifstream plik(filePath);

	plik >> score >> hp;

	drawable.add(new Text("Punkty: ", holder::get().fonts.get("arial"), 32, sf::Color::Red, 80, 32, &score, true));
	drawable.add(new Text("Hp: ", holder::get().fonts.get("arial"), 32, sf::Color::Red, WIDTH - 160, 32, &hp, true));

	std::string type;
	
	while (plik>>type)
	{
		if (type == "Enemy")
		{
			//Change texture with respect to the type value
			int x, y, dirx, timeToUpdatePosition, points;
			plik >> x >> y >> dirx >> timeToUpdatePosition >> points;
			sf::Texture& tex=points == 30 ? holder::get().textures.get("enemy1") : points == 60 ? holder::get().textures.get("enemy2") : holder::get().textures.get("enemy3");
			drawable.add(new Enemy(&drawable, tex, x, y, timeToUpdatePosition, dirx, points));
		}
		else if (type == "Player")
		{
			int x, y, dirx;
			plik >> x >> y >> dirx;
			drawable.add(new Player(&drawable, holder::get().textures.get("player"), x, y, dirx));
		}
		else if (type == "Bullet")
		{
			int x, y, diry;
			plik >> x >> y >> diry;
			drawable.add(new Bullet(holder::get().textures.get("bullet"), x, y, diry, diry < 0));
		}
	}
}