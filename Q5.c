#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 1000

int **allocate_matrix(int size) {
    int **matrix = malloc(size * sizeof(int *));
    int i;
    for (i = 0; i < size; i++) {
        matrix[i] = malloc(size * sizeof(int));
    }
    return matrix;
}

void free_matrix(int **matrix, int size) {
	int i;
    for (i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int i, j, k;
    int **A = allocate_matrix(SIZE);
    int **B = allocate_matrix(SIZE);
    int **C = allocate_matrix(SIZE);

    printf("Inicializando matrizes...\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }
    printf("Matrizes inicializadas.\n");

    printf("Iniciando multiplicação de matrizes usando OpenMP...\n");

    #pragma omp parallel for private(i, j, k)
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            C[i][j] = 0;
            for (k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    printf("Parte da matriz resultante C (10x10):\n");
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    printf("Multiplicação de matrizes concluída.\n");

    free_matrix(A, SIZE);
    free_matrix(B, SIZE);
    free_matrix(C, SIZE);

    return 0;
}

