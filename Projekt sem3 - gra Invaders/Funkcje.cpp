#include "Funkcje.h"

std::string to_string(int number)
{
	std::stringstream ss;
	ss << number;
	return ss.str();
}