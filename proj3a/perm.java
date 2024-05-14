// Maira Gomes

import java.util.Scanner;

public class Permutacoes {
    public static int calcularFatorial(int valor) {
        if (valor > 12) {
            System.out.println("ALERTA: O valor do fatorial ultrapassa o limite do int");
            return -1; 
        }
        if (valor <= 1)
            return 1;
        else
            return valor * calcularFatorial(valor - 1);
    }
    
    public static int calcularTotalPermutacoes(int quantidade) {
        return calcularFatorial(quantidade);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Digite a quantidade de elementos do conjunto: ");
        int quantidadeElementos = scanner.nextInt();

        int totalPermutacoes = calcularTotalPermutacoes(quantidadeElementos);

        if (totalPermutacoes != -1) {
            System.out.println("O número total de permutações possíveis é: " + totalPermutacoes);
        }
        scanner.close();
    }
}
