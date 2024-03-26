
#include <stdio.h>

#define levmax 3
#define amax 2047

enum fct {LIT, OPR, LOD, STO, CAL, INT, JMP, JPC};

typedef struct tinstruction {
     enum   fct    f;
     int    l; 
     int    a; 
}instruction;

instruction code[2048];


#define stacksize 5012

 
 int p,
     b, 
     t; 
 
instruction i;            
int         s[stacksize]; 

int base(int l){ 
 int b1; 

 b1 = b; 
 while (l > 0) {
    b1 = s[b1];
    l  = l - 1;
 }
 return b1;
}


int odd(int x){ return (  ((x%2)==1) ); }

void pcodevhw(){ // begin 
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
         
                 case  1: { 
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
   case JPC : if (s[t] == 1) { p = i.a; }  t = t - 1; printf("JPC %3d %3d", i.l, i.a); break;
  } 
  printf("      s[] : ");
  for (int h=0; h<=t; h++) { printf(" %3d", s[h]); }
 } while ( p != 0 );

 printf("\n === === ===   === === ===             === === === === === === === === === === === === === === ==="); 
 printf("\n t   b   p     f   l   a                 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14");
 printf("\n end pl/0");
}

int main(){

	// preenche as instrucoes no vetor code
    code[ 0].f = INT; code[ 0].l = 0; code[ 0].a = 6;
    code[ 1].f = LIT; code[ 1].l = 0; code[ 1].a = 0; //soma
    code[ 2].f = STO; code[ 2].l = 0; code[ 2].a = 3;
    code[ 3].f = LIT; code[ 3].l = 0; code[ 3].a = 0; //cont
    code[ 4].f = STO; code[ 4].l = 0; code[ 4].a = 4;
    code[ 5].f = LIT; code[ 5].l = 0; code[ 5].a = 101; //limite
//obs.: o limite é 101 porque a condição para o JPC é s[t]=1, então para que o loop funcione corretamente o limite tem que ser 11 para que sejam realizadas as 100 iterações.
    code[ 6].f = STO; code[ 6].l = 0; code[ 6].a = 5;
    code[ 7].f = LOD; code[ 7].l = 0; code[ 7].a = 3; //carrega soma
    code[ 8].f = LOD; code[ 8].l = 0; code[ 8].a = 4; //carrega cont
    code[ 9].f = OPR; code[ 9].l = 0; code[ 9].a = 2; //soma+cont
    code[ 10].f = STO; code[ 10].l = 0; code[ 10].a = 3;
    code[ 11].f = LOD; code[ 11].l = 0; code[ 11].a = 5; //carrega limite
    code[ 12].f = LOD; code[ 12].l = 0; code[ 12].a = 4; //carrega cont
    code[ 13].f = OPR; code[ 13].l = 0; code[ 13].a = 3; //limite-cont
    code[ 14].f = JPC; code[ 14].l = 0; code[ 14].a = 20; //vai para o final
    code[ 15].f = LOD; code[ 15].l = 0; code[ 15].a = 4;  //carrega cont
    code[ 16].f = LIT; code[ 16].l = 0; code[ 16].a = 1; //1
    code[ 17].f = OPR; code[ 17].l = 0; code[ 17].a = 2; //cont+1
    code[ 18].f = STO; code[ 18].l = 0; code[ 18].a = 4;
    code[ 19].f = JMP; code[ 19].l = 0; code[ 19].a = 7; //vai para 7
    code[ 20].f = OPR; code[ 20].l = 0; code[ 20].a = 0; 

	//chama a P-code machine para interpretar essas instrucoes
	pcodevhw();
	return 0;
}
