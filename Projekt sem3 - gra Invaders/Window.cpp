#include "Window.h"
#include "defines.h"
#include "holder.h"
#include "Text.h"
#include <vector>

#include <iostream>

Window::Window(bool _fullscreen)
{
	srand(time(NULL));

	if (_fullscreen)
		window.create(sf::VideoMode(WIDTH, HEIGHT), "Space Invaders", sf::Style::Fullscreen);
	else
		window.create(sf::VideoMode(WIDTH, HEIGHT), "Space Invaders");

	manager = new GameManager(this);
}

Window::~Window()
{
	delete manager;
}

void Window::draw()
{
	window.clear(sf::Color::Black);

	List* drawable = manager->getDrawable()->get();

	while (drawable)
	{
		drawable->obj->draw(window);

		drawable = drawable->next;
	}

	window.display();
}

void Window::update()
{
	manager->cleanUpObjects();

	manager->checkCollisions();

	manager->checkEnemies();

	manager->checkSounds();

	List* drawable = manager->getDrawable()->get();

	while (drawable)
	{
		drawable->obj->update();

		drawable = drawable->next;
	}
}

void Window::input()
{
	sf::Event event;

	Lista* drawable = manager->getDrawable();

	Lista* temporary = manager->getTemporary();

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape && manager->state == GameState::Playing)
			{
				*temporary = *drawable;
				drawable->wyzeruj();
				manager->createPause();

				manager->state = GameState::Pause;
			}
		}
		if (event.type == sf::Event::TextEntered || event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased || event.type == sf::Event::KeyReleased)
		{
			List* tmp = drawable->get();
			while (tmp)
			{
				tmp->obj->process(event);

				tmp = tmp->next;
			}
		}

		if (event.type == sf::Event::Closed)
			window.close();
	}

	manager->checkButtonInput();
}

void Window::run()
{
	while (window.isOpen())
	{
		if (zegar.getElapsedTime().asMicroseconds() >= UPDATE - renderTime)
		{
			timeElapsed.restart();

			input();

			update();

			draw();

			zegar.restart();

			renderTime = timeElapsed.getElapsedTime().asMicroseconds();
		}
	}
}

