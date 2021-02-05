#include "InputForm.h"
#include <iostream>

InputForm::InputForm(const std::string& str, const sf::Font& font, const int& cSize, const sf::Color& kolor, const int& x, const int& y, const int& width, const int& height, std::string* ptr) : Text(str, font, cSize, kolor, x - width / 2 + 5, y - height / 2, NULL, false), ptrToString(ptr), active(false)
{
	pole.setFillColor(sf::Color(50, 50, 50));
	pole.setPosition(sf::Vector2f(x - width / 2, y - height / 2));
	pole.setSize(sf::Vector2f(width, height));
	pole.setOutlineThickness(10);
	pole.setOutlineColor(sf::Color(25, 25, 25));
	*ptr = str;
}

void InputForm::process(sf::Event event)
{
	if (event.type == sf::Event::TextEntered && active)
	{
		if (event.text.unicode < 128 && event.text.unicode >= 32)
		{
			*this += (char)event.text.unicode;

			if (napis.getGlobalBounds().width >= pole.getGlobalBounds().width - 5)
				*this -= 1;
		}
		else if (event.text.unicode == 8) //Backspace
			*this -= 1;
		}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		if (pole.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
		{
			active = true;
			pole.setFillColor(sf::Color(100, 100, 100));
		}
		else
		{
			active = false;
			pole.setFillColor(sf::Color(50, 50, 50));
		}
	}
}

void InputForm::draw(sf::RenderWindow& window)
{
	window.draw(pole);
	Text::draw(window);
}

void InputForm::update()
{

}

InputForm& InputForm::operator+=(const char& add)
{
	napis.setString(str = *ptrToString += add);
	return *this;
}

InputForm& InputForm::operator-=(const int& amount)
{
	napis.setString(str = *ptrToString = (*ptrToString).substr(0, std::max((int)(*ptrToString).size() - abs(amount), 0)));
	return *this;
}