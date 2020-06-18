#ifndef GUI_H
#define GUI_H

#include <stdio.h>
#include <SFML/Graphics.h>
#include "struktury.h"
#include "sudoku.h"

#define WIDTH 453

#define HEIGHT 542

#define elementsToRemove 25

/** @file */

/** Funkcja wyœwietla na ekran podany napis
* @param win WskaŸnik na okno, na którym ma byæ napis narysowany
* @param color Jakiego koloru ma byæ napis
* @param font WskaŸnik na czcionkê
* @param x Pozycja x na oknie
* @param y Pozycja y na oknie
* @param charSize Rozmiar czcionki
* @param napis Napis do wyœwietlenia
* @param center Czy tekst ma zostaæ wyœrodkowany
* @return Funkcja nic nie zwraca
*/
void displayString(const sfRenderWindow* win, const sfColor color, const sfFont* font, const int x, const int y, const int charSize, const char* napis, const bool center);

/** Funckja zmienia wyœwietlany napis
* @param dst wskaŸnik na oryginalny napis, który ma zostaæ zedytowany
* @param src napis, który mamy zapisaæ do zmiennej src
* @param positions wskaŸnik na tablicê, która przechowuje pozycje ka¿dej z liter w napisie
* @return Funkcja nic nie zwraca
*/
void changeDisplayedText(char** dst, char* src, int** positions);

/** G³ówna funckja, obs³uguj¹ca zdarzenia i okno
* @param tab Informacje o tablicy sudoku
* @return Funkcja nic nie zwraca
*/
void handleWindow(struct tileInfo tab[sudokuSize][sudokuSize]);

#endif
