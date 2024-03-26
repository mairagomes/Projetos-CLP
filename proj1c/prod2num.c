// p-code.cpp :

// Aluna: Maira Gomes Santos 

#include <stdio.h>

#define levmax 3
#define amax 2047

enum fct {LIT, OPR, LOD, STO, CAL, INT, JMP, JPC, MUL};

typedef struct tinstruction {
    enum   fct    f;
    int    l; // l: 0..levmax; // Level buffer
    int    a; // a: 0..amax;   // Address buffer
} instruction;

instruction code[2048];

#define stacksize 5012

int p, // program-register
    b, // base-register
    t; // topstack-register

instruction i;
int s[stacksize];

int base(int l) {
    int b1;
    b1 = b;
    while (l > 0) {
        b1 = s[b1];
        l  = l - 1;
    }
    return b1;
}

int odd(int x) { 
    return ((x % 2) == 1); 
}

void pcodevhw() {
    printf("\n start pl/0");
    printf("\n t   b   p     f   l   a                 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14");
    printf("\n === === ===   === === ===             === === === === === === === === === === === === === === ===");
    t = -1;
    b = 0;
    p = 0;
    s[1] = 0; 
    s[2] = 0; 
    s[3] = 0;

    do {
        i = code[p]; 
        printf("\n %3d %3d %3d   ", t, b, p);
        p = p + 1;

        switch  (i.f) { 
            case LIT: { 
                t = t + 1; 
                s[t] = i.a; 
                printf("LIT %3d %3d", i.l, i.a); 
            } break;
            case OPR: {
                printf("OPR %3d %3d", i.l, i.a);
                switch (i.a) {
                    case 0: { 
                        t = b - 1; 
                        p = s[t + 3]; 
                        b = s[t + 2];
                    } break;
                    // Adicionando apenas a lógica de multiplicação
                    case 4: { 
                        t = t - 1; 
                        s[t] = s[t] * s[t + 1];
                    } break;
                } 
            } break;
            case LOD: { 
                printf("LOD %3d %3d", i.l, i.a);
                t = t + 1; 
                s[t] = s[base(i.l) + i.a];
            } break;
            case STO: { 
                printf("STO %3d %3d", i.l, i.a);
                s[base(i.l) + i.a] = s[t]; 
                t = t - 1;
            } break;
            case CAL: { 
                printf("CAL %3d %3d", i.l, i.a);
                s[t + 1] = base(i.l); 
                s[t + 2] = b; 
                s[t + 3] = p;
                b = t + 1; 
                p = i.a;
            } break;
            case INT: 
                t = t + i.a;
                printf("INT %3d %3d", i.l, i.a);
                break;
            case JMP: 
                p = i.a;    
                printf("JMP %3d %3d", i.l, i.a);
                break;
            case JPC: 
                if (s[t] == 1) { 
                    p = i.a; 
                }  
                t = t - 1; 
                printf("JPC %3d %3d", i.l, i.a);
                break;
            case MUL: { 
                t = t - 1; 
                s[t] = s[t] * s[t + 1];
                printf("MUL %3d %3d", i.l, i.a);
            } break;
        } 

        printf("      s[] : ");
        for (int h = 0; h <= t; h++) { 
            printf(" %3d", s[h]); 
        }
    } while (p != 0);

    printf("\n === === ===   === === ===             === === === === === === === === === === === === === === ==="); 
    printf("\n t   b   p     f   l   a                 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14");
    printf("\n end pl/0");
}

int main() {
    // Aqui vc preenche as instrucoes no vetor code
    code[0].f = INT; code[0].l = 0; code[0].a = 3;
    code[1].f = CAL; code[1].l = 0; code[1].a = 3;
    code[2].f = OPR; code[2].l = 0; code[2].a = 0; // RETURN
    code[3].f = INT; code[3].l = 0; code[3].a = 5;
    code[4].f = LIT; code[4].l = 0; code[4].a = 4; // PUSH (4)
    code[5].f = LIT; code[5].l = 0; code[5].a = 5; // PUSH (5)
    code[6].f = MUL; code[6].l = 0; code[6].a = 0; // MULTIPLICAÇÃO
    code[7].f = OPR; code[7].l = 0; code[7].a = 0; // RETURN

    // Aqui vc chama a P-code machine para interpretar essas instrucoes
    pcodevhw();
    return 0;
}
