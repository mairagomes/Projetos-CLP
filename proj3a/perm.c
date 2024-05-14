// Maira Gomes, questao 4

#include <stdio.h>
unsigned long long int calcularFatorial(int n) {
    unsigned long long int resultado = 1;
    for (int i = 1; i <= n; i++) {
        resultado *= i;
    }
    return resultado;
}


unsigned long long int calcularPermutacoes(int quantidade) {
    unsigned long long int permutacoes = 1;
    for (int i = 1; i <= quantidade; i++) {
        permutacoes *= i;
    }
    return permutacoes;
}

int main() {
    int quantidadeElementos;
    printf("Digite a quantidade de elementos: ");
    scanf("%d", &quantidadeElementos);

    if (quantidadeElementos <= 0) {
        printf("A quantidade de elementos deve ser um número positivo.\n");
        return 1;
    }

    unsigned long long int fatorial = calcularFatorial(quantidadeElementos);
    unsigned long long int permutacoes = calcularPermutacoes(quantidadeElementos);
    printf("O fatorial de %d é: %llu\n", quantidadeElementos, fatorial);
    printf("O número de permutações possíveis é: %llu\n", permutacoes);

    return 0;
}
