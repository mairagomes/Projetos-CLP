// p-code.cpp : 
//
// C conventions
// 0 == FALSE

//Aluna: Maira Gomes Santos
#include <stdio.h>

#define levmax 3
#define amax 2047

enum fct {LIT, OPR, LOD, STO, CAL, INT, JMP, JPC};

typedef struct tinstruction {
     enum fct    f;
     int    l; // l: 0..levmax; // Level buffer
     int    a; // a: 0..amax;   // Address buffer
}instruction;

instruction code[2048];

//procedure interpret;
// const stacksize = 500;

#define stacksize 5012

 // p, b, t: integer; {program-, base-, topstack-registers}
 int p, // program-register
     b, // base-register
     t; // topstack-register

instruction i;            //: instruction; {instruction register}
int         s[stacksize]; //: array [1..stacksize] of integer; {datastore}

int base(int l){ //l: integer)
 int b1; //

 b1 = b; // {find base l levels down}
 while (l > 0) {
    b1 = s[b1];
    l  = l - 1;
 }
 return b1;
}//end-int-base

// Determina se seu argumento é impar
int odd(int x){ return (  ((x%2)==1) ); }

void pcodevhw(){ // begin 
 printf("\n start pl/0");
 printf("\n t   b   p     f   l   a                 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14");
 printf("\n === === ===   === === ===             === === === === === === === === === === === === === === ===");
 t = -1; // topstack-register
 b = 0; // base-register
 p = 0; // program-register

 // OBS: s[0] must not be used
 s[1] = 0; 
 s[2] = 0; 
 s[3] = 0;

 do {
  i = code[p]; 
  //printf("\n %3d %3d %3d - %3d %3d %3d", t, b, p, i.f, i.l, i.a);
  printf("\n %3d %3d %3d   ", t, b, p);
  p = p + 1;
 // switch case i.f-BEGIN
  switch  (i.f) { // with i do case f of
    case LIT : { t = t + 1; s[t] = i.a; printf("LIT %3d %3d", i.l, i.a); } break;
    case OPR :
               printf("OPR %3d %3d", i.l, i.a);
//             switch case i.a-BEGIN
               switch (i.a) { // case a of {operator}
                 case  0: { // return
                            t = b - 1; 
                            p = s[t + 3]; 
                            b = s[t + 2];
                          }
                          break;

                 case  1: { //
                            s[t] = -s[t];
                          }
                          break;

                 case  2: { //  ADD     : PUSH( POP()+POP() )
                            t    = t - 1; 
                            s[t] = s[t] + s[t + 1];
                          }
                          break;

                 case  3: { // SUBSTRACT: PUSH( POP()-POP() )
                            t    = t - 1; 
                            s[t] = s[t] - s[t + 1];
                          }
                          break;

                 case  4: { // MULTIPLY: PUSH( POP()*POP() )
                            t    = t - 1; 
                            s[t] = s[t] * s[t + 1];
                          }
                          break;

                 case  5: { // DIVIDE  : PUSH( POP()/POP() )
                            t    = t - 1; 
                            s[t] = s[t] / s[t + 1];
                          }
                          break;

                 case  6: { // 
                            s[t] = odd(s[t]); //s[t] = ord(odd(s[t]));
                          }
                          break;

                 case  8: { // EQUAL
                            t    = t - 1; 
                            s[t] = (s[t] == s[t + 1]);
                          }
                          break;

                 case  9: { // NOT.EQUAL
                            t    = t - 1; 
                            s[t] = (s[t] != s[t + 1]);
                          }
                          break;

                 case 10: { // LESS THAN
                            t    = t - 1; 
                            s[t] = (s[t] < s[t + 1]);
                          }
                          break;

                 case 11: { // GREATER EQUAL THAN
                            t    = t - 1; 
                            s[t] = (s[t] >= s[t + 1]);
                          }
                          break;

                 case 12: { // GREATER THAN
                            t = t - 1; 
                            s[t] = (s[t] > s[t + 1]);
                          }
                          break;

                 case 13: { // LESS EQUAL THAN
                            t    = t - 1; 
                            s[t] = (s[t] <= s[t + 1]);
                          }
                          break;
               } // end;
//         switch case i.a-END
           break;

   case LOD : { // LOAD
                printf("LOD %3d %3d", i.l, i.a);
                t    = t + 1; 
                s[t] = s[base(i.l) + i.a];
              }
              break;

   case STO : { // STORE
                printf("STO %3d %3d", i.l, i.a);
                s[base(i.l)+i.a] = s[t]; 
                t            = t - 1;
              }
              break;

   case CAL :
              { // {generate new block mark}
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
   case JPC : if (s[t] == 1) { p = i.a; }  t = t - 1; printf("JPC %3d %3d", i.l, i.a); break;
  } // end {with, case}
  // switch case i.f-END

  // print stack
  printf("      s[] : ");
  for (int h=0; h<=t; h++) { printf(" %3d", s[h]); }
 } while ( p != 0 );

 printf("\n === === ===   === === ===             === === === === === === === === === === === === === === ==="); 
 printf("\n t   b   p     f   l   a                 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14");
 printf("\n end pl/0");
}//end-void-pcmachine() {interpret};

int main(){

  // Aqui vc preenche as instrucoes no vetor code
    //main
    code[ 0].f = INT; code[ 0].l = 0; code[ 0].a = 4;
    code[ 1].f = CAL; code[ 1].l = 0; code[ 1].a = 5; // chama função
    code[ 2].f = LOD; code[ 2].l = 0; code[ 2].a = 9; // carrega resultado
    code[ 3].f = STO; code[ 3].l = 0; code[ 3].a = 3; // coloca resultado no topo da pilha
    code[ 4].f = OPR; code[ 4].l = 0; code[ 4].a = 0;

    //função fib iterativo
    code[ 5].f = INT; code[ 5].l = 0; code[ 5].a = 8; 
    code[ 6].f = LIT; code[ 6].l = 0; code[ 6].a = 0; // aux1
    code[ 7].f = STO; code[ 7].l = 0; code[ 7].a = 3;
    code[ 8].f = LIT; code[ 8].l = 0; code[ 8].a = 1; // fib
    code[ 9].f = STO; code[ 9].l = 0; code[ 9].a = 4;  
    code[ 10].f = LIT; code[ 10].l = 0; code[ 10].a = 1; // cont
    code[ 11].f = STO; code[ 11].l = 0; code[ 11].a = 5; 
    code[ 12].f = LIT; code[ 12].l = 0; code[ 12].a = 0; // aux2
    code[ 13].f = STO; code[ 13].l = 0; code[ 13].a = 6; 
    code[ 14].f = LIT; code[ 14].l = 0; code[ 14].a = 5; // máx
    code[ 15].f = STO; code[ 15].l = 0; code[ 15].a = 7; 
    code[ 16].f = LOD; code[ 16].l = 0; code[ 16].a = 3; // inicio loop - carrega aux1
    code[ 17].f = LOD; code[ 17].l = 0; code[ 17].a = 4; // carrega fib
    code[ 18].f = OPR; code[ 18].l = 0; code[ 18].a = 2; // aux1+fib
    code[ 19].f = STO; code[ 19].l = 0; code[ 19].a = 6; // aux2 = aux1+fib
    code[ 20].f = LOD; code[ 20].l = 0; code[ 20].a = 4; // carrega fib
    code[ 21].f = STO; code[ 21].l = 0; code[ 21].a = 3; // aux1 = fib
    code[ 22].f = LOD; code[ 22].l = 0; code[ 22].a = 6; // carrega aux2
    code[ 23].f = STO; code[ 23].l = 0; code[ 23].a = 4; // fib = aux2
    code[ 24].f = LOD; code[ 24].l = 0; code[ 24].a = 5; // carrega cont
    code[ 25].f = LOD; code[ 25].l = 0; code[ 25].a = 7; // carrega máx 
    code[ 26].f = OPR; code[ 26].l = 0; code[ 26].a = 11; // verifica se cont>máx
    code[ 27].f = JPC; code[ 27].l = 0; code[ 27].a = 33; // fim
    code[ 28].f = LOD; code[ 28].l = 0; code[ 28].a = 5; // carrega cont
    code[ 29].f = LIT; code[ 29].l = 0; code[ 29].a = 1; // 1
    code[ 30].f = OPR; code[ 30].l = 0; code[ 30].a = 2; // cont+1
    code[ 31].f = STO; code[ 31].l = 0; code[ 31].a = 5; 
    code[ 32].f = JMP; code[ 32].l = 0; code[ 32].a = 16; // encerra loop
    code[ 33].f = OPR; code[ 33].l = 0; code[ 33].a = 0; 

  // Aqui vc chama a P-code machine para interpretar essas instrucoes
  pcodevhw();
  return 0;
}
