#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node* left;
    struct Node* right;
} Node;

#define LETTER 0
#define NUMBER 1
#define UNKNOWN 99

#define INT_LIT 10
#define ID 11
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define PAREN_ESQ 25
#define PAREN_DIR 26
#define END_LINE 27

int classChar;
char lex[100];
char nextChar;
int lexema;
int proxToken;
FILE *entrada;
int aceita;

int charLookup(char ch);
void charAppend();
void getNextChar();
void skipBlank();
int lexer();
Node* expression();
Node* term();
Node* factor();
void err(int value);

Node* newNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void preOrderPrint(Node* root) {
    if (root != NULL) {
        printf(" %d ", root->val);
        preOrderPrint(root->left);
        preOrderPrint(root->right);
    }
}

int charLookup(char ch) {
    switch (ch) {
        case '(':
            charAppend();
            proxToken = PAREN_ESQ;
            break;
        case ')':
            charAppend();
            proxToken = PAREN_DIR;
            break;
        case '+':
            charAppend();
            proxToken = ADD_OP;
            break;
        case '-':
            charAppend();
            proxToken = SUB_OP;
            break;
        case '*':
            charAppend();
            proxToken = MULT_OP;
            break;
        case '/':
            charAppend();
            proxToken = DIV_OP;
            break;
        case '$':
            charAppend();
            proxToken = END_LINE;
            break;
        default:
            charAppend();
            proxToken = EOF;
            break;
    }
    return proxToken;
}

void charAppend() {
    if (lexema <= 98) {
        lex[lexema++] = nextChar;
        lex[lexema] = '\0';
    } else {
        printf("TK_ERRO: LEXEMA LONGO \n");
    }
}

void getNextChar() {
    if ((nextChar = getc(entrada)) != EOF) {
        if (isalpha(nextChar))
            classChar = LETTER;
        else if (isdigit(nextChar))
            classChar = NUMBER;
        else
            classChar = UNKNOWN;
    } else {
        classChar = EOF;
    }
}

void skipBlank() {
    while (isspace(nextChar))
        getNextChar();
}

int lexer() {
    lexema = 0;
    skipBlank();
    switch (classChar) {
        case LETTER:
            charAppend();
            getNextChar();
            while (classChar == LETTER || classChar == NUMBER) {
                charAppend();
                getNextChar();
            }
            proxToken = ID;
            break;
        case NUMBER:
            charAppend();
            getNextChar();
            while (classChar == NUMBER) {
                charAppend();
                getNextChar();
            }
            proxToken = INT_LIT;
            break;
        case UNKNOWN:
            charLookup(nextChar);
            getNextChar();
            break;
        case EOF:
            proxToken = EOF;
            lex[0] = 'E';
            lex[1] = 'O';
            lex[2] = 'F';
            lex[3] = '\0';
            break;
    }
    printf("PROX TOKEN: %d == PROXIMO LEXEMA: %s\n", proxToken, lex);
    return proxToken;
}

Node* expression() {
    Node* node = term();
    while (proxToken == ADD_OP || proxToken == SUB_OP) {
        int tok = proxToken;
        lexer();
        Node* newNode = malloc(sizeof(Node));
        newNode->val = tok;
        newNode->left = node;
        newNode->right = term();
        node = newNode;
    }
    return node;
}

Node* term() {
    Node* node = factor();
    while (proxToken == MULT_OP || proxToken == DIV_OP) {
        int tok = proxToken;
        lexer();
        Node* newNode = malloc(sizeof(Node));
        newNode->val = tok;
        newNode->left = node;
        newNode->right = factor();
        node = newNode;
    }
    return node;
}

Node* factor() {
    Node* node = NULL;
    if (proxToken == ID || proxToken == INT_LIT) {
        node = newNode(proxToken);
        lexer();
    } else {
        if (proxToken == PAREN_ESQ) {
            lexer();
            node = expression();
            if (proxToken == PAREN_DIR) {
                lexer();
            } else {
                err(1);
            }
        } else {
            err(2);
        }
    }
    return node;
}

void err(int value) {
    aceita = 1;
    switch (value) {
        case 1:
            printf("ERRO!!\nTK_ERRO: Esperava um delimitador direito\n");
            break;
        case 2:
            printf("\nERRO!!\n*TK_ERRO: não é um id, um literal int ou delimitador esquerdo \n");
            break;
        default:
            printf("\nERRO!!\n");
            break;
    }
}

int main() {
    if ((entrada = fopen("entrada.txt", "r")) == NULL) {

    } else {
        getNextChar();
        do {
            printf("\n");
            lexer();
            Node* root = expression();

            if (aceita == 0) {
                printf("\n");
                printf("        - ANÁLISE  - \n");
                printf("       VETOR DE TOKENS          [");
                preOrderPrint(root);
                printf("]\n\n==>>> ACEITA!!");
            } else {
                printf("============================================\n");
            }
            aceita = 0;
        } while (proxToken != EOF);
    }
    return 0;
}
