#pragma warning(disable:4996)
#include "io.h"

bool save(const struct tileInfo tab[sudokuSize][sudokuSize])
{
	FILE* fout = fopen("save.dat", "wb"); // save

	if (fout == NULL)
		return false;

	fwrite(tab, sizeof(struct tileInfo), sudokuSize * sudokuSize, fout);

	fclose(fout);

	return true;
}

bool load(struct tileInfo tab[sudokuSize][sudokuSize])
{
	FILE* fin = fopen("save.dat", "rb"); // load

	if (fin == NULL)
		return false;

	struct tileInfo tmp[sudokuSize][sudokuSize];

	fseek(fin, 0, SEEK_END);

	int length = ftell(fin);

	fseek(fin, 0, SEEK_SET);

	if (length == sudokuSize * sudokuSize * sizeof(struct tileInfo))
	{
		memcpy(tmp, tab, sizeof(struct tileInfo) * sudokuSize * sudokuSize);
		fread(tab, sizeof(struct tileInfo), sudokuSize * sudokuSize, fin);
	}
	else
	{
		fclose(fin);
		return false;
	}

	fclose(fin);

	if (!isValid(tab))
	{
		memcpy(tab, tmp, sizeof(struct tileInfo) * sudokuSize * sudokuSize);
		return false;
	}

	return true;
}