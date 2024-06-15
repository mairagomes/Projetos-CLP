#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função de ordenação Merge Sort
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

// Função de ordenação Merge Sort recursiva
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Função para imprimir um array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Função para gerar um array aleatório de tamanho 'size'
void generateRandomArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000; // Números aleatórios de 0 a 999
    }
}

// Função para medir o tempo de execução do Merge Sort em um array de tamanho 'size'
double measureMergeSortTime(int arr[], int size) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    mergeSort(arr, 0, size - 1);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

int main() {
    srand(time(0)); // Inicializa o gerador de números aleatórios

    // Definindo os tamanhos das listas a serem testadas
    int sizes[] = {10, 100, 1000, 10000, 100000, 1000000}; // Adicione mais tamanhos conforme necessário

    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("Tamanho da lista, Tempo médio (s)\n");

    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];
        double total_time = 0.0;
        int num_trials = 5; // Número de vezes que o algoritmo será executado para obter a média

        for (int j = 0; j < num_trials; j++) {
            int* arr = (int*)malloc(size * sizeof(int));
            generateRandomArray(arr, size);

            total_time += measureMergeSortTime(arr, size);

            free(arr);
        }

        double average_time = total_time / num_trials;
        printf("%d, %.6f\n", size, average_time);
    }

    return 0;
}
