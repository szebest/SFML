#ifndef TEXT
#define TEXT

#include "includes.h"
#include "ObiektGraficzny.h"

//TODO: pozbyc sie virtualnego dziecziczenia
class Text : public ObiektGraficzny
{
protected:
	sf::Text napis;
	std::string str;
	int* ptrToNumber = NULL;
public:
	Text(const std::string& str, const sf::Font& font, const int& cSize, const sf::Color& kolor, const int& x, const int& y, int* ptr, bool center);

	Text& operator+=(const Text& other);

	void update() override;

	void draw(sf::RenderWindow& window) override;

	virtual void save(std::ostream& os) override
	{

	}

	void move(float x_offset, float y_offset);

	void process(sf::Event event) override;
};

#endif 