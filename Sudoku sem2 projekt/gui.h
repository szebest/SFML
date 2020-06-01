#ifndef GUI_H
#define GUI_H

#include <stdio.h>
#include <SFML/Graphics.h>
#include <stdbool.h>
#include "struktury.h"
#include "sudoku.h"

#define WIDTH 453

#define HEIGHT 542

#define elementsToRemove 25

/** Funkcja wy�wietla na ekran podany napis
* @param win Wska�nik na okno, na kt�rym ma by� napis narysowany
* @param color Jakiego koloru ma by� napis
* @param font Wska�nik na czcionk�
* @param x Pozycja x na oknie
* @param y Pozycja y na oknie
* @param charSize Rozmiar czcionki
* @param napis Napis do wy�wietlenia
* @param center Czy tekst ma zosta� wy�rodkowany
* @return Funkcja nic nie zwraca
*/
void displayString(const sfRenderWindow* win, const sfColor color, const sfFont* font, const int x, const int y, const int charSize, const char* napis, const bool center);

/** Funckja zmienia wy�wietlany napis
* @param dst wska�nik na oryginalny napis, kt�ry ma zosta� zedytowany
* @param src napis, kt�ry mamy zapisa� do zmiennej src
* @param positions wska�nik na tablic�, kt�ra przechowuje pozycje ka�dej z liter w napisie
* @return Funkcja nic nie zwraca
*/
void changeDisplayedText(char** dst, char* src, int** positions);

/** G��wna funckja, obs�uguj�ca zdarzenia i okno
* @param tab Informacje o tablicy sudoku
* @return Funkcja nic nie zwraca
*/
void handleWindow(struct tileInfo tab[sudokuSize][sudokuSize]);

#endif
