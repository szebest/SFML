#ifndef HOLDER
#define HOLDER

#include "Manager.h"
#include "includes.h"

class holder
{
public:
	static holder& get();

	manager<sf::Font> fonts;
	manager<sf::Texture> textures;
	manager<sf::SoundBuffer> sounds;

private:
	holder();
};

#endif
