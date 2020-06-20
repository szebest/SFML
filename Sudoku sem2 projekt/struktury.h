#ifndef STRUKTURY_H
#define STRUKTURY_H

#define sudokuSize 9

/** @file */

/** Zmienna typu bool */
typedef enum { false /**< Warto�� fa�szywa */, true /**< Warto�� prawdziwa */ } bool;

/** Informacje o jednym polu sudoku */
typedef struct tileInfo
{
	int value; /**< Przechowywana warto�� w polu */
	bool canBeModified; /**< Czy u�ytkownik mo�e edytowa� dane pole, czy zosta�o ono wygenerowane podczas generowania tablicy Sudoku */
};

/** Informacje przesy�ane do w�tku funkcji solveSudoku */
typedef struct threadInfo
{
	struct tileInfo(*tab)[sudokuSize]; /**< Tablica sudoku */
	short int more; /**< Ile wi�cej rozwi�za� ma rozwi�za� */
	int amount; /**< Przechowywana warto�� w polu */
	bool decremented; /**< Czy zmienna more zosta�a ju� zdekrementowana */
	bool inside; /**< Czy aktualnie jeste�my w w�tku */
};

/** Informacje o historii ostatnio wykonanych ruch�w przez u�ytkownika */
typedef struct tile_history
{
	int x; /**< pozycja x na planszy sudoku */
	int y; /**< pozycja y na planszy sudoku */
	int value; /**< przechowuje zapisan� liczb� z pola sudokuu */
	struct tile_history* next; /**< wska�nik na kolejny element listy jednokierunkowej */
};

/** Informacje o historii ostatnio wykonanych akcji przez u�ytkownika */
typedef struct action_history
{
	char* str; /**< napis, kt�ry przechowuje tekst wykonanej akcji przez u�ytkownika */
	struct action_history* next; /**< wska�nik na kolejny element listy jednokierunkowej */
};

#endif