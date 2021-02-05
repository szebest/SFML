#include "Button.h"

#include <iostream>

Button::Button(const std::string& displayedText, const sf::Font& textFont, const int& charSize, const sf::Color& kolor_tekstu, const int& _x, const int& _y, const int& _width, const int& _height, const int& _buttonType, int* ptr, const sf::Color& kolor_przycisku) : Text(displayedText, textFont, charSize, kolor_tekstu, _x, _y, ptr, true), buttonType(_buttonType)
{
	przycisk.setSize(sf::Vector2f(_width, _height));
	przycisk.setFillColor(kolor_przycisku);
	przycisk.setPosition(sf::Vector2f(_x - _width / 2, _y - _height / 2));
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(przycisk);
	Text::draw(window);
}

void Button::process(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed && wasReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (przycisk.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
			{
				wasPressed = true;
				wasReleased = false;
			}
		}
	}

	if (event.type == sf::Event::MouseButtonReleased)
		wasReleased = true;
}

void Button::update()
{
	if (!wasReleased)
		wasPressed = false;
}