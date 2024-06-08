//Aluna: Maira Gomes

#include <stdio.h>

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
    unsigned int m, n;
    printf("Digite os valores de m e n: ");
    scanf("%u %u", &m, &n);
    printf("Ackermann(%u, %u) = %u\n", m, n, ackermann(m, n));
    return 0;
}
