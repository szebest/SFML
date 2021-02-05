#ifndef ENTITY
#define ENTITY

#include "Lista.h"
#include "includes.h"
#include "withSprite.h"
#include <vector>

class Entity : public withSprite
{
protected:
	float dirx;
	Lista* wskNaObiekty = NULL;
public:
	Entity(float _dirx, Lista* wskNaObiekty, const int& x, const int& y);
};

#endif 