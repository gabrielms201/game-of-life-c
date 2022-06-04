// | EP - JOGO DA VIDA John Conway's Game of Life      |
// | Mayara Meneghetti Honda                  32152280 |
// | Paulo Henrique Braga Cechinel            32151128 |
// | Ricardo Gabriel Marques dos Santos Ruiz  32134908 |
#include <stdio.h>
#include <stdlib.h>

// Descomentar esse define faz com que o programa ja crie uma matriz.
// Fizemos isso para facilitar os testes durante a programacao
//#define TEST_MODE
const int g_ALIVE = 1;
const int g_DEAD = 0;

typedef struct
{
	int rows;
	int columns;
	int** data;
} Matrix;


// Funcao para contar a quantidade de vizinhos vivos dessa celula
int countLiveNearCells(int rowPosition, int columnPosition, Matrix matrix)
{
	int i, j, count = 0;
	// Abaixo fiz esse assing para evitar com que o numero de linhas ou colunas da matrix mude acidentalmente. ("encapsulamento")
	int rows = matrix.rows;
	int columns = matrix.columns;

	for (i = rowPosition - 1; i <= rowPosition + 1; i++)
	{
		for (j = columnPosition - 1; j <= columnPosition + 1; j++)
		{
			if ((i == rowPosition) && (j == columnPosition) || (i < 0 || j < 0) || (i >= rows || j >= columns))
			{
				continue;
			}
			if (matrix.data[i][j] == g_ALIVE)
			{
				count++;
			}
		}
	}
	return count;
}

// Funcao para julgar uma celula a partir de quantos vizinhos ela tem e adicionar na nova matriz gerada
void judgeCell(int rowPosition, int columnPosition, Matrix matrix, Matrix newMatrix)
{
	// Primeiro devemos contar a quantidade de vizinhos vivos dessa celula:
	int nearLivingCells = countLiveNearCells(rowPosition, columnPosition, matrix);

	// Defini um ponteiro para cada celula a fim de ter uma variavel ao inves de acessar toda hora (facilitando a codificacao)
	int* cell = &matrix.data[rowPosition][columnPosition];
	
	// Motivos para a celula viver:
	// Se tiver 2 ou 3 vizinhos, permanece viva
	int livingCondition = *cell == g_ALIVE && (nearLivingCells == 2 || nearLivingCells == 3);
	// Ou Se a celula estiver morta, mas com 3 vizinhos vivos, ela renasce
	int rebirthContition = *cell == g_DEAD && nearLivingCells == 3;
	
	if (livingCondition || rebirthContition)
	{
		newMatrix.data[rowPosition][columnPosition] = g_ALIVE;
	}
	// Motivos para a celula morrer:
	// Se tiver 1 ou 0 vizinhos, morre de solidao
	// Ou se tiver 4 ou mais vizinhos, morre de superpopulacao (podendo ser um else do primeiro)
	else
	{
		newMatrix.data[rowPosition][columnPosition] = g_DEAD;
	}
}

// Funcao para preencher as celulas vivas de acordo com o input do usuario
void fillAliveCellsByInput(Matrix matrix)
{
	// Abaixo fiz esse assing para evitar com que o numero de linhas ou colunas da matrix mude acidentalmente. ("encapsulamento")
	int rows = matrix.rows;
	int columns = matrix.columns;
	printf("-> Informe as celulas vivas: \nOBS: Digite -1 na linha para terminar \n");
	int i;
	for (i = 0; i < rows * columns; i++)
	{
		int row;
		int col;
		printf("\tLinha: ");
		scanf("%d%*c", &row);
		if (row < 0) break;
		printf("\tColuna: ");
		scanf("%d%*c", &col);
		printf("\n");
		matrix.data[row][col] = g_ALIVE;
	}
}

// Funcao feita para facilitar os testes durante a codificacao. Ela pula a etapa de pedir pro usuario digitar as celulas vivas de uma matriz
void mockMatrix(Matrix matrix)
{
	matrix.data[4][5] = g_ALIVE;
	matrix.data[5][4] = g_ALIVE;
	matrix.data[5][5] = g_ALIVE;
	matrix.data[5][6] = g_ALIVE;
	matrix.data[6][5] = g_ALIVE;
}

// Funcao para imprimir uma grade + matriz
void printMatrix(Matrix matrix)
{
	int i;
	int j;
	// Abaixo fiz esse assing para evitar com que o numero de linhas ou colunas da matrix mude acidentalmente. ("encapsulamento")
	int rows = matrix.rows;
	int columns = matrix.columns;

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
			printf("%s|", matrix.data[i][j] == g_DEAD ? "   " : "<X>");
			//printf("%d ", matrix.data[i][j]);
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

// Funcao para alocar os dados da matriz na heap e retornar uma struct "matrix"
Matrix generateMatrix(int rows, int columns)
{
	int i;
	int j;
	Matrix matrix;
	matrix.rows = rows;
	matrix.columns = columns;
	matrix.data = (int**)calloc(rows, sizeof(int*));
	for (i = 0; i < rows; i++)
	{
		matrix.data[i] = (int*)calloc(columns, sizeof(int));
		for (j = 0; j < columns; j++)
		{
			matrix.data[i][j] = g_DEAD;
		}
	}
	return matrix;
}

// Funcao para liberar a matriz da heap
void freeMatrix(Matrix matrix)
{
	int i;
	for (i = 0; i < matrix.columns; i++)
	{
		free(matrix.data[i]);
		matrix.data[i] = NULL;
	}
	free(matrix.data);
}

// Funcao para ler o input do usuario e armazenar as linhas e colunas
void readRowsAndColumns(int* rows, int* columns)
{
	printf("Digite a quantidade de linhas para gerar a matriz: \n");
	scanf("%d", rows);
	printf("Digite a quantidade de colunas desejadas para gerar a matriz: \n");
	scanf("%d", columns);
}
int shouldStop(int *end)
{
	char ch;
	printf("Pressione apenas ENTER para continuar, ou digite qualquer coisa para parar \n");
	scanf("%c", &ch);
	if (ch == '0' || ch != '\n')
	{
		*end = 1;
		return 1;
	}
	return 0;
}
// Funcao para iniciar o jogo da vida
void startGameOfLife()
{
	int rows = 11;
	int columns = 11;
	int end = 0;

#ifndef TEST_MODE
	readRowsAndColumns(&rows, &columns);
	Matrix matrix = generateMatrix(rows, columns);
	fillAliveCellsByInput(matrix);
#else
	Matrix matrix = generateMatrix(rows, columns);
	mockMatrix(matrix);
#endif

	printf("Matriz Inicial: \n");
	printMatrix(matrix);
	while (!end)
	{
		if(shouldStop(&end)) break;
		printf("Proxima Matriz: \n");
		Matrix newMatrix = generateMatrix(rows, columns);
		// Agora sera gerado a nova matrix de acordo com as regras do jogo da vida
		// Para cada celula, sera chamada a funcao que vai ver se ela deve ou nao morrer, e adicionar na nova matriz
		int i, j;
		for (i = 0; i < rows; i++)
		{
			for (j = 0; j < columns; j++)
			{
				judgeCell(i, j, matrix, newMatrix);
			}
		}
		printMatrix(newMatrix);
		// Desaloca da heap a matriz antiga para evitar leaks, e aponta o ponteiro da antiga para a nova.
		freeMatrix(matrix);
		matrix = newMatrix;
	}
	// Limpa a matriz da heap
	freeMatrix(matrix);
}

int main()
{
	startGameOfLife();
	return 0;
}
