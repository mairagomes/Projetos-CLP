import java.util.Random;

public class InsertionSortPerformance {

    void insertionSort(int arr[]) {
        int n = arr.length;
        for (int i = 1; i < n; ++i) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }

    void printArray(int arr[]) {
        int n = arr.length;
        for (int i = 0; i < n; ++i)
            System.out.print(arr[i] + " ");
        System.out.println();
    }

    long measureExecutionTime(int[] arr) {
        long startTime = System.nanoTime();
        insertionSort(arr);
        long endTime = System.nanoTime();
        return endTime - startTime; // Tempo em nanossegundos
    }

    void generateAndTestArrays(int maxSize) {
        Random random = new Random();
        System.out.println("Tamanho do array, Tempo médio (em nanossegundos)");

        for (int size = 10; size <= maxSize; size *= 10) {
            long totalTime = 0;

            // Executar várias vezes e tirar a média
            int[] arr = new int[size];
            int numTrials = Math.max(10000000 / size, 1); // ajuste para o tamanho do array

            for (int trial = 0; trial < numTrials; trial++) {
                // Preencher o array com números aleatórios
                for (int i = 0; i < size; i++) {
                    arr[i] = random.nextInt();
                }

                totalTime += measureExecutionTime(arr);
            }

            long averageTime = totalTime / numTrials;
            System.out.println(size + ", " + averageTime);
        }
    }

    public static void main(String args[]) {
        InsertionSortPerformance ob = new InsertionSortPerformance();
        ob.generateAndTestArrays(1000000); // Tamanho máximo ajustado conforme necessário
    }
}
