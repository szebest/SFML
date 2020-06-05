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
	int amount;
	bool decremented;
	bool inside;
};

/** Informacje o historii ostatnio wykonanych ruchów przez u¿ytkownika
* @param x pozycja x na planszy sudoku
* @param y pozycja y na planszy sudoku
* @param value przechowuje zapisan¹ liczbê z pola sudoku
* @param next wskaŸnik na kolejny element listy jednokierunkowej
*/
typedef struct tile_history
{
	int x;
	int y;
	int value;
	struct tile_history* next;
};

/** Informacje o historii ostatnio wykonanych akcji przez u¿ytkownika
* @param str napis, który przechowuje tekst wykonanej akcji przez u¿ytkownika
* @param next wskaŸnik na kolejny element listy jednokierunkowej
*/
typedef struct action_history
{
	char* str;
	struct action_history* next;
};

#endif