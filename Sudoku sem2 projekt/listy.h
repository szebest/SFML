#ifndef LISTY_H
#define LISTY_H

#include <stdio.h>
#include "struktury.h"

/** @file */

/** Funkcja zapisuje w li�cie jednokierunkowej poprzednio wykonane ruchy
* @param head adres wska�nika na pocz�tek listy jednokierunkowej
* @param value liczba w polu sudoku, kt�r� chcemy zapisa� w historii
* @param x pozycja x na planszy sudoku
* @param y pozycja y na planszy sudoku
* @return Funkcja nic nie zwraca
*/
void tile_dodajDoListyJednokierunkowej(struct tile_history** head, int value, int x, int y);

/** Funkcja odczytuje pierwsz� warto�� z liczby jednokierunkowej i zapisuje j� w podane miejsce w tablicy sudoku
* @param head adres wska�nika na pocz�tek listy jednokierunkowej
* @param tab Informacje o tablicy sudoku
* @return Funkcja nic nie zwraca
*/
void tile_czytajPoczatekListyJednokierunkowej(struct tile_history** head, struct tileInfo tab[sudokuSize][sudokuSize]);

/** Funkcja usuwa list� jednokierunkow�
* @param head adres wska�nika na pocz�tek listy jednokierunkowej
* @return Funkcja nic nie zwraca
*/
void tile_usunListeJednokierunkowa(struct tile_history** head);

/** Funckja dodaje tekst ostatniej akcji wykonanej przez u�ytkownika na koniec listy jednokierunkowej
* @param head adres wska�nika na pocz�tek listy jednokierunkowej
* @param tekst napis, kt�ry dodajemy do listy jednokierunkowej
* @return Funkcja nic nie zwraca
*/
void action_dodajNaKoniecListyJednokierunkowej(struct action_history** head, char* tekst);

/** Funkcja zapisuje list� jednokierunkow� do pliku
* @param head wska�nik na pocz�tek listy jednokierunkowej
* @return Funkcja nic nie zwraca
*/
void action_zapiszListeJednokierunkowaDoPliku(struct action_history* head);

/** Funkcja usuwa list� jednokierunkow�
* @param head adres wska�nika na pocz�tek listy jednokierunkowej
* @return Funkcja nic nie zwraca
*/
void action_usunListeJednokierunkowa(struct action_history** head);

#endif
