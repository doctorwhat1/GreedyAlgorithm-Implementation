#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 200


void MoveStr(char str[])
{
	int i = 0;
	int j = 0;

	while ((str[i] != ' ') && (str[i] != '\n') && strlen(str) > 1)
	{
		for (j = 0; j < strlen(str); j++)
		{
			str[j] = str[j + 1];
		}
	}
	if (strlen(str) > 0)
	{
		for (j = 0; j < strlen(str); j++)
		{
			str[j] = str[j + 1];
		}
	}
}

void PrintMatrix(int a[SIZE][SIZE], int ROWS, int COL)
{
	int i = 0;
	int j = 0;
	for (i = 0; i <= ROWS; i++)
	{
		for (j = 0; j <= COL; ++j)
		{
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
}



int FindRoute(int a[SIZE][SIZE], int StartingCity, int amount, int printallowed)
{
	int i = 0;
	int allvisited = 1;
	int flag = -1;
	int minID = 0;
	int minVAL = 0;
	int visited[SIZE] = { 0 };
	int value = 0;

	int costTotal = 0;
	int ROW = StartingCity;
	int COL = 0;



	while (printallowed<3)
	{
		visited[ROW] = 1;
		if (printallowed == 1)
		{
			printf("%d ", ROW); //minID
		}
		minID = 0;
		minVAL = 0;
		flag = -1;
		COL = 0;
		i = 0;

		for (COL = 0; COL <= amount; COL++)
		{
			if ((a[ROW][COL] != 0) && (visited[COL] != 1) && (COL!=ROW))
			{
				if (flag == -1)
				{
					flag = 1;
					minID = COL;
					minVAL = a[ROW][COL];
				}
				else
				{
					if (minVAL > a[ROW][COL])
					{
						minID = COL;
						minVAL = a[ROW][COL];
					}
				}

			}
		}
		// после этого цикла мы нашли номер пункта, который мы не посетили и с минимальным проездом далее ИЛИ НЕТ
		if (flag == 1)
		{
			costTotal = costTotal + minVAL;
			ROW = minID;
			// идём в тот город

		}
		else
		{
			// проверяем все ли города мы посетили. Если нет, то выводим -1

			for (i = 0; i <= amount; i++)
			{
				if (visited[i] == 0)
				{
					allvisited = 0;
				}
			}
			// если мы не посетили все города или дороги из конечного в начальный нет, то пишем -1, иначе - цену
			if ((allvisited == 0) || (a[ROW][StartingCity] == 0))
			{
				value = -1;
			}
			if ((allvisited == 1) && (a[ROW][StartingCity]!=0))
			{
				costTotal = costTotal + a[ROW][StartingCity];
				value = costTotal;
			}

			break;

		}
	}

	return(value);
}



int main(int argc, char* argv[])
{
	// Открываем файлы
	FILE* fr = fopen("input.txt", "r");
	if (!fr)
	{
		printf("Error opening file for reading\n");
		return -2;
	}

	FILE* fw = fopen("output.txt", "w");
	if (!fw)
	{
		printf("Error opening file for reading\n");
		return -3;
	}

	int a[SIZE][SIZE] = { 0 };

	int results[SIZE] = { 0 };
	int visited[SIZE] = { 0 };
	int i = 0;
	int j = 0;
	int k = 0;
	int x = 0;
	int amount = 0;
	int temp = 0;
	int ROW = 0;
	int COL = 0;
	int StartingCity = 0;

	char str1[SIZE] = { 0 };
	char str2[SIZE] = { 0 };

	fgets(str1, SIZE, fr);

	amount = atoi(str1);

	amount--;


	while (!feof(fr))
	{
		fgets(str1, SIZE, fr);
		COL = 0;
		while ((strlen(str1) > 0) && (str1[0] != '\n') && (str1[0] != ' '))
		{
			a[ROW][COL] = atoi(str1);
			MoveStr(str1);
			COL++;

		}
		ROW++;
	}



	for (k = 0; k <= amount; k++)
	{

		results[k] = FindRoute(a, k, amount,0);

	}




	int minNUM = 0;
	int minVAL = 0;

	int flag = 0;

	for (i = 0; i <= amount; i++)
	{
		if (results[i] != -1)
		{
			if (flag == 0)
			{
				flag = 1;
				minNUM = i;
				minVAL = results[i];

			}
			else
			{
				if (results[i] < minVAL)
				{
					minNUM = i;
					minVAL = results[i];

				}

			}
		}
		


	}
	if (flag == 0)
	{
		printf("Lost");
	}
	else
	{
		printf("Path:\n");

		//int FindRoute(int a[SIZE][SIZE], int StartingCity, int amount, int printallowed)

		k = FindRoute(a, minNUM, amount, 1);
		printf("%d ", minNUM);
		printf("\nCost: %d", k);
	}

	return 0;

}