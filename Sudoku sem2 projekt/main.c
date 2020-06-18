#pragma warning(disable:4996)
#include <time.h>
#include <stdio.h>

#include "struktury.h"
#include "sudoku.h"
#include "io.h"
#include "gui.h"
#include "listy.h"

int main()
{
	//Inicjujemy losowe liczby
	srand(time(NULL));

	//Tablica informacji o polach sudoku
	struct tileInfo tab[sudokuSize][sudokuSize];

	//Wypełniamy ją zerami
	fillSudoku(tab, 0);
	
	//Generujemy prawidłową tablicę sudoku
	bool redo = true;
	generateSudoku(tab, &redo);

	//Usuwamy z niej x elementów
	removeElements(tab, elementsToRemove);

	//Wchodzimy w główną funcję, która obsługuje okno
	handleWindow(tab);
	return 0;
}