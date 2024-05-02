//Aluna: Maira Gomes Santos

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_TREE_SIZE 100

// Declaração e inicialização das variáveis globais
int arvore[MAX_TREE_SIZE]; // Array para a árvore
int indice_arvore = 0; // Índice para controlar a árvore

char pilha[MAX_STACK_SIZE]; // Array para a pilha
int topo_pilha, indice_cadeia; // Variáveis de controle da pilha e da cadeia de entrada

// Função para empilhar um caractere na pilha
void empilhar(char *pilha, char caractere){
    topo_pilha++;
    pilha[topo_pilha] = caractere;
}

// Função para ler um caractere da cadeia de entrada
char lerCaractere(const char* cadeia){
    return cadeia[indice_cadeia++];
}

// Função para desempilhar um caractere da pilha
void desempilhar(){
    topo_pilha--;
}

// Função para imprimir a pilha (apenas para fins de depuração)
void imprimir_pilha() {
    printf("Pilha: ");
    for (int i = topo_pilha; i >= 0; i--) {
        printf("%c ", pilha[i]);
    }
    printf("\n");
}

// Função principal para validar as cadeias de entrada
const char* validarCadeias(const char* cadeia) { 
    topo_pilha = -1; // Inicializa o topo da pilha
    indice_cadeia = 0; // Inicializa o índice da cadeia de entrada
    char token; // Variável para armazenar o caractere atual

    // Estado inicial do autômato
    ESTADO_INICIAL:
        empilhar(pilha, 'S'); // Empilha o símbolo inicial 'S' na pilha
        token = lerCaractere(cadeia); // Lê o primeiro caractere da cadeia de entrada
        imprimir_pilha(); // Imprime a pilha (para fins de depuração)
    goto ESTADO_FINAL; // Transição para o estado final

    // Estado final do autômato
    ESTADO_FINAL:
        // Verifica se o token atual é 'a' e o topo da pilha é 'S'
        if(token == 'a' && pilha[topo_pilha] == 'S'){ 
            desempilhar(); 
            empilhar(pilha, 'b'); 
            empilhar(pilha, 'S'); 
            empilhar(pilha, 'a');
            printf("Regra 1: S -> aSb\n"); 
        }
        
        else if (token == 'b' && pilha[topo_pilha] == 'S'){ 
            desempilhar(); 
            empilhar(pilha, 'b'); 
            empilhar(pilha, 'S'); 
            empilhar(pilha, 'a'); 
            printf("Regra 1: S -> aSb\n");
        } 
        else if (token == 'c' && pilha[topo_pilha] == 'S') { 
            desempilhar(); 
            empilhar(pilha, 'c'); 
            printf("Regra 2: S -> c\n");
        }
          //Condiçao para desempilhar símbolos terminais
        else if (token == 'a' && pilha[topo_pilha] == 'a') { 
            desempilhar(); 
            token = lerCaractere(cadeia);
        } 
        else if (token == 'b' && pilha[topo_pilha] == 'b') { 
            desempilhar(); 
            token = lerCaractere(cadeia);
        } 
        else if (token == 'c' && pilha[topo_pilha] == 'c') { 
            desempilhar(); 
            token = lerCaractere(cadeia);
        } 
  // Verifica se chegou ao fim da cadeia de entrada
          else if (token == '\0') { 
              // Se a pilha estiver vazia, a cadeia é aceita
              if (topo_pilha == -1) {
                  return "ACEITA"; 
              }
              // Caso contrário, a cadeia é rejeitada
              return "REJEITADA"; 
          } 
          // Se nenhuma das condições anteriores for atendida, a cadeia é rejeitada
          else {
              return "REJEITADA";
          }
      goto ESTADO_FINAL; // Retorna ao estado final
  }

// Função principal
int main() {
    FILE *arquivo; // Ponteiro para o arquivo de entrada
    char cadeia[50]; // Array para armazenar a cadeia de entrada
    arquivo = fopen("entrada.txt", "r"); // Abre o arquivo para leitura
    if (arquivo == NULL) {
        return 1; // Retorna 1 se houver erro ao abrir o arquivo
    }    
    // Lê cada cadeia do arquivo e as valida
    while (fscanf(arquivo, "%s", cadeia) != EOF) {
        const char* resultado = validarCadeias(cadeia); // Chama a função de validação
        printf("CADEIA ===  %s\nResultado: %s\n", cadeia, resultado); // Imprime o resultado
        printf("\n");
    }
    fclose(arquivo); // Fecha o arquivo
    return 0; // Retorna 0 indicando sucesso
}
