#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void gerarArrayAleatorio(int arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        arr[i] = rand() % 1000;  // Números aleatórios entre 0 e 999
    }
}

double tempoMedioOrdenacao(int tamanho, int numTestes) {
    int *arr = (int *)malloc(tamanho * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Falha na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    double tempoTotal = 0;
    for (int i = 0; i < numTestes; i++) {
        gerarArrayAleatorio(arr, tamanho);
        clock_t inicio = clock();
        bubbleSort(arr, tamanho);
        clock_t fim = clock();
        tempoTotal += (double)(fim - inicio) / CLOCKS_PER_SEC;
    }
    free(arr);
    return tempoTotal / numTestes;
}

int main() {
    srand(time(NULL));
    int tamanhos[] = {10, 100, 1000, 10000, 20000};
    int numTamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);
    int numTestes = 10;

    printf("Tamanho\tTempo Médio (segundos)\n");
    for (int i = 0; i < numTamanhos; i++) {
        double tempoMedio = tempoMedioOrdenacao(tamanhos[i], numTestes);
        printf("%d\t%f\n", tamanhos[i], tempoMedio);
        if (tempoMedio > 60.0) {
            break;  // Para se a ordenação levar mais de 60 segundos
        }
    }
    return 0;
}
