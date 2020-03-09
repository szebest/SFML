#pragma warning(disable:4996)
#include <SFML/Graphics.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define sudokuSize 9

#define elementsToRemove 50

#define WIDTH 453

#define HEIGHT 542

typedef struct tileInfo
{
	int value;
	bool canBeModified;
}tileInfo;

typedef struct
{
	tileInfo(*tab)[sudokuSize];
	short int more;
	bool decremented;
	int level;
}threadInfo;

void save(tileInfo tab[sudokuSize][sudokuSize])
{
	FILE* fout = fopen("save.dat", "wb"); // save

	fwrite(tab, sizeof(struct tileInfo), sudokuSize * sudokuSize, fout);

	fclose(fout);
}

void load(tileInfo tab[sudokuSize][sudokuSize])
{
	//if( access( "save.dat", F_OK ) == -1 )
		//return false;

	FILE* fin = fopen("save.dat", "rb"); // save

	fread(tab, sizeof(struct tileInfo), sudokuSize * sudokuSize, fin);

	fclose(fin);

	//return true;
}

void displayString(sfRenderWindow* win, sfColor color, sfFont* font, int x, int y, int charSize, char* napis, bool center)
{
	sfText* text;
	sfVector2f vec;
	vec.x = x;
	vec.y = y;
	text = sfText_create();
	sfText_setFont(text, font);
	sfText_setColor(text, color);
	sfText_setString(text, napis);
	sfText_setPosition(text, vec);
	sfText_setCharacterSize(text, charSize);

	vec.x = x - sfText_getGlobalBounds(text).width / 2;

	if (center) sfText_setPosition(text, vec);

	sfRenderWindow_drawText(win, text, NULL);

	sfText_destroy(text);
}

bool checkColumn(tileInfo tab[sudokuSize][sudokuSize], int i, int number)
{
	for (int j = 0; j < sudokuSize; j++)
	{
		if (tab[j][i].value == number)
			return false;
	}

	return true;
}

bool checkRow(tileInfo tab[sudokuSize][sudokuSize], int i, int number)
{
	for (int j = 0; j < sudokuSize; j++)
	{
		if (tab[i][j].value == number)
			return false;
	}

	return true;
}

bool checkSquare(tileInfo tab[sudokuSize][sudokuSize], int x, int y, int number)
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

void fillSudoku(tileInfo tab[sudokuSize][sudokuSize], int number)
{
	for (int i = 0; i < sudokuSize; i++)
	{
		for (int j = 0; j < sudokuSize; j++)
		{
			tab[i][j].value = number;
		}
	}
}

void removeElements(tileInfo tab[sudokuSize][sudokuSize], int elements)
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

void generateSudoku(tileInfo tab[sudokuSize][sudokuSize], bool* redo)
{
	for (int y = 0; y < sudokuSize; y++)
	{
		for (int x = 0; x < sudokuSize; x++)
		{
			if (!(*redo))
				return;

			if (tab[y][x].value == 0)
			{
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

void solveSudoku(threadInfo* tInfo)
{
	tInfo->level++;
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
			{
				tInfo->level--;
				return;
			}

			if (tInfo->tab[y][x].value == 0)
			{
				for (int n = 1; n < 10; n++)
				{
					if (checkRow(tInfo->tab, y, n) && checkColumn(tInfo->tab, x, n) && checkSquare(tInfo->tab, x / 3, y / 3, n))
					{
						tInfo->tab[y][x].value = n;
						solveSudoku(tInfo);

						if (tInfo->more < 0)
						{
							tInfo->level--;
							return;
						}

						tInfo->tab[y][x].value = 0;
					}
				}
				return;
			}
		}
	}
	while (tInfo->more == 0)
		sfSleep(sfMilliseconds(100));
	tInfo->level--;
}

bool hasWon(tileInfo tab[sudokuSize][sudokuSize])
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
	free(*dst);
	free(*positions);

	*dst = (char*)malloc(strlen(src) * sizeof(char) + 1);
	*positions = (int*)malloc(strlen(src) * sizeof(int));

	memcpy(*dst, src, strlen(src) + 1);

	for (int i = 0; i < strlen(src); i++)
		(*positions)[i] = 300 + i * 15;
}

void handleWindow(tileInfo tab[sudokuSize][sudokuSize])
{
	sfShader* shader;
	shader = sfShader_createFromFile(NULL, NULL, "fragmentshader.frag");

	tileInfo helpTab[sudokuSize][sudokuSize];
	sfRenderWindow* win;
	sfVideoMode mode = { WIDTH, HEIGHT, 32 };
	sfTexture* tGrid;
	sfSprite* grid;
	sfFont* font;
	sfClock* clock;
	sfThread* thread;
	threadInfo tInfo;
	tInfo.tab = tab;
	tInfo.more = -1;
	tInfo.decremented = false;
	tInfo.level = 0;
	bool hasClicked = false;
	bool leftMouse = false;
	bool rightMouse = false;
	bool released = false;

	short unsigned int winningState = 0;

	char* wyswietlane = NULL;
	int* positions = NULL;
	changeDisplayedText(&wyswietlane, "Sudoku", &positions);

	int currentNumber = 0;

	font = sfFont_createFromFile("arial.ttf");
	tGrid = sfTexture_createFromFile("sudoku-blankgrid.png", NULL);
	grid = sfSprite_create();
	clock = sfClock_create();
	thread = sfThread_create(solveSudoku, &tInfo);
	sfSprite_setTexture(grid, tGrid, NULL);
	win = sfRenderWindow_create(mode, "Sudoku", sfClose, NULL);
	sfRenderWindow_setFramerateLimit(win, 60);
	sfWindow_setKeyRepeatEnabled(win, false);
	while (sfRenderWindow_isOpen(win))
	{
		hasClicked = false;
		leftMouse = false;
		rightMouse = false;

		sfEvent event;
		while (sfRenderWindow_pollEvent(win, &event))
		{
			if (event.type == sfEvtClosed)
				sfRenderWindow_close(win);
			else if (event.type == sfEvtMouseButtonPressed)
			{
				hasClicked = true;

				if (event.mouseButton.button == sfMouseRight)
					rightMouse = true;
				if (event.mouseButton.button == sfMouseLeft)
					leftMouse = true;
			}
			else if (event.type == sfEvtKeyPressed)
			{
				if ((tInfo.level > 0 && sfKeyboard_isKeyPressed(sfKeyR)) || (tInfo.level > 0 && sfKeyboard_isKeyPressed(sfKeyS) && tInfo.decremented == false))
				{
					winningState = 1;
					tInfo.more = -1;
					tInfo.decremented = false;
					tInfo.level = 0;
					sfThread_terminate(thread);
					memcpy(tab, helpTab, sizeof(struct tileInfo) * sudokuSize * sudokuSize);
				}
				else if (tInfo.level == 0 && sfKeyboard_isKeyPressed(sfKeyS))
				{
					winningState = 2;
					memcpy(helpTab, tab, sizeof(struct tileInfo) * sudokuSize * sudokuSize);
					tInfo.more = 1;
					tInfo.decremented = false;
					tInfo.level = 0;
					sfThread_launch(thread);
				}
				else if (tInfo.level > 0 && sfKeyboard_isKeyPressed(sfKeyS))
				{
					tInfo.more = 1;
					tInfo.decremented = false;
				}
			}
		}

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
				save(tab);
			} break;
			case 2:
			{
				load(tab);
				winningState = 1;
			} break;
			case 3:
			{
				fillSudoku(tab, 0);
				bool redo = true;
				generateSudoku(tab, &redo);
				removeElements(tab, elementsToRemove);
				memcpy(helpTab, tab, sudokuSize * sudokuSize);
				winningState = 1;
			} break;
			}
		}

		if (winningState == 1)
		{
			changeDisplayedText(&wyswietlane, "Sudoku", &positions);
			winningState = 0;
		}

		else if (winningState == 2)
		{
			changeDisplayedText(&wyswietlane, "Sudoku", &positions);
			winningState = 3;
		}

		else if (hasWon(tab) && winningState == 0)
		{
			changeDisplayedText(&wyswietlane, "Congratulations! You won!", &positions);
			winningState = 4;
		}

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
							tab[j][i].value = currentNumber;
						if (rightMouse && tab[j][i].canBeModified)
						{
							tab[j][i].value = 0;
							winningState = 1;
						}
					}
				}
			}
		}

		sfShader_setFloat2Parameter(shader, "mousePos", sfMouse_getPosition(win).x, HEIGHT - sfMouse_getPosition(win).y);

		sfRenderWindow_clear(win, sfBlack);

		sfShader_bind(shader);

		sfRenderWindow_drawSprite(win, grid, NULL);

		sfShader_bind(NULL);

		bool wys = false;

		if (sfClock_getElapsedTime(clock).microseconds >= 250000)
		{
			sfClock_restart(clock);
			wys = true;
		}

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
					positions[i] = (strlen(wyswietlane) * 19 * sizeof(char) > 300 ? strlen(wyswietlane) * 19 * sizeof(char) : 300);
			}
		}


		char c[12];
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

		sfRenderWindow_display(win);

	}

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

int main()
{
	srand(time(NULL));
	tileInfo tab[sudokuSize][sudokuSize];
	fillSudoku(tab, 0);
	bool redo = true;
	generateSudoku(tab, &redo);
	removeElements(tab, elementsToRemove);
	handleWindow(tab);
	return 0;
}