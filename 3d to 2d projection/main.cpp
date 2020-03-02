#include <SFML/Graphics.hpp>

const int width = 800;
const int height = 600;

int main()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "3d to 2d");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	window.clear();


	window.display();

	return 0;
}