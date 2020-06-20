#pragma warning(disable:4996)
#include "gui.h"

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
	//¯ó³te kó³ko obok kursora
	sfShader* shader;
	shader = sfShader_createFromFile(NULL, NULL, "fragmentshader.frag");

	//Informacje o jednym polu w Sudoku, tablica pomocnicza, gdy wchodzimy do w¹tku, aby pokazaæ mo¿liwe rozwi¹zania
	struct tileInfo helpTab[sudokuSize][sudokuSize];

	//Zmienne dotycz¹ce okna, tekstur, zegarów itp
	sfRenderWindow* win;
	sfVideoMode mode = { WIDTH, HEIGHT, 32 };
	sfTexture* tGrid;
	sfSprite* grid;
	sfFont* font;
	sfClock* clock;
	sfThread* thread;

	//Zmienne listy jednokierunkowej
	struct tile_history* tile_head = NULL;
	struct action_history* action_head = NULL;

	//Zmienna, w ktorej przechowujemy informacje przekazane w¹tkowi
	struct threadInfo tInfo;
	tInfo.tab = tab;
	tInfo.more = -1;
	tInfo.amount = 0;
	tInfo.decremented = false;
	tInfo.inside = false;

	//Zmienne eventowe
	bool hasClicked = false;
	bool leftMouse = false;
	bool rightMouse = false;

	bool check = true;

	//Zmienne przechowuj¹ce pozycjê i aktualnie wyœwietlany napis stanu gry
	char* wyswietlane = NULL;
	int* positions = NULL;
	changeDisplayedText(&wyswietlane, "Sudoku", &positions);

	//Aktualnie wybrana liczba do wstawienia w pole
	int currentNumber = 0;

	//Pobieranie czcionki, t³a, inicjowanie zmiennych
	font = sfFont_createFromFile("arial.ttf");
	tGrid = sfTexture_createFromFile("sudoku-blankgrid.png", NULL);
	grid = sfSprite_create();
	clock = sfClock_create();
	thread = sfThread_create(solveSudoku, &tInfo);
	sfSprite_setTexture(grid, tGrid, NULL);
	win = sfRenderWindow_create(mode, "Sudoku", sfClose, NULL);
	sfRenderWindow_setFramerateLimit(win, 60);
	sfWindow_setKeyRepeatEnabled(win, false);

	action_dodajNaKoniecListyJednokierunkowej(&action_head, "Otwarto aplikacjê");

	//G³ówna pêtla okna
	while (sfRenderWindow_isOpen(win))
	{
		//Resetujemy zmienne eventowe
		hasClicked = false;
		leftMouse = false;
		rightMouse = false;

		//Sprawdzanie eventów okna
		sfEvent event;
		while (sfRenderWindow_pollEvent(win, &event))
		{
			//Zamykamy okno
			if (event.type == sfEvtClosed)
				sfRenderWindow_close(win);
			//Przycisk myszy zosta³ wciœniêty
			else if (event.type == sfEvtMouseButtonPressed)
			{
				hasClicked = true;

				if (event.mouseButton.button == sfMouseRight)
					rightMouse = true;
				if (event.mouseButton.button == sfMouseLeft)
					leftMouse = true;
			}
			//Przycisk na klawiaturze zosta³ wciœniêty
			else if (event.type == sfEvtKeyPressed)
			{
				if (!hasWon(tab) || tInfo.inside)
				{
					//Resetujemy i zamykamy w¹tek
					if (tInfo.inside && sfKeyboard_isKeyPressed(sfKeyR))
					{
						tInfo.more = -1;
						tInfo.decremented = false;
						tInfo.inside = false;
						tInfo.amount = 0;
						sfThread_terminate(thread);
						memcpy(tab, helpTab, sizeof(struct tileInfo) * sudokuSize * sudokuSize);

						action_dodajNaKoniecListyJednokierunkowej(&action_head, "U¿ytkownik wy³¹czy³ podpowiedzi");
					}
					//W³¹czamy w¹tek
					else if (!tInfo.inside && sfKeyboard_isKeyPressed(sfKeyS))
					{
						memcpy(helpTab, tab, sizeof(struct tileInfo) * sudokuSize * sudokuSize);
						tInfo.more = 1;
						tInfo.amount++;
						tInfo.decremented = false;
						tInfo.inside = true;

						char buffer[100];

						sprintf(buffer, "Pokazano mo¿liwe rozwiazanie nr %d", tInfo.amount);

						action_dodajNaKoniecListyJednokierunkowej(&action_head, buffer);

						sfThread_launch(thread);
					}
					//Ujawniamy kolejne rozwi¹zanie (o ile istnieje)
					else if (tInfo.inside && sfKeyboard_isKeyPressed(sfKeyS))
					{
						tInfo.more = 1;
						tInfo.amount++;
						tInfo.decremented = false;

						sfSleep(sfMilliseconds(15));

						//Je¿eli kolejne rozwi¹zanie nie istnieje, resetuj i zamknij w¹tek
						if (!hasWon(tab))
						{
							tInfo.more = -1;
							tInfo.decremented = false;
							tInfo.inside = false;
							tInfo.amount = 0;
							sfThread_terminate(thread);
							memcpy(tab, helpTab, sizeof(struct tileInfo) * sudokuSize * sudokuSize);

							action_dodajNaKoniecListyJednokierunkowej(&action_head, "Brak dodatkowych rozwi¹zañ");
							action_dodajNaKoniecListyJednokierunkowej(&action_head, "U¿ytkownik wy³¹czy³ podpowiedzi");
						}
						else
						{
							char buffer[100];

							sprintf(buffer, "Pokazano mo¿liwe rozwi¹zanie nr %d", tInfo.amount);

							action_dodajNaKoniecListyJednokierunkowej(&action_head, buffer);
						}
					}
				}

				if (!tInfo.inside)
				{
					//Cofiemy do stanu poprzedniego
					if (sfKeyboard_isKeyPressed(sfKeyZ))
					{
						if (tile_head)
						{
							char buffer[100];

							sprintf(buffer, "Cofniêto ruch z liczby %d na liczbe %d na pozycji %d, %d", tab[tile_head->y][tile_head->x].value, tile_head->value, tile_head->x, tile_head->y);

							action_dodajNaKoniecListyJednokierunkowej(&action_head, buffer);
						}
						tile_czytajPoczatekListyJednokierunkowej(&tile_head, tab);
					}

					//Inna forma wpisywania liczb do tablicy Sudoku
					if (event.text.unicode - 75 >= 0 && event.text.unicode - 75 < 10)
					{
						hasClicked = true;
						leftMouse = true;
						currentNumber = event.text.unicode - 75;

						char buffer[100];

						sprintf(buffer, "U¿ytkownik wybra³ liczbê %d", currentNumber);

						action_dodajNaKoniecListyJednokierunkowej(&action_head, buffer);
					}

					//0 w unicodzie ma wartosc 75
				}
			}
		}

		//Zmiana wyœwietlanego tekstu
		if (check)
		{
			if (hasWon(tab) && !tInfo.inside)
			{
				changeDisplayedText(&wyswietlane, "Congratulations! You have won!", &positions);
				action_dodajNaKoniecListyJednokierunkowej(&action_head, "U¿ytkownik wygral");
			}
			else
				changeDisplayedText(&wyswietlane, "Sudoku", &positions);

			check = false;
		}

		//Czy zosta³y wciœnite przyciski wczytaj, zapisz, generuj
		if (!tInfo.inside)
		{
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
					{
						changeDisplayedText(&wyswietlane, "Saved", &positions);
						action_dodajNaKoniecListyJednokierunkowej(&action_head, "Zapisano");
					}
					else
					{
						changeDisplayedText(&wyswietlane, "Couldn't save", &positions);
						action_dodajNaKoniecListyJednokierunkowej(&action_head, "Nie uda³o siê zapisaæ");
					}
				} break;
				case 2:
				{
					if (load(tab))
					{
						tile_usunListeJednokierunkowa(&tile_head);
						changeDisplayedText(&wyswietlane, "Loaded", &positions);
						action_dodajNaKoniecListyJednokierunkowej(&action_head, "Wczytano");
					}
					else
					{
						changeDisplayedText(&wyswietlane, "Couldn't load", &positions);
						action_dodajNaKoniecListyJednokierunkowej(&action_head, "Nie uda³o siê wczytaæ");
					}
				} break;
				case 3:
				{
					tile_usunListeJednokierunkowa(&tile_head);
					fillSudoku(tab, 0);
					bool redo = true;
					generateSudoku(tab, &redo);
					removeElements(tab, elementsToRemove);
					memcpy(helpTab, tab, sudokuSize * sudokuSize);
					changeDisplayedText(&wyswietlane, "Generated", &positions);
					action_dodajNaKoniecListyJednokierunkowej(&action_head, "Wygenerowano now¹ tablicê");
				} break;
				default:
					break;
				}
			}
		}

		//U¿ytkownik zmieni³ liczbê
		if (sfMouse_getPosition(win).y >= 488 && sfMouse_getPosition(win).y <= 533 && hasClicked)
		{
			for (int i = 0; i < 9; i++)
			{
				if (sfMouse_getPosition(win).x >= 8 + i * 48.5 + (int)(i / 3) * 3 && sfMouse_getPosition(win).x < 8 + (i + 1) * 48.5 + (int)(i / 3) * 4)
				{
					currentNumber = i + 1;

					char buffer[100];

					sprintf(buffer, "U¿ytkownik wybra³ liczbê %d", currentNumber);

					action_dodajNaKoniecListyJednokierunkowej(&action_head, buffer);
					break;
				}
			}
		}
		//U¿ytkownik chce zmieniæ liczbê w tablicy sudoku
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
							tile_dodajDoListyJednokierunkowej(&tile_head, tab[j][i].value, i, j);
							tab[j][i].value = currentNumber;

							char buffer[100];

							sprintf(buffer, "U¿ytkownik wpisa³ liczbê %d na pozycjê %d, %d", currentNumber, i, j);

							action_dodajNaKoniecListyJednokierunkowej(&action_head, buffer);

							check = true;
						}
						if (rightMouse && tab[j][i].canBeModified)
						{
							char buffer[100];

							sprintf(buffer, "U¿ytkownik usun¹³ liczbê %d z pozycji %d, %d", tab[j][i].value, i, j);

							action_dodajNaKoniecListyJednokierunkowej(&action_head, buffer);

							tile_dodajDoListyJednokierunkowej(&tile_head, tab[j][i].value, i, j);
							tab[j][i].value = 0;
							check = true;
						}
					}
				}
			}
		}

		//Informacje dotycz¹ce shadera
		sfShader_setFloat2Parameter(shader, "mousePos", sfMouse_getPosition(win).x, HEIGHT - sfMouse_getPosition(win).y);

		//Czyœcimy okno kolorem czarnym
		sfRenderWindow_clear(win, sfBlack);

		//U¿ywamy shadera do rysowania na ekranie
		sfShader_bind(shader);

		//Rysujemy planszê
		sfRenderWindow_drawSprite(win, grid, NULL);

		//Pozbywamy siê shadera
		sfShader_bind(NULL);

		//Czy mamy przesun¹æ aktualnie wyœwietlany tekst
		bool wys = false;

		if (sfClock_getElapsedTime(clock).microseconds >= 250000)
		{
			sfClock_restart(clock);
			wys = true;
		}

		//Logika dotycz¹ca przesuwania tekstu / Wyœwietlanie tekstu
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

		//Wyœwietlamy liczby przechowane w tablicy na ekran w odpowiednie miejsca
		char c[2];
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (tab[i][j].value != 0)
				{
					c[0] = '0' + tab[i][j].value;
					c[1] = '\0';
					displayString(win, tab[i][j].canBeModified ? sfBlack : sfBlue, font, 30 + j * 48.5, 58 + i * 47.5, 32, c, true);
				}
			}
		}

		for (int i = 0; i < 9; i++)
		{
			c[0] = '0' + i + 1;
			c[1] = '\0';
			displayString(win, sfBlack, font, 30 + i * 48.5, 488, 32, c, true);
		}

		//Renderujemy zmiany na okno
		sfRenderWindow_display(win);
	}

	action_dodajNaKoniecListyJednokierunkowej(&action_head, "Zamkniêto aplikacjê");

	action_zapiszListeJednokierunkowaDoPliku(action_head);

	//Po wyjœciu z okna, czyœcimy po siebie

	sfThread_terminate(thread);

	sfRenderWindow_destroy(win);
	sfFont_destroy(font);
	sfTexture_destroy(tGrid);
	sfSprite_destroy(grid);
	sfClock_destroy(clock);
	sfShader_destroy(shader);

	free(positions);
	free(wyswietlane);

	tile_usunListeJednokierunkowa(&tile_head);
	action_usunListeJednokierunkowa(&action_head);
}