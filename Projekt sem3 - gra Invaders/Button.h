#ifndef BUTTON
#define BUTTON

#include "Text.h"
#include "includes.h"
#include "enums.h"

class Button : public Text
{
	ButtonType buttonType = ButtonType::None;
	bool wasPressed = false;
	bool wasReleased = true;
	sf::RectangleShape przycisk;
public:
	bool getWasPressed() { return wasPressed; }

	ButtonType getButtonType() { return buttonType; }

	Button(const std::string& displayedText, const sf::Font& textFont, const int& charSize, const sf::Color& kolor_tekstu, const int& _x, const int& _y, const int& _width, const int& _height, ButtonType _buttonType, int* ptr, const sf::Color& kolor_przycisku);

	void draw(sf::RenderWindow& window) override;

	void update() override;

	void process(sf::Event event) override;
};

#endif 