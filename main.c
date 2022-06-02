// | EP - JOGO DA VIDA John Conway's Game of Life      |
// | Mayara Meneghetti Honda                  32152280 |
// | Paulo Henrique Braga Cechinel            32151128 |
// | Ricardo Gabriel Marques dos Santos Ruiz  32134908 |
#include <stdio.h>
#include <stdlib.h>

#define TEST_MODE
const int g_ALIVE = 1;
const int g_DEAD = 0;


int countLiveNearCells(int rowPosition, int columnPosition, int** matrix, int rows, int columns)
{
	int i, j, count = 0;
	for (i = rowPosition - 1; i <= rowPosition + 1; i++)
	{
		for (j = columnPosition - 1; j <= columnPosition + 1; j++)
		{
			if ((i == rowPosition) && (j == columnPosition) || (i < 0 || j < 0) || (i >= rows || j >= columns))
			{
				continue;
			}
			if (matrix[i][j] == g_ALIVE)
			{
				count++;
			}
		}
	}
	return count;
}

void judgeCell(int rowPosition, int columnPosition, int** matrix, int rows, int columns, int** newMatrix)
{
	int nearLivingCells = countLiveNearCells(rowPosition, columnPosition, matrix, rows, columns);

	int* cell = &matrix[rowPosition][columnPosition];
	// Se tiver 2 ou 3 vizinhos, permanece viva
	// Ou Se a celula estiver morta, mas com 3 vizinhos vivos, ela renasce
	if (*cell == g_ALIVE && (nearLivingCells == 2 || nearLivingCells == 3) || (*cell == g_DEAD && nearLivingCells == 3))
	{
		newMatrix[rowPosition][columnPosition] = g_ALIVE;
	}
	// Se tiver 1 ou 0 vizinhos, morre de solidao ou se tiver 4 ou mais, morre de superpopulacao
	/*else if (nearLivingCells == 1 || nearLivingCells == 0 || nearLivingCells >= 4)
	{
		*cell = g_DEAD;
	}*/
	else
	{
		newMatrix[rowPosition][columnPosition] = g_DEAD;
	}
}


void fillMatrix(int rows, int columns, int** matrix)
{
	printf("-> Informe as celulas vivas: \nOBS: Digite -1 na linha para terminar \n");
	int i;
	for (i = 0; i < rows * columns; i++)
	{
		int row;
		int col;
		printf("\tLinha: ");
		scanf("%d", &row);
		if (row < 0) break;
		printf("\tColuna: ");
		scanf("%d", &col);
		printf("\n");
		matrix[row][col] = g_ALIVE;
	}
}

void mockMatrix(int** matrix)
{
	matrix[4][5] = g_ALIVE;
	matrix[5][4] = g_ALIVE;
	matrix[5][5] = g_ALIVE;
	matrix[5][6] = g_ALIVE;
	matrix[6][5] = g_ALIVE;
}

void printMatrix(int rows, int columns, int** matrix)
{
	int i;
	int j;

	for (i = 0; i < rows; i++)
	{
		// Imprime o tracejado das linhas
		for (j = 0; j < columns; j++)
		{
			printf("----");
		}
		printf("-\n");
		// Imprime a linha
		printf("|");
		for (j = 0; j < columns; j++)
		{
			printf("%s|", matrix[i][j] == g_DEAD ? "   " : "<X>");
			//printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	// Imprime o ultimo tracejado das linhas
	for (i = 0; i < columns; i++)
	{
		printf("----");
	}
	printf("-\n");
}

int** generateMatrix(int rows, int columns)
{
	int i;
	int** matrix = (int**)calloc(rows, sizeof(int*));
	for (i = 0; i < rows; i++)
	{
		matrix[i] = (int*)calloc(columns, sizeof(int));
		for (int j = 0; j < columns; j++)
		{
			matrix[i][j] = g_DEAD;
		}
	}
	return matrix;
}

void freeMatrix(int columns, int** matrix)
{
	int i;
	for (i = 0; i < columns; i++)
	{
		free(matrix[i]);
		matrix[i] = NULL;
	}
	free(matrix);
}

void readRowsAndColumns(int* rows, int* columns)
{
	printf("Digite a quantidade de linhas para gerar a matriz: \n");
	scanf("%d", rows);
	printf("Digite a quantidade de colunas desejadas para gerar a matriz: \n");
	scanf("%d", columns);
}

void gameOfLife()
{
	int rows = 100;
	int columns = 100;
	int end = 0;

#ifndef TEST_MODE
	readRowsAndColumns(&rows, &columns);
#endif
	int** matrix = generateMatrix(rows, columns);

#ifdef TEST_MODE
	mockMatrix(matrix);
#else
	fillMatrix(rows, columns, matrix);
#endif

	printf("Matriz Inicial: \n");
	printMatrix(rows, columns, matrix);
	while (!end)
	{
		int i;
		int j;
		printf("Proxima Matriz: \n");
		int** newMatrix = generateMatrix(rows, columns);
		for (i = 0; i < rows; i++)
		{
			for (j = 0; j < columns; j++)
			{
				judgeCell(i, j, matrix, rows, columns, newMatrix);
			}
		}
		printMatrix(rows, columns, newMatrix);
		printf("Pressione qualquer tecla para continuar, ou digite (0) para parar: \n");
		char* choice = "";
		scanf("%s*c", choice);
		matrix = newMatrix;
		if (strcmp(choice, "0") == 0)
		{
			end = 1;
		}
		
	}
	freeMatrix(columns, matrix);
}

int main()
{
	gameOfLife();
	return 0;
}
