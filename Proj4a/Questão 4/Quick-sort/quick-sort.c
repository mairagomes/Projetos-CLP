#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para trocar dois elementos
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Função para particionar o array
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Função para implementar o QuickSort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Função para imprimir o array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Função para preencher o array com números aleatórios
void fillArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000; // Preenche com números aleatórios de 0 a 999
    }
}

// Função para medir o tempo médio de ordenação
double measureSortTime(int size, int numTrials) {
    int* arr = (int*)malloc(size * sizeof(int));
    clock_t start, end;
    double totalTime = 0;

    for (int i = 0; i < numTrials; i++) {
        fillArray(arr, size);
        start = clock();
        quickSort(arr, 0, size - 1);
        end = clock();
        totalTime += (double)(end - start) / CLOCKS_PER_SEC;
    }

    free(arr);
    return totalTime / numTrials;
}

int main() {
    int sizes[] = {10, 100, 1000, 10000, 100000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    int numTrials = 10;

    for (int i = 0; i < numSizes; i++) {
        double avgTime = measureSortTime(sizes[i], numTrials);
        printf("Tamanho: %d, Tempo médio: %f segundos\n", sizes[i], avgTime);
    }

    return 0;
}
