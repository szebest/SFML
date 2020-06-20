#ifndef STRUKTURY_H
#define STRUKTURY_H

#define sudokuSize 9

/** @file */

/** Zmienna typu bool */
typedef enum { false /**< Wartoœæ fa³szywa */, true /**< Wartoœæ prawdziwa */ } bool;

/** Informacje o jednym polu sudoku */
typedef struct tileInfo
{
	int value; /**< Przechowywana wartoœæ w polu */
	bool canBeModified; /**< Czy u¿ytkownik mo¿e edytowaæ dane pole, czy zosta³o ono wygenerowane podczas generowania tablicy Sudoku */
};

/** Informacje przesy³ane do w¹tku funkcji solveSudoku */
typedef struct threadInfo
{
	struct tileInfo(*tab)[sudokuSize]; /**< Tablica sudoku */
	short int more; /**< Ile wiêcej rozwi¹zañ ma rozwi¹zaæ */
	int amount; /**< Przechowywana wartoœæ w polu */
	bool decremented; /**< Czy zmienna more zosta³a ju¿ zdekrementowana */
	bool inside; /**< Czy aktualnie jesteœmy w w¹tku */
};

/** Informacje o historii ostatnio wykonanych ruchów przez u¿ytkownika */
typedef struct tile_history
{
	int x; /**< pozycja x na planszy sudoku */
	int y; /**< pozycja y na planszy sudoku */
	int value; /**< przechowuje zapisan¹ liczbê z pola sudokuu */
	struct tile_history* next; /**< wskaŸnik na kolejny element listy jednokierunkowej */
};

/** Informacje o historii ostatnio wykonanych akcji przez u¿ytkownika */
typedef struct action_history
{
	char* str; /**< napis, który przechowuje tekst wykonanej akcji przez u¿ytkownika */
	struct action_history* next; /**< wskaŸnik na kolejny element listy jednokierunkowej */
};

#endif