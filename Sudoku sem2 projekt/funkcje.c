#pragma warning(disable:4996)
#include "funkcje.h"
#include "struktury.h"

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

bool save(const struct tileInfo tab[sudokuSize][sudokuSize])
{
	FILE* fout = fopen("save.dat", "wb"); // save

	if (fout == NULL)
		return false;

	fwrite(tab, sizeof(struct tileInfo), sudokuSize * sudokuSize, fout);

	fclose(fout);

	return true;
}

bool isValid(struct tileInfo tab[sudokuSize][sudokuSize])
{
	//Sprawdza kolumny i wiersze
	for (int i = 0; i < sudokuSize; i++)
		for (int j = 0; j < sudokuSize; j++)
			for (int k = 0; k < sudokuSize; k++)
				if (j != k && (tab[i][j].value == tab[i][k].value || tab[j][i].value == tab[k][i].value))
					return false;

	//Sprawdza kwadraty
	for (int i = 0; i < sudokuSize / 3; i++)
		for (int j = 0; j < sudokuSize / 3; j++)
			for (int k = 0; k < sudokuSize / 3; k++)
				for (int m = 0; m < sudokuSize / 3; m++)
					for (int n = 0; n < sudokuSize / 3; n++)
						for (int o = 0; o < sudokuSize / 3; o++)
							if (k != n && m != o && tab[i * 3 + k][j * 3 + m].value == tab[i * 3 + n][j * 3 + o].value)
								return false;

	return true;
}

bool load(struct tileInfo tab[sudokuSize][sudokuSize])
{
	struct tileInfo tmp[sudokuSize][sudokuSize];

	memcpy(tmp, tab, sizeof(struct tileInfo) * sudokuSize * sudokuSize);

	FILE* fin = fopen("save.dat", "rb"); // load

	if (fin == NULL)
		return false;

	fseek(fin, 0, SEEK_END);

	int length = ftell(fin);

	fseek(fin, 0, SEEK_SET);

	if (length == sudokuSize * sudokuSize * sizeof(struct tileInfo)) fread(tab, sizeof(struct tileInfo), sudokuSize * sudokuSize, fin);

	fclose(fin);

	if (!isValid(tab) || length != sudokuSize * sudokuSize * sizeof(struct tileInfo))
	{
		memcpy(tab, tmp, sizeof(struct tileInfo) * sudokuSize * sudokuSize);
		return false;
	}

	return true;
}

void displayString(const sfRenderWindow* win, const sfColor color, const sfFont* font, const int x, const int y, const int charSize, const char* napis, const bool center)
{
	sfText* text;
	sfVector2f vec;
	vec.x = x;
	vec.y = y;
	text = sfText_create();
	sfText_setFont(text, font);
	sfText_setColor(text, color);
	sfText_setString(text, napis);
	sfText_setCharacterSize(text, charSize);

	if (center) vec.x = x - sfText_getGlobalBounds(text).width / 2;

	sfText_setPosition(text, vec);

	sfRenderWindow_drawText(win, text, NULL);

	sfText_destroy(text);
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
				//Liczby losowane s� w ten spos�b, aby zapewni� losowo��, podczas generowania sudoku. W przeciwnym razie rozwi�zana tablica Sudoku wygl�da�aby zawsze identycznie
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

//Funkcja podobna do powy�szej, lecz jest przerobiona, aby mog�a dzia�a� jako osobny w�tek
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

	//Dop�ki zmienna nie zostanie zinkrementowana poprzez kolejne wci�ni�cie klawiszu 'S', czekamy w niesko�czonej p�tli
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

void changeDisplayedText(char** dst, char* src, int** positions)
{
	if (*dst != NULL && strcmp(src, *dst) == 0)
		return;

	free(*dst);
	free(*positions);

	*dst = (char*)malloc(strlen(src) * sizeof(char) + 1);
	*positions = (int*)malloc(strlen(src) * sizeof(int));

	strcpy(*dst, src);

	for (int i = 0; i < strlen(src); i++)
		(*positions)[i] = 300 + i * 15;
}

void handleWindow(struct tileInfo tab[sudokuSize][sudokuSize])
{
	//��te k�ko obok kursora
	sfShader* shader;
	shader = sfShader_createFromFile(NULL, NULL, "fragmentshader.frag");

	//Informacje o jednym polu w Sudoku, tablica pomocnicza, gdy wchodzimy do w�tku, aby pokaza� mo�liwe rozwi�zania
	struct tileInfo helpTab[sudokuSize][sudokuSize];

	//Zmienne dotycz�ce okna, tekstur, zegar�w itp
	sfRenderWindow* win;
	sfVideoMode mode = { WIDTH, HEIGHT, 32 };
	sfTexture* tGrid;
	sfSprite* grid;
	sfFont* font;
	sfClock* clock;
	sfThread* thread;

	//Zmienna, w ktorej przechowujemy informacje przekazane w�tkowi
	struct threadInfo tInfo;
	tInfo.tab = tab;
	tInfo.more = -1;
	tInfo.decremented = false;
	tInfo.inside = false;

	//Zmienne eventowe
	bool hasClicked = false;
	bool leftMouse = false;
	bool rightMouse = false;

	bool check = true;

	//Zmienne przechowuj�ce pozycj� i aktualnie wy�wietlany napis stanu gry
	char* wyswietlane = NULL;
	int* positions = NULL;
	changeDisplayedText(&wyswietlane, "Sudoku", &positions);

	//Aktualnie wybrana liczba do wstawienia w pole
	int currentNumber = 0;

	//Pobieranie czcionki, t�a, inicjowanie zmiennych
	font = sfFont_createFromFile("arial.ttf");
	tGrid = sfTexture_createFromFile("sudoku-blankgrid.png", NULL);
	grid = sfSprite_create();
	clock = sfClock_create();
	thread = sfThread_create(solveSudoku, &tInfo);
	sfSprite_setTexture(grid, tGrid, NULL);
	win = sfRenderWindow_create(mode, "Sudoku", sfClose, NULL);
	sfRenderWindow_setVerticalSyncEnabled(win, true);
	sfWindow_setKeyRepeatEnabled(win, false);

	//G��wna p�tla okna
	while (sfRenderWindow_isOpen(win))
	{
		//Resetujemy zmienne eventowe
		hasClicked = false;
		leftMouse = false;
		rightMouse = false;

		//Sprawdzanie event�w okna
		sfEvent event;
		while (sfRenderWindow_pollEvent(win, &event))
		{
			//Zamykamy okno
			if (event.type == sfEvtClosed)
				sfRenderWindow_close(win);
			//Przycisk myszy zosta� wci�ni�ty
			else if (event.type == sfEvtMouseButtonPressed)
			{
				hasClicked = true;

				if (event.mouseButton.button == sfMouseRight)
					rightMouse = true;
				if (event.mouseButton.button == sfMouseLeft)
					leftMouse = true;
			}
			//Przycisk na klawiaturze zosta� wci�ni�ty
			else if (event.type == sfEvtKeyPressed)
			{
				if (!hasWon(tab) || tInfo.inside)
				{
					//Resetujemy i zamykamy w�tek
					if (tInfo.inside && sfKeyboard_isKeyPressed(sfKeyR))
					{
						tInfo.more = -1;
						tInfo.decremented = false;
						tInfo.inside = false;
						sfThread_terminate(thread);
						memcpy(tab, helpTab, sizeof(struct tileInfo) * sudokuSize * sudokuSize);
					}
					//W��czamy w�tek
					else if (!tInfo.inside && sfKeyboard_isKeyPressed(sfKeyS))
					{
						memcpy(helpTab, tab, sizeof(struct tileInfo) * sudokuSize * sudokuSize);
						tInfo.more = 1;
						tInfo.decremented = false;
						sfThread_launch(thread);
					}
					//Ujawniamy kolejne rozwi�zanie (o ile istnieje)
					else if (tInfo.inside && sfKeyboard_isKeyPressed(sfKeyS))
					{
						tInfo.more = 1;
						tInfo.decremented = false;

						sfSleep(sfMilliseconds(25));

						//Je�eli kolejne rozwi�zanie nie istnieje, resetuj i zamknij w�tek
						if (!hasWon(tab))
						{
							tInfo.more = -1;
							tInfo.decremented = false;
							tInfo.inside = false;
							sfThread_terminate(thread);
							memcpy(tab, helpTab, sizeof(struct tileInfo) * sudokuSize * sudokuSize);
						}
					}
				}
			}
		}

		//Zmiana wy�wietlanego tekstu
		if (!tInfo.inside && check)
		{
			if (hasWon(tab))
				changeDisplayedText(&wyswietlane, "Congratulations! You have won!", &positions);
			else
				changeDisplayedText(&wyswietlane, "Sudoku", &positions);

			check = false;
		}

		//Czy zosta�y wci�nite przyciski wczytaj, zapisz, generuj
		if (sfMouse_getPosition(win).y >= 0 && sfMouse_getPosition(win).y <= 53 && hasClicked)
		{
			int num = 0;
			for (int i = 0; i < 3; i++)
			{
				if (sfMouse_getPosition(win).x >= 302 + i * 48 && sfMouse_getPosition(win).x < 302 + (i + 1) * 48)
				{
					num = i + 1;
					break;
				}
			}

			switch (num)
			{
			case 1:
			{
				if (save(tab))
					changeDisplayedText(&wyswietlane, "Saved", &positions);
				else
					changeDisplayedText(&wyswietlane, "Couldn't save", &positions);
			} break;
			case 2:
			{
				if (load(tab))
					changeDisplayedText(&wyswietlane, "Loaded", &positions);
				else
					changeDisplayedText(&wyswietlane, "Couldn't load", &positions);
			} break;
			case 3:
			{
				fillSudoku(tab, 0);
				bool redo = true;
				generateSudoku(tab, &redo);
				removeElements(tab, elementsToRemove);
				memcpy(helpTab, tab, sudokuSize * sudokuSize);
				changeDisplayedText(&wyswietlane, "Generated", &positions);
			} break;
			}
		}

		//U�ytkownik zmieni� liczb�
		if (sfMouse_getPosition(win).y >= 488 && sfMouse_getPosition(win).y <= 533 && hasClicked)
		{
			for (int i = 0; i < 9; i++)
			{
				if (sfMouse_getPosition(win).x >= 8 + i * 48.5 + (int)(i / 3) * 3 && sfMouse_getPosition(win).x < 8 + (i + 1) * 48.5 + (int)(i / 3) * 4)
				{
					currentNumber = i + 1;
					break;
				}
			}
		}
		//U�ytkownik chce zmieni� liczb� w tablicy sudoku
		else if (hasClicked)
		{
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (sfMouse_getPosition(win).x >= 8 + i * 48.5 + (int)(i / 3) * 3 && sfMouse_getPosition(win).x < 8 + (i + 1) * 48.5 + (int)(i / 3) * 4
						&& sfMouse_getPosition(win).y >= 61 + j * 46.5 && sfMouse_getPosition(win).y < 61 + (j + 1) * 46.5)
					{
						if (leftMouse && tab[j][i].canBeModified && checkColumn(tab, i, currentNumber) && checkRow(tab, j, currentNumber) && checkSquare(tab, i / 3, j / 3, currentNumber))
						{
							tab[j][i].value = currentNumber;
							check = true;
						}
						if (rightMouse && tab[j][i].canBeModified)
						{
							tab[j][i].value = 0;
							check = true;
						}
					}
				}
			}
		}

		//Informacje dotycz�ce shadera
		sfShader_setFloat2Parameter(shader, "mousePos", sfMouse_getPosition(win).x, HEIGHT - sfMouse_getPosition(win).y);

		//Czy�cimy okno kolorem czarnym
		sfRenderWindow_clear(win, sfBlack);

		//U�ywamy shadera do rysowania na ekranie
		sfShader_bind(shader);

		//Rysujemy plansz�
		sfRenderWindow_drawSprite(win, grid, NULL);

		//Pozbywamy si� shadera
		sfShader_bind(NULL);

		//Czy mamy przesun�� aktualnie wy�wietlany tekst
		bool wys = false;

		if (sfClock_getElapsedTime(clock).microseconds >= 250000)
		{
			sfClock_restart(clock);
			wys = true;
		}

		//Logika dotycz�ca przesuwania tekstu / Wy�wietlanie tekstu
		for (int i = 0; i < strlen(wyswietlane); i++)
		{
			if (positions[i] < 300)
			{
				char str[2] = "\0";
				str[0] = wyswietlane[i];
				displayString(win, sfBlack, font, positions[i], 20, 20, str, true);
			}

			if (wys)
			{
				positions[i] -= 15;

				if (positions[i] <= 18)
				{
					positions[i] = (strlen(wyswietlane) * 19 > 300 ? strlen(wyswietlane) * 19 : 300);
					check = true;
				}
			}
		}

		//Wy�wietlamy liczby przechowane w tablicy na ekran w odpowiednie miejsca
		char c[2];
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (tab[i][j].value != 0)
				{
					sprintf_s(c, sizeof(int), "%d", tab[i][j].value);
					displayString(win, tab[i][j].canBeModified ? sfBlack : sfBlue, font, 30 + j * 48.5, 58 + i * 47.5, 32, c, true);
				}
			}
		}

		for (int i = 0; i < 9; i++)
		{
			sprintf_s(c, sizeof(int), "%d", i + 1);
			displayString(win, sfBlack, font, 30 + i * 48.5, 488, 32, c, true);
		}

		//Renderujemy zmiany na okno
		sfRenderWindow_display(win);
	}

	//Po wyj�ciu z okna, czy�cimy po siebie

	sfThread_terminate(thread);

	sfRenderWindow_destroy(win);
	sfFont_destroy(font);
	sfTexture_destroy(tGrid);
	sfSprite_destroy(grid);
	sfClock_destroy(clock);
	sfShader_destroy(shader);

	free(positions);
	free(wyswietlane);
}