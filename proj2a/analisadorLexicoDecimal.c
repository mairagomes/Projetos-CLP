//Aluna: Maira Gomes Santos

#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *arquivo;
    char arq[] = "arquivo.txt"; 
    char caracter[200]; 
    int i = 0;
    char c;
    int linha_reconhecida = 1;
    int linha_nao_reconhecida = 1;

    arquivo = fopen(arq, "r");
    if (arquivo == NULL) {
        return 1;
    }

    printf("caracter reconhecido:       | caracteres não reconhecidos:\n");
    printf("----------------------------------+-------------------------------------\n"); //

leitura:
    c = fgetc(arquivo);
    if (c == EOF) {
        goto fim;
    }

    if (isdigit(c)) {
        caracter[i++] = c;
        goto leitura;
    } else if (isspace(c)) {
        if (i > 0) {
            caracter[i] = '\0'; 
            printf("%2d | %10s                         \n", linha_reconhecida++, caracter);
      
            i = 0; // 
        }
        goto leitura;
    } else {
        caracter[i++] = c;
        while ((c = fgetc(arquivo)) != EOF && !isspace(c)) {
            caracter[i++] = c; 
        }
        caracter[i] = '\0'; 
        printf("   |                        | %2d | %-20s \n", linha_nao_reconhecida++, caracter);
       
        i = 0; 
        goto leitura;
    }

fim:
    if (i > 0) {
        caracter[i] = '\0'; 
        printf("%2d | %10s                         \n", linha_reconhecida++, caracter);
    }
    fclose(arquivo);

    return 0;
}
