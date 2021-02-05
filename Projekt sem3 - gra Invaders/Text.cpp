#pragma warning(disable:4996)
#include "Text.h"
#include "Funkcje.h"

#include <iostream>

Text::Text(const std::string& str, const sf::Font& font, const int& cSize, const sf::Color& kolor, const int& x, const int& y, int* ptr, bool center) : ptrToNumber(ptr), str(str), ObiektGraficzny(x, y)
{
	napis.setString(str);
	napis.setCharacterSize(cSize);
	napis.setColor(kolor);
	napis.setFont(font);

	if (center)
		napis.setPosition(x - napis.getGlobalBounds().width / 2, y - napis.getGlobalBounds().height / 2 - cSize * 2 / 5);
	else
		napis.setPosition(x, y);

	napis.setString(ptrToNumber != NULL ? str + to_string(*ptrToNumber) : str);
}

Text& Text::operator+=(const Text& other)
{
	this->str += other.str;
	this->update();
	return *this;
}

void Text::update()
{
	napis.setString(ptrToNumber != NULL ? str + to_string(*ptrToNumber) : str);
}

void Text::draw(sf::RenderWindow& window)
{
	window.draw(napis);
}

void Text::move(float x_offset, float y_offset)
{
	x += x_offset;
	y += y_offset;

	napis.move(x_offset, y_offset);
}

void Text::process(sf::Event event)
{

}