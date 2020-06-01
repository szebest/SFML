#ifndef IO_H
#define IO_H

#include <stdbool.h>
#include <stdio.h>
#include "struktury.h"

/** @file */

/** Funkcja wczytuje planszê sudoku z pliku binarnego
* @param tab Informacje o tablicy sudoku
* @return Zwraca, czy uda³o siê wczytaæ tablicê z pliku
*/
bool load(struct tileInfo tab[sudokuSize][sudokuSize]);

/** Funkcja zapisuje aktualn¹ planszê sudoku do pliku binarnego
* @param tab Informacje o tablicy sudoku
* @return Zwraca, czy uda³o siê zapisaæ do pliku
*/
bool save(const struct tileInfo tab[sudokuSize][sudokuSize]);

#endif