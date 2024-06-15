//para executar: gcc -o insertion_sort insertion_sort.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Cannot open input file");
        return 1;
    }

    int arr[10000];
    int n = 0;

    while (fscanf(file, "%d", &arr[n]) != EOF) {
        n++;
    }
    fclose(file);

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    insertionSort(arr, n);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    FILE *output = fopen("output.txt", "w");
    for (int i = 0; i < n; i++) {
        fprintf(output, "%d ", arr[i]);
    }
    fclose(output);

    printf("Time taken: %f seconds\n", cpu_time_used);

    return 0;
}
