//Aluna: Maira Gomes
public class Ackermann {

    // Função de Ackermann
    public static int ackermann(int m, int n) {
        if (m == 0) {
            return n + 1;
        } else if (m > 0 && n == 0) {
            return ackermann(m - 1, 1);
        } else {
            return ackermann(m - 1, ackermann(m, n - 1));
        }
    }

    public static void main(String[] args) {
        long startTime = System.currentTimeMillis();
        long endTime;
        int m, n, result;

        System.out.println("Calculando valores da função de Ackermann que podem ser computados em menos de 1 minuto...");

        for (m = 0; m <= 3; m++) { // Mantenha m pequeno devido ao crescimento rápido
            for (n = 0; n <= 10; n++) { // Ajuste n conforme necessário
                endTime = System.currentTimeMillis();
                if ((endTime - startTime) >= 60000) {
                    System.out.println("Tempo limite atingido.");
                    return;
                }
                result = ackermann(m, n);
                System.out.println("Ackermann(" + m + ", " + n + ") = " + result);
            }
        }
    }
}

