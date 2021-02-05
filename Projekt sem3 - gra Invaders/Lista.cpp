#include "Lista.h"
#include <iostream> 

Lista::Lista()
{

}

Lista::~Lista()
{
	usun();
}

List* Lista::get() const
{
	return ptr;
}

List* Lista::operator[](std::size_t index)
{
	std::size_t i = 0;

	List* tmp = ptr;

	while (ptr && i != index)
	{
		tmp = tmp->next;

		i++;
	}

	if (!tmp)
		std::cout << "Out of bounds \n";

	return tmp;
}

void Lista::add(ObiektGraficzny* object)
{
	if (!ptr)
	{
		ptr = new List{ object, NULL };
		return;
	}

	List* tmp = ptr;

	while (tmp->next)
		tmp = tmp->next;

	tmp->next = new List{ object, NULL };
}

void Lista::erase(const ObiektGraficzny* object)
{
	if (!ptr)
		return;

	if (ptr->obj == object)
	{
		List* tmp = ptr->next;
		delete ptr->obj;
		delete ptr;
		ptr = tmp;
	}
	else
	{
		List* tmp = ptr;
		while (tmp->next != NULL && tmp->next->obj != object)
			tmp = tmp->next;

		if (tmp->next != NULL)
		{
			List* tmp2 = tmp->next->next;
			delete tmp->next->obj;
			delete tmp->next;
			tmp->next = tmp2;
		}
	}
}

void Lista::usun()
{
	while (ptr)
	{
		List* nast = ptr->next;
		delete ptr->obj;
		delete ptr;

		ptr = nast;
	}

	ptr = NULL;
}

void Lista::wyzeruj()
{
	ptr = NULL;
}