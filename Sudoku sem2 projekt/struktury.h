#ifndef STRUKTURY_H
#define STRUKTURY_H

#include <stdbool.h>

#define sudokuSize 9

/** @file */

/** Informacje o jednym polu sudoku
* @param value Przechowywana wartoœæ w polu
* @param canBeModified Czy u¿ytkownik mo¿e edytowaæ dane pole, czy zosta³o ono wygenerowane podczas generowania tablicy Sudoku
*/
typedef struct tileInfo
{
	int value;
	bool canBeModified;
};

/** Informacje przesy³ane do w¹tku funkcji solveSudoku
* @param tab Tablica sudoku
* @param more Ile wiêcej rozwi¹zañ ma rozwi¹zaæ
* @param decremented Czy zmienna more zosta³a ju¿ zdekrementowana
* @param inside Czy aktualnie jesteœmy w w¹tku
*/
typedef struct threadInfo
{
	struct tileInfo(*tab)[sudokuSize];
	short int more;
	bool decremented;
	bool inside;
};

#endif