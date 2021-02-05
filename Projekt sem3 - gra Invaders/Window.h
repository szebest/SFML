#ifndef WINDOW
#define WINDOW

#include "GameManager.h"
#include "includes.h"
#include "Struktury.h"
#include "Enums.h"
#include <ctime>
#include <vector>

class Window
{
protected:
	sf::RenderWindow window;
	GameManager* manager;
	sf::Clock zegar;
	sf::Clock timeElapsed;
	float renderTime = 0.0f;
private:
	void update();

	void input();

	void draw();
public:
	void run();

	Window(bool _fullscreen=false);

	~Window();

	friend class GameManager;
};

#endif