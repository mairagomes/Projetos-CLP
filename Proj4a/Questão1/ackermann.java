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
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        System.out.print("Digite os valores de m e n: ");
        int m = scanner.nextInt();
        int n = scanner.nextInt();
        System.out.println("Ackermann(" + m + ", " + n + ") = " + ackermann(m, n));
    }
}
