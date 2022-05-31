// | EP - JOGO DA VIDA John Conway's Game of Life      |
// | Mayara Meneghetti Honda                  32152280 |
// | Paulo Henrique Braga Cechinel            32151128 |
// | Ricardo Gabriel Marques dos Santos Ruiz  32134908 |
#include <stdio.h>
#include <stdlib.h>


//void generateMatrix(int **matrix, int lines, int columns);

void *generateMatrix(int rows, int columns)
{
    int (*matrix)[columns] = malloc (sizeof(int[rows][columns]));
    if (matrix == NULL)
    {
        fprintf(stderr, "Falha ao tentar alocar memoria da matriz\n");
        exit(-1);
    }
    return matrix;
}
void readRowsAndColumns(int* rows, int* columns)
{
    printf("Digite a quantidade de linhas para gerar a matriz: \n");
    scanf("%d", &*rows);
    printf("Digite a quantidade de colunas desejadas para gerar a matriz: \n");
    scanf("%d", &*columns);
}


int main()
{
    int rows = 1;
    int columns = 2;
    //readRowsAndColumns(&rows, &columns);

    int (*matrix)[columns] = generateMatrix(rows,columns);

    printf("%d", matrix[0][0]);
    free(matrix[rows]);
    return 0;

}
