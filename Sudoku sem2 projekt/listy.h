#ifndef LISTY_H
#define LISTY_H

#include <stdio.h>
#include "struktury.h"

void tile_dodajDoListyJednokierunkowej(struct tile_history** head, int value, int x, int y);

void tile_czytajPoczatekListyJednokierunkowej(struct tile_history** head, struct tileInfo tab[sudokuSize][sudokuSize]);

void tile_usunListeJednokierunkowa(struct tile_history** head);

void action_dodajNaKoniecListyJednokierunkowej(struct action_history** head, char* tekst);

void action_zapiszListeJednokierunkowaDoPliku(struct action_history* head);

void action_usunListeJednokierunkowa(struct action_history** head);

#endif
