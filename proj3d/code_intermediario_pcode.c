#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ADD 2
#define SUB 3
#define MUL 4
#define DIV 5

void processar_linha(char *linha, int memoria[]);
void empilhar_valor(char variavel, int memoria[]);
void processar_operacao(const char *operacao);

int main() {
    int memoria[8]; // Endereços de memória para a, b, c, d, e

    // Valores predefinidos para os endereços de memória
    memoria[3] = 1; // Valor para a
    memoria[4] = 5; // Valor para b
    memoria[5] = 4; // Valor para c
    memoria[6] = 2; // Valor para d
    memoria[7] = 3; // Valor para e

    FILE *arquivo = fopen("input.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo input.txt\n");
        return -1;
    }

    printf("\nIniciando leitura do código intermediário...\n");

    char linha[256];
    int codigo_atual = 1;
    printf("=== Início do Código %d ===\n", codigo_atual);
    printf("Inicializando pilha: INT 0 7\n");

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strncmp(linha, "###", 3) == 0) {
            codigo_atual++;
            printf("Finalizando código: OPR 0 0\n");
            printf("\n=== Início do Código %d ===\n", codigo_atual);
            printf("Inicializando pilha: INT 0 7\n");
        } else {
            processar_linha(linha, memoria);
        }
    }
    printf("Finalizando código: OPR 0 0\n");

    fclose(arquivo);

    printf("\nLeitura do código intermediário concluída.\n");

    return 0;
}

void processar_linha(char *linha, int memoria[]) {
    if (strncmp(linha, "PUSH(", 5) == 0) {
        char variavel = linha[5];
        empilhar_valor(variavel, memoria);
    } else if (strstr(linha, "y=POP(); x=POP(); PUSH(") != NULL) {
        processar_operacao(linha);
    }
}

void empilhar_valor(char variavel, int memoria[]) {
    int indice;
    switch (variavel) {
        case 'a':
            indice = 3;
            break;
        case 'b':
            indice = 4;
            break;
        case 'c':
            indice = 5;
            break;
        case 'd':
            indice = 6;
            break;
        case 'e':
            indice = 7;
            break;
        default:
            return;
    }
    printf("Carregando valor de %c na pilha: LOD 0 %d\n", variavel, indice);
}

void processar_operacao(const char *operacao) {
    if (strstr(operacao, "PUSH(x ADD y)") != NULL) {
        printf("Realizando operação ADD: OPR 0 %d\n", ADD);
    } else if (strstr(operacao, "PUSH(x SUB y)") != NULL) {
        printf("Realizando operação SUB: OPR 0 %d\n", SUB);
    } else if (strstr(operacao, "PUSH(x MUL y)") != NULL) {
        printf("Realizando operação MUL: OPR 0 %d\n", MUL);
    } else if (strstr(operacao, "PUSH(x DIV y)") != NULL) {
        printf("Realizando operação DIV: OPR 0 %d\n", DIV);
    }
}
