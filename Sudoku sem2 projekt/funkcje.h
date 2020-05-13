#ifndef FUNKCJE_H
#define FUNKCJE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SFML/Graphics.h>

#include "struktury.h"

#define elementsToRemove 25

#define sudokuSize 9

#define WIDTH 453

#define HEIGHT 542

/** @file */

/** Funkcja wype�nia sudoku podan� liczb�
* @param tab Informacje o tablicy sudoku
* @param number Liczba, kt�r� zostanie wype�niona tablica
* @return Funkcja nic nie zwraca
*/
void fillSudoku(struct tileInfo tab[sudokuSize][sudokuSize], int number);

/** Funkcja zapisuje aktualn� plansz� sudoku do pliku binarnego
* @param tab Informacje o tablicy sudoku
* @return Zwraca, czy uda�o si� zapisa� do pliku
*/
bool save(const struct tileInfo tab[sudokuSize][sudokuSize]);

/** Funkcja sprawdza poprawno�� tablicy sudoku
* @param tab Informacje o tablicy sudoku
* @return Zwraca, czy tablica sudoku jest poprawna
*/
bool isValid(struct tileInfo tab[sudokuSize][sudokuSize]);

/** Funkcja wczytuje plansz� sudoku z pliku binarnego
* @param tab Informacje o tablicy sudoku
* @return Zwraca, czy uda�o si� wczyta� tablic� z pliku
*/
bool load(struct tileInfo tab[sudokuSize][sudokuSize]);

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

/** Funkcja sprawdza, czy mo�liwe jest umieszczenie danej liczby w danej kolumnie
* @param tab Informacje o tablicy sudoku
* @param i Index kolumny
* @param number Liczba do sprawdzenia
* @return Zwraca, czy mo�na wstawi� podan� liczb� do danej kolumny
*/
bool checkColumn(struct tileInfo tab[sudokuSize][sudokuSize], int i, int number);

/** Funkcja sprawdza, czy mo�liwe jest umieszczenie danej liczby w danym wierszu
* @param tab Informacje o tablicy sudoku
* @param i Index wiersza
* @param number Liczba do sprawdzenia
* @return Zwraca, czy mo�na wstawi� podan� liczb� do danego wierszu
*/
bool checkRow(struct tileInfo tab[sudokuSize][sudokuSize], int i, int number);

/** Funkcja sprawdza, czy mo�liwe jest umieszczenie danej liczby w danym kwadracie 3x3
* @param tab Informacje o tablicy sudoku
* @param x Index x kwadratu
* @param y Index y kwadratu
* @param number Liczba do sprawdzenia
* @return Zwraca, czy mo�na wstawi� podan� liczb� do danego kwadratu 3x3
*/
bool checkSquare(struct tileInfo tab[sudokuSize][sudokuSize], int x, int y, int number);

/** Funkcja usuwa 'elements' element�w z tablicy sudoku
* @param tab Informacje o tablicy sudoku
* @param elements Ile element�w do usuni�cia
* @return Funkcja nic nie zwraca
*/
void removeElements(struct tileInfo tab[sudokuSize][sudokuSize], int elements);

/** Rekurencyjna funkcja tworzy poprawn�, w pe�ni wype�nion� tablic� sudoku
* @param tab Informacje o tablicy sudoku
* @param redo Wska�nik na zmienn� logiczn�, kt�ra m�wi, czy po znalezieniu jednej rozwi�zanej tablicy mamy szuka� dalej w poszukiwaniu kolejnych (true = pierwsza tablica wygenerowana ko�czy funkcj�)
* @return Funkcja nic nie zwraca
*/
void generateSudoku(struct tileInfo tab[sudokuSize][sudokuSize], bool* redo);

/** Rekurencyjna funkcja, wywo�ywana na osobnym w�tku, kt�ra pokazuje mo�liwe rozwi�zania tablicy sudoku. Przy ka�dym klikni�ciu klawisza 'S' pokazuje, kolejne rozwi�anie (o ile istnieje takie)
* @param tInfo Wska�nik na informacje przesy�ane do w�tku
* @return Funkcja nic nie zwraca
*/
void solveSudoku(struct threadInfo* tInfo);

/** Funckja sprawdza, czy u�ytkownik wygra�
* @param tab Informacje o tablicy sudoku
* @return Zwraca, czy tablica jest w pe�ni rozwi�zana
*/
bool hasWon(struct tileInfo tab[sudokuSize][sudokuSize]);

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