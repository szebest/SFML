#ifndef STRUKTURY_H
#define STRUKTURY_H

#define sudokuSize 9

typedef enum { false, true } bool;

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

/** Informacje o historii ostatnio wykonanych ruch�w przez u�ytkownika
* @param x pozycja x na planszy sudoku
* @param y pozycja y na planszy sudoku
* @param value przechowuje zapisan� liczb� z pola sudoku
* @param next wska�nik na kolejny element listy jednokierunkowej
*/
typedef struct tile_history
{
	int x;
	int y;
	int value;
	struct tile_history* next;
};

/** Informacje o historii ostatnio wykonanych akcji przez u�ytkownika
* @param str napis, kt�ry przechowuje tekst wykonanej akcji przez u�ytkownika
* @param next wska�nik na kolejny element listy jednokierunkowej
*/
typedef struct action_history
{
	char* str;
	struct action_history* next;
};

#endif