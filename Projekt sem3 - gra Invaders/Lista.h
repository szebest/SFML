#ifndef LISTA
#define LISTA

#include "Struktury.h"
#include "ObiektGraficzny.h"

class Lista
{
	List* ptr = NULL;
public:
	Lista();

	~Lista();

	List* operator[](std::size_t index);

	List* get() const;

	void add(ObiektGraficzny* object);

	void erase(const ObiektGraficzny* object);

	void usun();

	void wyzeruj();
};

#endif
