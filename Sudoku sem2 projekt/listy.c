#pragma warning(disable:4996)
#include "listy.h"

void tile_dodajDoListyJednokierunkowej(struct tile_history** head, int value, int x, int y)
{
	if (*head == NULL)
	{
		*head = (struct history*)malloc(sizeof(struct tile_history));
		(*head)->next = NULL;
		(*head)->value = value;
		(*head)->x = x;
		(*head)->y = y;
	}
	else {
		struct tile_history* tmp = (struct history*)malloc(sizeof(struct tile_history));
		tmp->next = *head;
		tmp->value = value;
		tmp->x = x;
		tmp->y = y;
		*head = tmp;
	}
}

void tile_czytajPoczatekListyJednokierunkowej(struct tile_history** head, struct tileInfo tab[sudokuSize][sudokuSize])
{
	if (*head)
	{
		tab[(*head)->y][(*head)->x].value = (*head)->value;

		struct tile_history* tmp = (*head)->next;
		free(*head);
		*head = tmp;
	}
}

void tile_usunListeJednokierunkowa(struct tile_history** head)
{
	while (*head)
	{
		struct tile_history* tmp = (*head)->next;
		free(*head);
		*head = tmp;
	}
}

void action_dodajNaKoniecListyJednokierunkowej(struct action_history** head, char* tekst)
{
	if (*head == NULL)
	{
		*head = (struct action_history*)malloc(sizeof(struct action_history));
		(*head)->str = (char*)malloc(strlen(tekst) + 1);
		strcpy((*head)->str, tekst);
		(*head)->next = NULL;

		return;
	}

	struct action_history* tmp = *head;

	while (tmp->next)
		tmp = tmp->next;

	tmp->next = (struct action_history*)malloc(sizeof(struct action_history));
	tmp->next->str = (char*)malloc(strlen(tekst) + 1);
	strcpy(tmp->next->str, tekst);
	tmp->next->next = NULL;
}

void action_zapiszListeJednokierunkowaDoPliku(struct action_history* head)
{
	FILE* plik = fopen("historia_akcji.txt", "w");

	if (plik)
	{
		int index = 1;
		while (head)
		{
			fprintf(plik, "%d. %s\n", index, head->str);
			index++;
			head = head->next;
		}

		fclose(plik);
	}
}

void action_usunListeJednokierunkowa(struct action_history** head)
{
	while (*head)
	{
		struct action_history* tmp = (*head)->next;
		free((*head)->str);
		free(*head);
		*head = tmp;
	}
}