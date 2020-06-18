#ifndef IO_H
#define IO_H

#include <stdio.h>
#include "struktury.h"

/** @file */

/** Funkcja wczytuje plansz� sudoku z pliku binarnego
* @param tab Informacje o tablicy sudoku
* @return Zwraca, czy uda�o si� wczyta� tablic� z pliku
*/
bool load(struct tileInfo tab[sudokuSize][sudokuSize]);

/** Funkcja zapisuje aktualn� plansz� sudoku do pliku binarnego
* @param tab Informacje o tablicy sudoku
* @return Zwraca, czy uda�o si� zapisa� do pliku
*/
bool save(const struct tileInfo tab[sudokuSize][sudokuSize]);

#endif