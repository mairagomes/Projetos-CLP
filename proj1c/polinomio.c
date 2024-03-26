
// Aluna : Maira Gomes

#include <stdio.h>

#define levmax 3
#define amax 2047

#define A 1
#define B 2
#define C 3
#define X 4

enum fct {LIT, OPR, LOD, STO, CAL, INT, JMP, JPC};

typedef struct tinstruction {
     enum fct    f;
     int    l; // l: 0..levmax; // Level buffer
     int    a; // a: 0..amax;   // Address buffer
}instruction;

instruction code[2048];

#define stacksize 5012

 
 int p, 
     b, 
     t; 

instruction i;         
int s[stacksize]; 

int base(int l){ //l: integer)
 int b1; //

 b1 = b; // {find base l levels down}
 while (l > 0) {
    b1 = s[b1];
    l  = l - 1;
 }
 return b1;
}


int odd(int x){
  return (  ((x%2)==1) );
}

void pcodevhw(){ // begin
    printf("\n start pl/0");
    printf("\n p   b   t     f   l   a                 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14");
    printf("\n === === ===   === === ===             === === === === === === === === === === === === === === ===");
 t = -1; // topstack-register
 b = 0;  // base-register
 p = 0;  // program-register
 s[1] = 0;
 s[2] = 0;
 s[3] = 0;

 do {
  i = code[p];
  
  printf("\n %3d %3d %3d   ", p, b, t);
  p = p + 1;
  switch  (i.f) { 
    case LIT : { t = t + 1; s[t] = i.a; printf("LIT %3d %3d", i.l, i.a); } break;
    case OPR :
               printf("OPR %3d %3d", i.l, i.a);

               switch (i.a) { 
                 case  0: { 
                            t = b - 1;
                            p = s[t + 3];
                            b = s[t + 2];
                          }
                          break;

                 case  1: { //
                            s[t] = -s[t];
                          }
                          break;

                 case  2: { 
                            t    = t - 1;
                            s[t] = s[t] + s[t + 1];
                          }
                          break;

                 case  3: { 
                            t    = t - 1;
                            s[t] = s[t] - s[t + 1];
                          }
                          break;

                 case  4: { 
                            t    = t - 1;
                            s[t] = s[t] * s[t + 1];
                          }
                          break;

                 case  5: { 
                            t    = t - 1;
                            s[t] = s[t] / s[t + 1];
                          }
                          break;

                 case  6: { 
                            s[t] = odd(s[t]); 
                          }
                          break;

                 case  8: { 
                            t    = t - 1;
                            s[t] = (s[t] == s[t + 1]);
                          }
                          break;

                 case  9: { 
                            t    = t - 1;
                            s[t] = (s[t] != s[t + 1]);
                          }
                          break;

                 case 10: { 
                            t    = t - 1;
                            s[t] = (s[t] < s[t + 1]);
                          }
                          break;

                 case 11: { 
                            t    = t - 1;
                            s[t] = (s[t] >= s[t + 1]);
                          }
                          break;

                 case 12: { 
                            t = t - 1;
                            s[t] = (s[t] > s[t + 1]);
                          }
                          break;

                 case 13: { 
                            t    = t - 1;
                            s[t] = (s[t] <= s[t + 1]);
                          }
                          break;
               } 
           break;

   case LOD : {
                printf("LOD %3d %3d", i.l, i.a);
                t    = t + 1;
                s[t] = s[base(i.l) + i.a];
              }
              break;

   case STO : { 
                printf("STO %3d %3d", i.l, i.a);
                s[base(i.l)+i.a] = s[t];
                t            = t - 1;
              }
              break;

   case CAL :
              { 
                printf("CAL %3d %3d", i.l, i.a);
                s[t + 1] = base(i.l);
                s[t + 2] = b;
                s[t + 3] = p;
                b        = t + 1;
                p        = i.a;
              }
              break;

   case INT : t = t + i.a;printf("INT %3d %3d", i.l, i.a); break;
   case JMP : p = i.a;    printf("JMP %3d %3d", i.l, i.a); break;
   case JPC : if (s[t] != 0) { p = i.a; }  t = t - 1; printf("JPC %3d %3d", i.l, i.a); break;
  } 
  printf("      s[] : ");
  for (int h=0; h<=t; h++) { printf(" %3d", s[h]); }
 } while ( p != 0 );

 printf("\n === === ===   === === ===             === === === === === === === === === === === === === === ===");
 printf("\n p   b   t     f   l   a                 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14");
 printf("\n end pl/0");
}

int main(){

  // Aqui vc preenche as instrucoes no vetor code
   code[ 0 ].f = INT; code[  0 ].l = 0; code[  0 ].a = 9;
   code[ 1 ].f = LIT; code[  1 ].l = 0; code[  1 ].a = A;  // A = 1
   code[ 2 ].f = STO; code[  2 ].l = 0; code[  2 ].a = 3;
   code[ 3 ].f = LIT; code[  3 ].l = 0; code[  3 ].a = B;  // B = 2
   code[ 4 ].f = STO; code[  4 ].l = 0; code[  4 ].a = 4;
   code[ 5 ].f = LIT; code[  5 ].l = 0; code[  5 ].a = C;  // C = 3
   code[ 6 ].f = STO; code[  6 ].l = 0; code[  6 ].a = 5;
   code[ 7 ].f = LIT; code[  7 ].l = 0; code[  7 ].a = X;  // X = 4 
   code[ 8 ].f = STO; code[  8 ].l = 0; code[  8 ].a = 6;

   // MULTIPLICACAO X^2
   code[ 9 ].f = LOD; code[  9 ].l = 0; code[  9 ].a = 6;      // topo = 4
   code[ 10 ].f = STO; code[ 10 ].l = 0; code[ 10 ].a = 12;    // armazena 4 na posicao 12
   code[ 11 ].f = LOD; code[ 11 ].l = 0; code[ 11 ].a = 6;     // topo = 4
   code[ 12 ].f = STO; code[ 12 ].l = 0; code[ 12 ].a = 13;    // armazena 4 na posicao 13
   code[ 13 ].f = CAL; code[ 13 ].l = 0; code[ 13 ].a = 100;    // chama a funcao multiplicacao (4 * 4)

   // MULTIPLICACAO A*X^2
   code[ 14 ].f = LOD; code[ 14 ].l = 0; code[ 14 ].a = 7;     // topo = 16  --> X^2
   code[ 15 ].f = STO; code[ 15 ].l = 0; code[ 15 ].a = 12;    // armazena 16 na posicao 12
   code[ 16 ].f = LOD; code[ 16 ].l = 0; code[ 16 ].a = 3;     // topo = 1
   code[ 17 ].f = STO; code[ 17 ].l = 0; code[ 17 ].a = 13;    // armazena 1 na posicao 13
   code[ 18 ].f = CAL; code[ 18 ].l = 0; code[ 18 ].a = 100;    // chama a funcao multiplicacao (16 * 1)
   code[ 19 ].f = LOD; code[ 19 ].l = 0; code[ 19 ].a = 7;    // topo = 16 --> A*X^2
   code[ 20 ].f = STO; code[ 20 ].l = 0; code[ 20 ].a = 8;    // armazena 16 na posicao 8


   // MULTIPLICACAO B*X
   code[ 21 ].f = LOD; code[ 21 ].l = 0; code[ 21 ].a = 6;     // topo = 4  --> X
   code[ 22 ].f = STO; code[ 22 ].l = 0; code[ 22 ].a = 12;    // armazena 4 na posicao 12
   code[ 23 ].f = LOD; code[ 23 ].l = 0; code[ 23 ].a = 4;     // topo = 2
   code[ 24 ].f = STO; code[ 24 ].l = 0; code[ 24 ].a = 13;    // armazena 2 na posicao 13
   code[ 25 ].f = CAL; code[ 25 ].l = 0; code[ 25 ].a = 100;    // chama a funcao multiplicacao (4 * 2)

   // SOMA ax^2 + bx
   code[ 26 ].f = LOD; code[ 26 ].l = 0; code[ 26 ].a = 8;     // topo = 16
   code[ 27 ].f = STO; code[ 27 ].l = 0; code[ 27 ].a = 12;    // armazena 8 na posicao 12
   code[ 28 ].f = LOD; code[ 28 ].l = 0; code[ 28 ].a = 7;     // topo = 8
   code[ 29 ].f = STO; code[ 29 ].l = 0; code[ 29 ].a = 13;    // armazena 7 na posicao 13
   code[ 30 ].f = CAL; code[ 30 ].l = 0; code[ 30 ].a = 200;    // chama a funcao soma (16 + 8)

   // SOMA ax^2 + bx + c
   code[ 31 ].f = LOD; code[ 31 ].l = 0; code[ 31 ].a = 8;     // topo = 24
   code[ 32 ].f = STO; code[ 32 ].l = 0; code[ 32 ].a = 12;    // armazena 8 na posicao 12
   code[ 33 ].f = LOD; code[ 33 ].l = 0; code[ 33 ].a = 5;     // topo = 3
   code[ 34 ].f = STO; code[ 34 ].l = 0; code[ 34 ].a = 13;    // armazena 3 na posicao 13
   code[ 35 ].f = CAL; code[ 35 ].l = 0; code[ 35 ].a = 200;    // chama a funcao soma (24 + 3)
   code[ 36 ].f = OPR; code[ 36 ].l = 0; code[ 36 ].a = 0;     // finaliza Main


   // FUNCAO MULTIPLICACAO
   code[ 100 ].f = INT; code[ 100 ].l = 0; code[ 100 ].a = 6;
   code[ 101 ].f = LOD; code[ 101 ].l = 0; code[ 101 ].a = 3;     // topo = posicao 3
   code[ 102 ].f = LOD; code[ 102 ].l = 0; code[ 102 ].a = 4;     // topo = posicao 4
   code[ 103 ].f = OPR; code[ 103 ].l = 0; code[ 103 ].a = 4;     // N * M
   code[ 104 ].f = STO; code[ 104 ].l = 1; code[ 104 ].a = 7;     // salva (N * M) na posicao 7 da pilha inicial
   code[ 105 ].f = OPR; code[ 105 ].l = 0; code[ 105 ].a = 0;     // finaliza a funcao

   // FUNCAO SOMA
   code[ 200 ].f = INT; code[ 200 ].l = 0; code[ 200 ].a = 6;
   code[ 201 ].f = LOD; code[ 201 ].l = 0; code[ 201 ].a = 3;     // topo = posicao 3
   code[ 202 ].f = LOD; code[ 202 ].l = 0; code[ 202 ].a = 4;     // topo = posicao 4
   code[ 203 ].f = OPR; code[ 203 ].l = 0; code[ 203 ].a = 2;     // N + M
   code[ 204 ].f = STO; code[ 204 ].l = 1; code[ 204 ].a = 8;     // salva (N + M) na posicao 8 da pilha inicial
   code[ 205 ].f = OPR; code[ 205 ].l = 0; code[ 205 ].a = 0;     // finaliza a funcao


  // Aqui vc chama a P-code machine para interpretar essas instrucoes
  pcodevhw();
  return 0;
}
