#include <stdio.h>

#define MAX_SIZE 1024
#define MAX_WORD 100
#define POLISH_SIZE 50

char tree[MAX_SIZE];
int indexStack[MAX_WORD];
char symbolStack[MAX_WORD];
char input[MAX_WORD];
char reversePolish[POLISH_SIZE];

int topIndex = 0;
int topSymbols = 0;
int nextSymbol = 0;
int topPolish = 0;

int popIndex() {
    return indexStack[--topIndex];
}

void pushIndex(int value) {
    indexStack[topIndex++] = value;
}

int readTopIndex() {
    return indexStack[topIndex - 1];
}

void initializeTree(char *tree) {
    for (int i = 0; i < MAX_SIZE; i++)
        tree[i] = ' ';
}

void addToTree(int p) {
    if (p == 0) {
        tree[0] = 'E';
        pushIndex(0);
    } else {
        int current = popIndex();
        switch (p) {
            case 1:
                tree[5 * current + 1] = '(';
                tree[5 * current + 2] = 'E';
                tree[5 * current + 3] = 'X';
                tree[5 * current + 4] = 'E';
                tree[5 * current + 5] = ')';
                pushIndex(5 * current + 4);
                pushIndex(5 * current + 3);
                pushIndex(5 * current + 2);
                break;
            case 2:
                tree[5 * current + 1] = '0';
                break;
            case 3:
                tree[5 * current + 1] = '1';
                break;
            case 4:
                tree[5 * current + 1] = 'a';
                break;
            case 5:
                tree[5 * current + 1] = 'b';
                break;
            case 6:
                tree[5 * current + 1] = 'c';
                break;
            case 7:
                tree[5 * current + 1] = '+';
                break;
            case 8:
                tree[5 * current + 1] = '-';
                break;
            case 9:
                tree[5 * current + 1] = '*';
                break;
            case 10:
                tree[5 * current + 1] = '/';
                break;
        }
    }
}

void convertToBinaryTree(char *newTree) {
    int parent, ancestor;

    initializeTree(newTree);

    for (int i = MAX_SIZE; i >= 0; i--) {
        if (tree[i] == 'a' || tree[i] == 'b' || tree[i] == 'c' || tree[i] == '0' || tree[i] == '1') {
            parent = (i - 1) / 5;
            newTree[parent] = tree[i];
            newTree[i] = ' ';
        } else if (tree[i] == '+' || tree[i] == '-' || tree[i] == '*' || tree[i] == '/') {
            parent = (i - 1) / 5;
            ancestor = (parent - 1) / 5;
            newTree[parent] = ' ';
            newTree[ancestor] = tree[i];
            newTree[i] = ' ';
        }
    }
}

void postOrderTraversal(char *tree, int index) {
    if (tree[index] != ' ') {
        postOrderTraversal(tree, 5 * index + 2);
        postOrderTraversal(tree, 5 * index + 4);
        reversePolish[topPolish++] = tree[index];
    }
}

void generatePcode() {
    for (int i = 0; reversePolish[i] != '\0'; i++) {
        switch (reversePolish[i]) {
            case 'a':
                printf(" LOD 0 3");
                break;
            case 'b':
                printf(" LOD 0 4");
                break;
            case 'c':
                printf(" LOD 0 5");
                break;
            case '1':
                printf(" LIT 0 1");
                break;
            case '+':
                printf(" OPR 0 2");
                break;
            case '-':
                printf(" OPR 0 3");
                break;
            case '*':
                printf(" OPR 0 4");
                break;
            case '/':
                printf(" OPR 0 5");
                break;
            default:
                break;
        }
        printf("\n");
    }
    printf(" OPR 0 0"); // End of P-code
}

void printTree(char *tree, int index, int level) {
    if (index < MAX_SIZE && tree[index] != ' ') {
        for (int i = 0; i < level; i++)
            printf("   ");

        printf("|-- %c\n", tree[index]);

        printTree(tree, 5 * index + 1, level + 1);
        printTree(tree, 5 * index + 2, level + 1);
        printTree(tree, 5 * index + 3, level + 1);
        printTree(tree, 5 * index + 4, level + 1);
        printTree(tree, 5 * index + 5, level + 1);
    }
}

int wordSize(char *word) {
    int size = -1;
    for (int i = 0; word[i] != '\0'; i++)
        size++;

    return size;
}

void displayHeader() {
    int wordLength = wordSize(input);

    printf("Parsing Table:\n\n");
    printf("  i ||  q  ||");

    for (int i = 0; i < wordLength; i++) {
        if (i == wordLength / 2)
            printf(".w");
        
        printf(" ");
    }

    printf("  ||  t  ||  p  || Stack\n");
    for (int i = 0; i < wordLength + 40; i++)
        printf("=");
}

void pushSymbol(char *value) {
    int size = wordSize(value);

    for (int i = 0; value[i] != '\0'; i++) {
        symbolStack[topSymbols] = value[size - i];
        topSymbols++;
    }
}

void popSymbol() {
    topSymbols--;
}

char readTopSymbol() {
    return symbolStack[topSymbols - 1];
}

char getNextSymbol() {
    nextSymbol++;
    char token = input[nextSymbol];
    return token;
}

void displayError(int type) {
    if (type == 1) {
        printf("\n\n\tError: unrecognized word\n");
    }
}

void displayState(int i, char *state, char *transition, char *symbol) {
    printf("\n");
    printf("%3d || ", i);
    printf("%3s || ", state);

    for (int j = 0; input[j] != '\0'; j++) {
        if (j == nextSymbol) {
            printf(".");
        }
        printf("%c", input[j]);
    }

    if (input[nextSymbol] == '\0')
        printf(".");

    printf(" || ");
    printf("%3s || ", transition);
    printf("%3s || ", symbol);

    if (topSymbols == 0)
        printf("None");
    else
        for (int j = topSymbols - 1; j >= 0; j--)
            printf("%c", symbolStack[j]);
}

int main() {
    char currentToken;
    int count = 0;
    FILE *inputFile;
    char binaryTree[MAX_SIZE];

    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error reading file\n");
        return 0;
    }

    fscanf(inputFile, "%s", input);
    fclose(inputFile);

    initializeTree(tree);
    displayHeader();

    // Initial state
    state0:
        displayState(count, "q0", "t0", "-");
        currentToken = input[topSymbols];
        pushSymbol("E");
        addToTree(0);
        goto state1;

    state1:
        count++;
        if (currentToken == '(' && readTopSymbol() == 'E') {
            displayState(count, "q1", "t1", "p1");
            popSymbol();
            pushSymbol("(EXE)");
            addToTree(1);
            goto state1;
        } else if (currentToken == '0' && readTopSymbol() == 'E') {
            displayState(count, "q1", "t2", "p2");
            popSymbol();
            pushSymbol("0");
            addToTree(2);
            goto state1;
        } else if (currentToken == '1' && readTopSymbol() == 'E') {
            displayState(count, "q1", "t3", "p3");
            popSymbol();
            pushSymbol("1");
            addToTree(3);
            goto state1;
        } else if (currentToken == 'a' && readTopSymbol() == 'E') {
            displayState(count, "q1", "t4", "p4");
            popSymbol();
            pushSymbol("a");
            addToTree(4);
            goto state1;
        } else if (currentToken == 'b' && readTopSymbol() == 'E') {
            displayState(count, "q1", "t5", "p5");
            popSymbol();
            pushSymbol("b");
            addToTree(5);
            goto state1;
        } else if (currentToken == 'c' && readTopSymbol() == 'E') {
            displayState(count, "q1", "t6", "p6");
            popSymbol();
            pushSymbol("c");
            addToTree(6);
            goto state1;
        } else if ((currentToken == '+' || currentToken == '-' || currentToken == '*' || currentToken == '/') && readTopSymbol() == 'X') {
            switch (currentToken) {
                case '+':
                    displayState(count, "q1", "t7", "p7");
                    break;
                case '-':
                    displayState(count, "q1", "t8", "p8");
                    break;
                case '*':
                    displayState(count, "q1", "t9", "p9");
                    break;
                case '/':
                    displayState(count, "q1", "t10", "p10");
                    break;
            }
            popSymbol();
            pushSymbol(&currentToken);
            addToTree(7 + currentToken - '+');
            goto state1;
        } else if ((currentToken == 'a' || currentToken == 'b' || currentToken == 'c' || currentToken == '0' || currentToken == '1') && readTopSymbol() == currentToken) {
            switch (currentToken) {
                case 'a':
                    displayState(count, "q1", "t11", "-");
                    break;
                case 'b':
                    displayState(count, "q1", "t12", "-");
                    break;
                case 'c':
                    displayState(count, "q1", "t13", "-");
                    break;
                case '0':
                    displayState(count, "q1", "t14", "-");
                    break;
                case '1':
                    displayState(count, "q1", "t15", "-");
                    break;
            }
            popSymbol();
            currentToken = getNextSymbol();
            goto state1;
        } else if ((currentToken == '(' || currentToken == ')' || currentToken == '+' || currentToken == '-' || currentToken == '*' || currentToken == '/') && readTopSymbol() == currentToken) {
            switch (currentToken) {
                case '(':
                    displayState(count, "q1", "t16", "-");
                    break;
                case ')':
                    displayState(count, "q1", "t17", "-");
                    break;
                case '+':
                    displayState(count, "q1", "t18", "-");
                    break;
                case '-':
                    displayState(count, "q1", "t19", "-");
                    break;
                case '*':
                    displayState(count, "q1", "t20", "-");
                    break;
                case '/':
                    displayState(count, "q1", "t21", "-");
                    break;
            }
            popSymbol();
            currentToken = getNextSymbol();
            goto state1;
        } else if (currentToken == '\0' && topSymbols == 0) {
            displayState(count, "q1", "-", "-");
            goto end;
        } else {
            displayError(1);
            return 0;
        }

    end:
        printf("\n\nN-ary Tree:\n");
        printTree(tree, 0, 0);
        convertToBinaryTree(binaryTree);
        postOrderTraversal(binaryTree, 0);
        reversePolish[topPolish] = '\0';
        printf("\n\nReverse Polish P-code:\n %s\n\n", reversePolish);
        generatePcode();

    return 0;
}
