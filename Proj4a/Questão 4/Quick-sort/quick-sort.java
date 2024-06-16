import java.util.Arrays;
import java.util.Random;

public class QuickSortBenchmark {

    public static void main(String[] args) {
        int[] sizes = {10, 100, 1000, 10000}; // Tamanhos das listas a serem testadas

        // Executando para cada tamanho de lista
        for (int size : sizes) {
            System.out.println("Tamanho da lista: " + size);
            double totalTime = 0; // Para armazenar o tempo total gasto nas ordenações

            // Executando múltiplas vezes para obter um tempo médio
            int numTests = 10; // Número de vezes que cada tamanho de lista será testado
            for (int i = 0; i < numTests; i++) {
                int[] arr = generateRandomArray(size); // Gerando lista aleatória de tamanho 'size'

                // Clonando a lista para manter a original intacta para cada teste
                int[] arrCopy = arr.clone();

                long startTime = System.nanoTime();
                QuickSort ob = new QuickSort();
                ob.sort(arrCopy, 0, arrCopy.length - 1);
                long endTime = System.nanoTime();

                double duration = (endTime - startTime) / 1e6; // Convertendo para milissegundos
                System.out.println("Execução " + (i + 1) + ": " + duration + " ms");
                totalTime += duration;
            }

            double averageTime = totalTime / numTests;
            System.out.println("Tempo médio: " + averageTime + " ms\n");
        }
    }

    // Método para gerar um array de inteiros aleatórios
    private static int[] generateRandomArray(int size) {
        Random random = new Random();
        int[] arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = random.nextInt(); // Gerando números inteiros aleatórios
        }
        return arr;
    }

    // Classe Quicksort implementada
    static class QuickSort {
        int partition(int arr[], int low, int high) {
            int pivot = arr[high];
            int i = (low - 1);
            for (int j = low; j < high; j++) {
                if (arr[j] < pivot) {
                    i++;
                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
            int temp = arr[i + 1];
            arr[i + 1] = arr[high];
            arr[high] = temp;
            return i + 1;
        }

        void sort(int arr[], int low, int high) {
            if (low < high) {
                int pi = partition(arr, low, high);
                sort(arr, low, pi - 1);
                sort(arr, pi + 1, high);
            }
        }
    }
}
