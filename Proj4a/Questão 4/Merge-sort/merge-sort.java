import java.util.Arrays;
import java.util.Random;

public class ComparacaoMergeSort {

    public static void main(String[] args) {
        int[] tamanhos = {10, 100, 1000, 10000, 50000, 100000, 500000, 1000000};

        System.out.println("Comparação de Desempenho do Merge Sort");
        System.out.println("-------------------------------------");
        System.out.println("Tamanho \t| Tempo Médio (ms)");
        System.out.println("-------------------------------------");

        for (int tamanho : tamanhos) {
            long tempoTotal = 0;
            int[] arr;

            // Executar 10 testes e calcular o tempo médio
            for (int teste = 0; teste < 10; teste++) {
                arr = gerarArrayAleatorio(tamanho);
                
                long tempoInicial = System.nanoTime();
                mergeSort(arr);
                long tempoFinal = System.nanoTime();
                
                // Converter nanossegundos para milissegundos
                long duracaoMs = (tempoFinal - tempoInicial) / 1000000;
                tempoTotal += duracaoMs;
            }

            // Calcular o tempo médio
            long tempoMedio = tempoTotal / 10;

            System.out.printf("%d \t\t| %d%n", tamanho, tempoMedio);
        }
    }

    // Método para gerar um array de inteiros aleatórios de tamanho especificado
    private static int[] gerarArrayAleatorio(int tamanho) {
        int[] arr = new int[tamanho];
        Random random = new Random();
        for (int i = 0; i < tamanho; i++) {
            arr[i] = random.nextInt(1000); // Números aleatórios até 999
        }
        return arr;
    }

    // Implementação do Merge Sort
    public static void mergeSort(int[] arr) {
        mergeSort(arr, 0, arr.length - 1);
    }

    private static void mergeSort(int[] arr, int l, int r) {
        if (l < r) {
            int m = (l + r) / 2;
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);
            merge(arr, l, m, r);
        }
    }

    private static void merge(int[] arr, int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;
        int[] L = new int[n1];
        int[] R = new int[n2];

        for (int i = 0; i < n1; ++i)
            L[i] = arr[l + i];
        for (int j = 0; j < n2; ++j)
            R[j] = arr[m + 1 + j];

        int i = 0, j = 0;
        int k = l;
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
    }
}
