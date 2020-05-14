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

/** Funkcja wype³nia sudoku podan¹ liczb¹
* @param tab Informacje o tablicy sudoku
* @param number Liczba, któr¹ zostanie wype³niona tablica
* @return Funkcja nic nie zwraca
*/
void fillSudoku(struct tileInfo tab[sudokuSize][sudokuSize], int number);

/** Funkcja zapisuje aktualn¹ planszê sudoku do pliku binarnego
* @param tab Informacje o tablicy sudoku
* @return Zwraca, czy uda³o siê zapisaæ do pliku
*/
bool save(const struct tileInfo tab[sudokuSize][sudokuSize]);

/** Funkcja sprawdza poprawnoœæ tablicy sudoku
* @param tab Informacje o tablicy sudoku
* @return Zwraca, czy tablica sudoku jest poprawna
*/
bool isValid(struct tileInfo tab[sudokuSize][sudokuSize]);

/** Funkcja wczytuje planszê sudoku z pliku binarnego
* @param tab Informacje o tablicy sudoku
* @return Zwraca, czy uda³o siê wczytaæ tablicê z pliku
*/
bool load(struct tileInfo tab[sudokuSize][sudokuSize]);

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

/** Funkcja sprawdza, czy mo¿liwe jest umieszczenie danej liczby w danej kolumnie
* @param tab Informacje o tablicy sudoku
* @param i Index kolumny
* @param number Liczba do sprawdzenia
* @return Zwraca, czy mo¿na wstawiæ podan¹ liczbê do danej kolumny
*/
bool checkColumn(struct tileInfo tab[sudokuSize][sudokuSize], int i, int number);

/** Funkcja sprawdza, czy mo¿liwe jest umieszczenie danej liczby w danym wierszu
* @param tab Informacje o tablicy sudoku
* @param i Index wiersza
* @param number Liczba do sprawdzenia
* @return Zwraca, czy mo¿na wstawiæ podan¹ liczbê do danego wierszu
*/
bool checkRow(struct tileInfo tab[sudokuSize][sudokuSize], int i, int number);

/** Funkcja sprawdza, czy mo¿liwe jest umieszczenie danej liczby w danym kwadracie 3x3
* @param tab Informacje o tablicy sudoku
* @param x Index x kwadratu
* @param y Index y kwadratu
* @param number Liczba do sprawdzenia
* @return Zwraca, czy mo¿na wstawiæ podan¹ liczbê do danego kwadratu 3x3
*/
bool checkSquare(struct tileInfo tab[sudokuSize][sudokuSize], int x, int y, int number);

/** Funkcja usuwa 'elements' elementów z tablicy sudoku
* @param tab Informacje o tablicy sudoku
* @param elements Ile elementów do usuniêcia
* @return Funkcja nic nie zwraca
*/
void removeElements(struct tileInfo tab[sudokuSize][sudokuSize], int elements);

/** Rekurencyjna funkcja tworzy poprawn¹, w pe³ni wype³nion¹ tablicê sudoku
* @param tab Informacje o tablicy sudoku
* @param redo WskaŸnik na zmienn¹ logiczn¹, która mówi, czy po znalezieniu jednej rozwi¹zanej tablicy mamy szukaæ dalej w poszukiwaniu kolejnych (true = pierwsza tablica wygenerowana koñczy funkcjê)
* @return Funkcja nic nie zwraca
*/
void generateSudoku(struct tileInfo tab[sudokuSize][sudokuSize], bool* redo);

/** Rekurencyjna funkcja, wywo³ywana na osobnym w¹tku, która pokazuje mo¿liwe rozwi¹zania tablicy sudoku. Przy ka¿dym klikniêciu klawisza 'S' pokazuje, kolejne rozwi¹anie (o ile istnieje takie)
* @param tInfo WskaŸnik na informacje przesy³ane do w¹tku
* @return Funkcja nic nie zwraca
*/
void solveSudoku(struct threadInfo* tInfo);

/** Funckja sprawdza, czy u¿ytkownik wygra³
* @param tab Informacje o tablicy sudoku
* @return Zwraca, czy tablica jest w pe³ni rozwi¹zana
*/
bool hasWon(struct tileInfo tab[sudokuSize][sudokuSize]);

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

void dodajDoListyJednokierunkowej(struct history** head, int value, int x, int y);

void czytajPoczatekListyJednokierunkowej(struct history** head, struct tileInfo tab[sudokuSize][sudokuSize]);

void usunListeJednokierunkowa(struct history** head);

#endif