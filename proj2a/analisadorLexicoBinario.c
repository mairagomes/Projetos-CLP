//Aluna: Maira Gomes

#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *arquivo;
    char arq[] = "arquivo.txt"; 
    char token[200];
    int i = 0;
    char c;
    int linha_reconhecida = 1;
    int linha_nao_reconhecida = 1;

    arquivo = fopen(arq, "r");
    if (arquivo == NULL) {
        
        return 1;
    }

  printf("numero binário recinhecido  | numeros binarios não reconhecidos:\n");
  printf("----------------------------------+-------------------------------------\n"); //

leitura:
    c = fgetc(arquivo);
    if (c == EOF) {
        goto fim;
    }

    if (c == '0' || c == '1') {
        token[i++] = c;
        goto leitura;
    } else if (isspace(c)) {
        if (i > 0) {
            token[i] = '\0';
          printf("%2d | %10s                         \n", linha_reconhecida++, token);
            i = 0;
        }
        goto leitura;
    } else {
        token[i++] = c;
        while ((c = fgetc(arquivo)) != EOF && !isspace(c)) {
            token[i++] = c;
        }
        token[i] = '\0';
        printf("   |                        | %2d | %-40s \n", linha_nao_reconhecida++, token);
        i = 0;
        goto leitura;
    }

fim:
    if (i > 0) {
        token[i] = '\0';
        printf("%2d | %10s   \n", linha_reconhecida++, token);
    }
    fclose(arquivo);

    return 0;
}
