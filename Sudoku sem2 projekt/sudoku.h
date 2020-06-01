#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdbool.h>
#include "struktury.h"

/** Funkcja wype³nia sudoku podan¹ liczb¹
* @param tab Informacje o tablicy sudoku
* @param number Liczba, któr¹ zostanie wype³niona tablica
* @return Funkcja nic nie zwraca
*/
void fillSudoku(struct tileInfo tab[sudokuSize][sudokuSize], int number);

/** Funkcja sprawdza poprawnoœæ tablicy sudoku
* @param tab Informacje o tablicy sudoku
* @return Zwraca, czy tablica sudoku jest poprawna
*/
bool isValid(struct tileInfo tab[sudokuSize][sudokuSize]);

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

#endif
