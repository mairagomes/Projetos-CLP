import java.util.Arrays;
import java.util.Random;

public class Main {
    void bubbleSort(int arr[]) {
        int n = arr.length;
        for (int i = 0; i < n - 1; i++)
            for (int j = 0; j < n - i - 1; j++)
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
    }

    public static void main(String args[]) {
        Main ob = new Main();
        Random random = new Random();
        int maxSize = 100000; // Tamanho máximo da lista

        // Loop para diferentes tamanhos de lista
        for (int size = 10; size <= maxSize; size *= 10) {
            long totalTime = 0;

    
            for (int i = 0; i < 10; i++) {
                int[] arr = new int[size];

                // Gera lista aleatória
                for (int j = 0; j < size; j++) {
                    arr[j] = random.nextInt();
                }

                // Medir tempo de ordenação
                long startTime = System.nanoTime();
                ob.bubbleSort(arr);
                long endTime = System.nanoTime();
                long duration = (endTime - startTime);

                // Add ao tempo total
                totalTime += duration;
            }

            
            long averageTime = totalTime / 10;

            System.out.println("Tamanho da Lista: " + size + ", Tempo Médio: " + averageTime + " nanossegundos");
        }
    }
}
