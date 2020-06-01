#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdbool.h>
#include "struktury.h"

/** Funkcja wype�nia sudoku podan� liczb�
* @param tab Informacje o tablicy sudoku
* @param number Liczba, kt�r� zostanie wype�niona tablica
* @return Funkcja nic nie zwraca
*/
void fillSudoku(struct tileInfo tab[sudokuSize][sudokuSize], int number);

/** Funkcja sprawdza poprawno�� tablicy sudoku
* @param tab Informacje o tablicy sudoku
* @return Zwraca, czy tablica sudoku jest poprawna
*/
bool isValid(struct tileInfo tab[sudokuSize][sudokuSize]);

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

#endif
