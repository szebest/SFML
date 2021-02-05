#include "GameManager.h"
#include "Enemy.h"
#include "Player.h"
#include "Button.h"
#include "Particle.h"
#include "Holder.h"
#include "InputForm.h"
#include "Barrier.h"
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

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				drawable.add(new Barrier(100 + i * ((WIDTH - 500) / 4 + 100) + j * 70, HEIGHT * 3 / 5 + k * 70, holder::get().textures.get("bariera")));

	drawable.add(new Player(&drawable, holder::get().textures.get("player"), x, y, 5));
	drawable.add(new Text("Punkty: ", holder::get().fonts.get("arial"), 32, sf::Color::Red, 80, 32, score, true));
	drawable.add(new Text("Hp: ", holder::get().fonts.get("arial"), 32, sf::Color::Red, WIDTH - 160, 32, hp, true));
}

void GameManager::createMenu()
{
	drawable.usun();
	drawable.add(new Button("Start", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 200, 200, 60, 6, NULL, sf::Color::White));
	drawable.add(new Button("Highscores", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 300, 200, 60, 5, NULL, sf::Color::White));
	drawable.add(new Button("Exit", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 400, 200, 60, 1, NULL, sf::Color::White));
}

void GameManager::createPause()
{
	drawable.usun();
	drawable.add(new Button("Return", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 200, 200, 60, 2, NULL, sf::Color::White));
	drawable.add(new Button("Menu", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 300, 200, 60, 3, NULL, sf::Color::White));
	drawable.add(new Button("Save", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 400, 200, 60, 8, NULL, sf::Color::White));
	drawable.add(new Button("Exit", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 500, 200, 60, 1, NULL, sf::Color::White));
}

void GameManager::createSelectMenu()
{
	drawable.usun();
	drawable.add(new Button("New Game", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 200, 200, 60, 0, NULL, sf::Color::White));
	drawable.add(new Button("Load Game", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 300, 200, 60, 7, NULL, sf::Color::White));
	drawable.add(new Button("Return", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 400, 200, 60, 3, NULL, sf::Color::White));
}

void GameManager::createParticles(const int& n, const int& x, const int& y, sf::Color kolor)
{
	for (int i = 0; i < n; i++)
		drawable.add(new Particle(holder::get().textures.get("particle"), kolor, (rand() % 10 - 5) / 5.f, (rand() % 10 - 5) / 5.f, x + rand() % 50 - 25, y + rand() % 50 - 25, (16666 + rand() % 8000 - 4000) * 60));
}

bool GameManager::newHighscore(const int& score, const std::string& filePath)
{
	//implement score check here

	std::ifstream plik(filePath);

	std::string nazwa;
	int wynik;

	int highscoreAmount = 0;

	while (plik >> nazwa >> wynik)
	{
		highscoreAmount++;
		if (score > wynik)
		{
			plik.close();
			return true;
		}
	}

	if (highscoreAmount < 10)
		return true;

	plik.close();

	return false;
}

void GameManager::updateHighscores(const std::string& filePath, std::string name, int score)
{
	for (int i = 0; i < name.size(); i++)
		if (name[i] == ' ')
			name[i] = '_';

	std::ifstream plikOdczyt(filePath);

	std::vector<std::pair<std::string, int>> dane;

	std::string tmpString;
	int tmpInt;

	bool written = false;

	while (plikOdczyt >> tmpString >> tmpInt && dane.size() < 10)
	{
		if (score > tmpInt)
		{
			dane.push_back(std::make_pair(name, score));
			score = -1;
			written = true;
		}
		if (dane.size() < 10)
			dane.push_back(std::make_pair(tmpString, tmpInt));
	}

	if (!written)
		dane.push_back(std::make_pair(name, score));

	plikOdczyt.close();

	std::ofstream plikZapis(filePath);

	for (int i = 0; i < dane.size(); i++)
		plikZapis << dane[i].first << " " << dane[i].second << std::endl;

	plikOdczyt.close();
}

void GameManager::selectNextScreen(const int& score, std::string* name)
{
	if (newHighscore(score, SAVE_FILE_HIGHSCORE))
		inputNewHighscoreScreen(name);
	else
		gameOverScreen();
}

void GameManager::gameOverScreen()
{
	drawable.usun();
	drawable.add(new Button("Return to menu", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 600, 250, 60, 3, NULL, sf::Color::White));
	drawable.add(new Text("Game Over", holder::get().fonts.get("arial"), 64, sf::Color::Red, WIDTH / 2, 200, NULL, true));
}

void GameManager::inputNewHighscoreScreen(std::string* name)
{
	drawable.usun();
	drawable.add(new Text("Game Over", holder::get().fonts.get("arial"), 64, sf::Color::Red, WIDTH / 2, 200, NULL, true));
	drawable.add(new Text("New Highscore", holder::get().fonts.get("arial"), 64, sf::Color::White, WIDTH / 2, 300, NULL, true));
	drawable.add(new Text("Enter your name", holder::get().fonts.get("arial"), 64, sf::Color::White, WIDTH / 2, 400, NULL, true));
	drawable.add(new InputForm("", holder::get().fonts.get("arial"), 32, sf::Color::Red, WIDTH / 2, 500, 250, 60, name));
	drawable.add(new Button("Submit", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 600, 250, 60, 4, NULL, sf::Color::White));
}

void GameManager::highscoreScreen(const std::string& filePath)
{
	drawable.usun();

	std::ifstream plik(filePath);

	std::string nazwa;
	int wynik;

	int i = 1;
	int j = 1;

	while (plik >> nazwa >> wynik)
	{
		drawable.add(new Text(to_string(i + (j - 1) * 5) + ". " + nazwa + " : " + to_string(wynik) + " points", holder::get().fonts.get("arial"), 32, sf::Color::Red, WIDTH * j / 3, 50 + 120 * i, NULL, true));
		i++;

		if (i == 6)
		{
			i = 1;
			j++;
		}
	}

	drawable.add(new Button("Return to menu", holder::get().fonts.get("arial"), 32, sf::Color::Black, WIDTH / 2, 900, 250, 60, 3, NULL, sf::Color::White));
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
							createParticles(50, bulletObject->x, bulletObject->y, sf::Color::Red);
							drawable.erase(bulletObject);
							drawable.erase(enemyObject);

							addSound(holder::get().sounds.get("explosion"));

							return;
						}
					}
					else
					{
						Barrier* barrierObject = dynamic_cast<Barrier*>(tmp2->obj);
						if (barrierObject)
						{
							if (bulletObject->getBounds().intersects(barrierObject->getBounds()))
							{
								createParticles(50, bulletObject->x, bulletObject->y, sf::Color::Red);
								drawable.erase(bulletObject);
								drawable.erase(barrierObject);

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
									createParticles(50, bulletObject->x, bulletObject->y, sf::Color::Red);
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
										createParticles(50, bulletObject->x, bulletObject->y, sf::Color::Blue);
										drawable.erase(bulletObject);
										hp--;

										addSound(holder::get().sounds.get("hurt"));

										return;
									}
								}
							}
						}
					}
				}

				tmp2 = tmp2->next;
			}

			if (bulletObject)
			{
				if (bulletObject->y >= HEIGHT - bulletObject->sprite.getSprite().getTexture()->getSize().y || bulletObject->y <= 0)
				{
					createParticles(50, bulletObject->x, bulletObject->y, sf::Color::White);
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
				case 0: //Starting the game
				{
					score = 0;
					hp = 3;

					createGame(&score, &hp);

					state = GameState::Playing;
				} break;
				case 1: //Exiting the game
				{
					drawable.usun();
					ptrToWindow->window.close();
				} break;
				case 2:
				{
					drawable.usun();
					drawable = temporary;
					temporary.wyzeruj();
					state = GameState::Playing;
				} break;
				case 3:
				{
					drawable.usun();
					createMenu();
					score = 0;
					hp = 3;
					state = GameState::Menu;
				} break;
				case 4:
				{
					if (name.size() > 0)
					{
						updateHighscores("dane\\highscores.txt", name, score);
						drawable.usun();
						createMenu();
						score = 0;
						hp = 3;
						name = "";
						state = GameState::Menu;
					}
					else
						drawable.add(new Text("Type in at least one character", holder::get().fonts.get("arial"), 32, sf::Color::Red, WIDTH / 2, 700, NULL, true));
				} break;
				case 5:
				{
					drawable.usun();
					highscoreScreen(SAVE_FILE_HIGHSCORE);
					state = GameState::Highscore;
				} break;
				case 6:
				{
					drawable.usun();
					createSelectMenu();
				} break;
				case 7: //load
				{
					state = GameState::Playing;
					loadGame(SAVE_FILE_GAME);
				} break;
				case 8: //save
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
				selectNextScreen(score, &name);
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
		selectNextScreen(score, &name);
		state = GameState::GameOver;
	}
}

void GameManager::cleanUpObjects()
{
	List* tmp = drawable.get();
	while (tmp)
	{
		Particle* particleObject = dynamic_cast<Particle*>(tmp->obj);

		List* nast = tmp->next;

		if (particleObject)
			if (particleObject->zegar.getElapsedTime().asMicroseconds() >= particleObject->lifeDuration)
				drawable.erase(particleObject);

		tmp = nast;
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
		else if (type == "Barrier")
		{
			int x, y;
			plik >> x >> y;
			drawable.add(new Barrier(x, y, holder::get().textures.get("bariera")));
		}
	}
}