#ifndef GAMEMANAGER
#define GAMEMANAGER

#include "ObiektGraficzny.h"
#include "defines.h"
#include "Window.h"
#include "Enums.h"
#include "Lista.h"
#include <vector>

class Window;

class GameManager
{
	void createGame(int* score, int* hp, const int& x = WIDTH / 2, const int& y = HEIGHT * 0.9);

	void createMenu();

	void createPause();

	void createSelectMenu();

	void addSound(const sf::SoundBuffer& buffer);

	void saveGame(const std::string& filePath);

	void loadGame(const std::string& filePath);

	Window* ptrToWindow;

	Lista drawable;
	Lista temporary;

	std::vector<sf::Sound> sounds;

	int score;
	int hp;
	std::string name;
	GameState state;
public:
	GameManager(Window* ptr);

	~GameManager();

	Lista* getDrawable() { return &drawable; }

	Lista* getTemporary() { return &temporary; }

	void checkCollisions();

	void checkButtonInput();

	void checkEnemies();

	void checkSounds();

	void gameOverScreen();

	friend class Window;
};

#endif