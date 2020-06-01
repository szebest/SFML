#include "sudoku.h"

void fillSudoku(struct tileInfo tab[sudokuSize][sudokuSize], int number)
{
	for (int i = 0; i < sudokuSize; i++)
	{
		for (int j = 0; j < sudokuSize; j++)
		{
			tab[i][j].value = number;
		}
	}
}

bool isValid(struct tileInfo tab[sudokuSize][sudokuSize])
{
	//Sprawdza czy liczby sa w odpowiednim przedziale
	for (int i = 0; i < sudokuSize; i++)
		for (int j = 0; j < sudokuSize; j++)
			if (tab[i][j].value > 9 || tab[i][j].value < 0)
				return false;

	//Sprawdza kolumny i wiersze
	for (int i = 0; i < sudokuSize; i++)
		for (int j = 0; j < sudokuSize; j++)
			for (int k = 0; k < sudokuSize; k++)
				if (j != k && ((tab[i][j].value == tab[i][k].value && tab[i][j].value != 0) || (tab[j][i].value != 0 && tab[j][i].value == tab[k][i].value != 0)))
					return false;

	//Sprawdza kwadraty
	for (int i = 0; i < sudokuSize / 3; i++)
		for (int j = 0; j < sudokuSize / 3; j++)
			for (int k = 0; k < sudokuSize / 3; k++)
				for (int m = 0; m < sudokuSize / 3; m++)
					for (int n = 0; n < sudokuSize / 3; n++)
						for (int o = 0; o < sudokuSize / 3; o++)
							if (k != n && m != o && tab[i * 3 + k][j * 3 + m].value == tab[i * 3 + n][j * 3 + o].value && tab[i * 3 + k][j * 3 + m].value != 0)
								return false;

	return true;
}

bool checkColumn(struct tileInfo tab[sudokuSize][sudokuSize], int i, int number)
{
	for (int j = 0; j < sudokuSize; j++)
	{
		if (tab[j][i].value == number)
			return false;
	}

	return true;
}

bool checkRow(struct tileInfo tab[sudokuSize][sudokuSize], int i, int number)
{
	for (int j = 0; j < sudokuSize; j++)
	{
		if (tab[i][j].value == number)
			return false;
	}

	return true;
}

bool checkSquare(struct tileInfo tab[sudokuSize][sudokuSize], int x, int y, int number)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (tab[y * 3 + i][x * 3 + j].value == number)
				return false;
		}
	}

	return true;
}

void removeElements(struct tileInfo tab[sudokuSize][sudokuSize], int elements)
{
	if (elements > sudokuSize* sudokuSize)
		elements = sudokuSize * sudokuSize;

	int losx, losy;
	while (elements > 0)
	{
		do
		{
			losx = rand() % sudokuSize;
			losy = rand() % sudokuSize;
		} while (tab[losy][losx].value == 0);

		tab[losy][losx].value = 0;
		tab[losy][losx].canBeModified = true;

		elements--;
	}
}

void generateSudoku(struct tileInfo tab[sudokuSize][sudokuSize], bool* redo)
{
	for (int y = 0; y < sudokuSize; y++)
	{
		for (int x = 0; x < sudokuSize; x++)
		{
			if (!(*redo))
				return;

			if (tab[y][x].value == 0)
			{
				//Liczby losowane s¹ w ten sposób, aby zapewniæ losowoœæ, podczas generowania sudoku. W przeciwnym razie rozwi¹zana tablica Sudoku wygl¹da³aby zawsze identycznie
				bool hashtable[10] = { false };
				int liczba = 0;
				while (liczba <= 9)
				{
					int n = rand() % 9 + 1;

					if (!hashtable[n - 1])
					{
						liczba++;
						hashtable[n] = true;

						if (checkRow(tab, y, n) && checkColumn(tab, x, n) && checkSquare(tab, x / 3, y / 3, n))
						{

							tab[y][x].value = n;
							tab[y][x].canBeModified = false;
							generateSudoku(tab, redo);
							if (!(*redo))
								return;
							tab[y][x].value = 0;
						}
					}
				}
				return;
			}
		}
	}

	(*redo) = false;
}

//Funkcja podobna do powy¿szej, lecz jest przerobiona, aby mog³a dzia³aæ jako osobny w¹tek
void solveSudoku(struct threadInfo* tInfo)
{
	tInfo->inside = true;
	if (!tInfo->decremented)
	{
		tInfo->more--;
		tInfo->decremented = true;
	}
	for (int y = 0; y < sudokuSize; y++)
	{
		for (int x = 0; x < sudokuSize; x++)
		{
			tInfo->tab[y][x].canBeModified = false;
			if (tInfo->more < 0)
				return;

			if (tInfo->tab[y][x].value == 0)
			{
				for (int n = 1; n < 10; n++)
				{
					if (checkRow(tInfo->tab, y, n) && checkColumn(tInfo->tab, x, n) && checkSquare(tInfo->tab, x / 3, y / 3, n))
					{
						tInfo->tab[y][x].value = n;
						solveSudoku(tInfo);

						if (tInfo->more < 0)
							return;

						tInfo->tab[y][x].value = 0;
					}
				}
				return;
			}
		}
	}

	//Dopóki zmienna nie zostanie zinkrementowana poprzez kolejne wciœniêcie klawiszu 'S', czekamy w nieskoñczonej pêtli
	while (tInfo->more == 0)
		sfSleep(sfMilliseconds(20));
}

bool hasWon(struct tileInfo tab[sudokuSize][sudokuSize])
{
	for (int i = 0; i < sudokuSize; i++)
	{
		for (int j = 0; j < sudokuSize; j++)
		{
			if (tab[i][j].value == 0)
				return false;
		}
	}

	return true;
}