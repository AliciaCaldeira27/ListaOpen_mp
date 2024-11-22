#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define MAX 100000

// Função para verificar se um número é primo
int is_prime(int num) {
	int i;
    if (num < 2) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    for (i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main() {
	int i;
    printf("Iniciando cálculo de números primos até %d usando OpenMP...\n", MAX);

    #pragma omp parallel for
    
    for (i = 0; i < MAX; i++) {
        if (is_prime(i)) {
            #pragma omp critical
            {
                printf("Primo encontrado: %d\n", i);
            }
        }
    }

    printf("Cálculo de números primos concluído.\n");
    return 0;
}

