//Aluna: Maira Gomes

#include <stdio.h>
#include <time.h>

// Função de Ackermann
unsigned int ackermann(unsigned int m, unsigned int n) {
    if (m == 0) {
        return n + 1;
    } else if (m > 0 && n == 0) {
        return ackermann(m - 1, 1);
    } else {
        return ackermann(m - 1, ackermann(m, n - 1));
    }
}

int main() {
    unsigned int m, n, result;
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    printf("Calculando valores da função de Ackermann que podem ser computados em menos de 1 minuto...\n");

    for (m = 0; m <= 3; ++m) { // Mantenha m pequeno devido ao crescimento rápido
        for (n = 0; n <= 10; ++n) { // Ajuste n conforme necessário
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            if (cpu_time_used >= 60.0) {
                printf("Tempo limite atingido.\n");
                return 0;
            }
            result = ackermann(m, n);
            printf("Ackermann(%u, %u) = %u\n", m, n, result);
        }
    }

    return 0;
}

