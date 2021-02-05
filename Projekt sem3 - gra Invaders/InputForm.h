#ifndef INPUTFORM
#define INPUTFORM

#include "Text.h"
#include <string>

class InputForm : public Text
{
	std::string* ptrToString;
	sf::RectangleShape pole;
	bool active = false;
public:
	std::string getString() { return str; }

	InputForm(const std::string& str, const sf::Font& font, const int& cSize, const sf::Color& kolor, const int& x, const int& y, const int& width, const int& height, std::string* ptr=NULL);

	void update() override;

	void draw(sf::RenderWindow& window) override;

	void process(sf::Event event) override;

	InputForm& operator+=(const char& add);

	InputForm& operator-=(const int& amount);
};

#endif 