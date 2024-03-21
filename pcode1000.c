#include <stdio.h>
#include<locale.h>

#define amax 2047
#define levmax 3       
#define cxmax 1000
#define stacksize 5012


enum fct{LIT, OPR, LOD, STO, CAL, INT, JMP, JPC};
typedef struct {
    enum fct f; 
    long long int l;      
    long long int a;
} instruction;

instruction code[cxmax];
long long int s[stacksize];

int odd(int l) {
    int b1 = 1; 

    while (l > 0) {
        b1 = code[b1].a;
        l--;
    }
    return b1;
}

void pcodevhw() {
    instruction i;
    int p = 0, b = 1, t = 0;

    s[1] = 0;
    s[2] = 0;
    s[3] = 0;

    
    int k = 0;
    code[k].f = INT; code[k].l = 0; code[k].a = 6; k++;		
    code[k].f = LIT; code[k].l = 0; code[k].a = 2; k++;			
    code[k].f = STO; code[k].l = 0; code[k].a = 3; k++;		
    code[k].f = LIT; code[k].l = 0; code[k].a = 1000; k++;	
    code[k].f = STO; code[k].l = 0; code[k].a = 4; k++;		
    code[k].f = LIT; code[k].l = 0; code[k].a = 1; k++;	
    code[k].f = STO; code[k].l = 0; code[k].a = 5; k++;		
    code[k].f = LOD; code[k].l = 0; code[k].a = 3; k++;	
    code[k].f = LOD; code[k].l = 0; code[k].a = 3; k++;	
    code[k].f = LOD; code[k].l = 0; code[k].a = 3; k++;  
    code[k].f = OPR; code[k].l = 0; code[k].a = 4; k++;   
    code[k].f = OPR; code[k].l = 0; code[k].a = 4; k++;		
    code[k].f = LOD; code[k].l = 0; code[k].a = 5; k++;		
    code[k].f = OPR; code[k].l = 0; code[k].a = 2; k++;			
    code[k].f = STO; code[k].l = 0; code[k].a = 5; k++;		
    code[k].f = LOD; code[k].l = 0; code[k].a = 3; k++;			
    code[k].f = LOD; code[k].l = 0; code[k].a = 4; k++;			
    code[k].f = OPR; code[k].l = 0; code[k].a = 10; k++;		
    code[k].f = JPC; code[k].l = 0; code[k].a = 23; k++;		
    code[k].f = LOD; code[k].l = 0; code[k].a = 3; k++;			
    code[k].f = OPR; code[k].l = 0; code[k].a = 2; k++;			
    code[k].f = STO; code[k].l = 0; code[k].a = 3; k++;		
    code[k].f = JMP; code[k].l = 0; code[k].a = 7; k++;			
    code[k].f = OPR; code[k].l = 0; code[k].a = 0;				

   printf("\n start pl/0");
   printf("\n t     b    p  ");
   printf("\n===   ===  ===   ");

    do {
        i = code[p++];
        printf("\n%3d  %3d  %3d  ", p, b, t);
        switch (i.f) {
            case LIT: 
                t++;
                s[t] = i.a;
                break;
            case OPR: 
                switch(i.a){
                    case 0: 
                        t = b - 1;
                        p = s[t + 3];
                        b = s[t + 2];
                        break;
                    case 1:
                        s[t] = -s[t];
                        break;
                    case 2: 
                        t--;
                        s[t] = s[t] + s[t + 1];
                        
                        break;
                    case 3: 
                        s[t] = s[t] - s[t + 1];
                        break;
                    case 4:
                        t--;
                        s[t] = s[t] * s[t + 1];
                        break;
                    case 5: 
                        t--;
                        s[t] = s[t] / s[t + 1];
                        break;
                    case 6: 
                        s[t] = (s[t]) % 2;
                        break;
                    case 8: 
                        t--;
                        s[t] = (s[t] == s[t + 1]);
                        break;
                    case 9: 
                        t--;
                        s[t] = (s[t] != s[t + 1]);
                        break;
                    case 10:
                        t--;
                        s[t] = (s[t] < s[t + 1]);
                        break;
                    case 11:
                        t--;
                        s[t] = (s[t] <= s[t + 1]);
                        break;
                    case 12: 
                        t--;
                        s[t] = (s[t] > s[t + 1]);
                        break;
                    case 13: 
                        t--;
                        s[t] = (s[t] >= s[t + 1]);
                        break;
                }
                break;
            case LOD:
                t++;
                s[t] = s[odd(i.l) + i.a];
                break;
            case STO:
                s[odd(i.l) + i.a] = s[t];
                t--;
                break;
            case CAL:
                s[t + 1] = odd(i.l);
                s[t + 2] = b;
                s[t + 3] = p;
                b = t + 1;
                p = i.a;
               
                break;
            case INT:
                t += i.a;
                
                break;
            case JMP:
                p = i.a;
                
                break;
            case JPC:
                if (s[t] == 0){
                    p = i.a;
                    t--;
                    
                }
                break;
        }

        for (int j = 1; j <= t; j++){
            printf(" [%lld] ", s[j]);
        }
    } while (p != 0);
}
int main() {
    pcodevhw();
    return 0;
}
