#ifndef STRUKTURY_H
#define STRUKTURY_H

#include <stdbool.h>

#define sudokuSize 9

/** @file */

/** Informacje o jednym polu sudoku
* @param value Przechowywana warto�� w polu
* @param canBeModified Czy u�ytkownik mo�e edytowa� dane pole, czy zosta�o ono wygenerowane podczas generowania tablicy Sudoku
*/
typedef struct tileInfo
{
	int value;
	bool canBeModified;
};

/** Informacje przesy�ane do w�tku funkcji solveSudoku
* @param tab Tablica sudoku
* @param more Ile wi�cej rozwi�za� ma rozwi�za�
* @param decremented Czy zmienna more zosta�a ju� zdekrementowana
* @param inside Czy aktualnie jeste�my w w�tku
*/
typedef struct threadInfo
{
	struct tileInfo(*tab)[sudokuSize];
	short int more;
	int amount;
	bool decremented;
	bool inside;
};

typedef struct tile_history
{
	int x;
	int y;
	int value;
	struct tile_history* next;
};

typedef struct action_history
{
	char* str;
	struct action_history* next;
};

#endif