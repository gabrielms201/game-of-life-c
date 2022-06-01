// | EP - JOGO DA VIDA John Conway's Game of Life      |
// | Mayara Meneghetti Honda                  32152280 |
// | Paulo Henrique Braga Cechinel            32151128 |
// | Ricardo Gabriel Marques dos Santos Ruiz  32134908 |
#include <stdio.h>
#include <stdlib.h>
//#define TEST_MODE

void fillMatrix(int rows, int columns, int** matrix)
{
    printf("-> Informe as celulas vivas: \nOBS: Digite -1 na linha para terminar \n");
    int i;
    for (int i = 0; i < rows * columns; i++)
    {
        int row;
        int col;
        printf("\tLinha: ");
        scanf("%d", &row);
        if (row < 0) break;
        printf("\tColuna: ");
        scanf("%d", &col);
        printf("\n");
        matrix[row][col] = 1;
    }
}

void mockMatrix(int** matrix)
{
    matrix[0][1] = 1;
    matrix[1][0] = 1;
    matrix[2][1] = 1;
    matrix[3][1] = 1;
}

void printMatrix(int rows, int columns, int **matrix)
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
            printf("%s|", matrix[i][j] == 0 ? "   " : "<X>");
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

int **generateMatrix(int rows, int columns)
{
    int i;
    int **matrix = (int**) calloc(rows, sizeof(int *));
    for (i = 0; i < rows; i++)
    {
        matrix[i] = (int *) calloc(columns, sizeof(int));
        for (int j = 0; j < columns; j++)
        {
            matrix[i][j] = 0;
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

void readRowsAndColumns(int *rows, int *columns)
{
    printf("Digite a quantidade de linhas para gerar a matriz: \n");
    scanf("%d", rows);
    printf("Digite a quantidade de colunas desejadas para gerar a matriz: \n");
    scanf("%d", columns);
}

void gameOfLife()
{
    int rows = 4;
    int columns = 4;

#ifndef TEST_MODE
    readRowsAndColumns(&rows, &columns);
#endif
    int** matrix = generateMatrix(rows, columns);
    
#ifdef TEST_MODE
    mockMatrix(matrix);
#else
    fillMatrix(rows, columns, matrix);
#endif
    printMatrix(rows, columns, matrix);
    freeMatrix(columns, matrix);
}
int main()
{
    gameOfLife();
    return 0;
}
