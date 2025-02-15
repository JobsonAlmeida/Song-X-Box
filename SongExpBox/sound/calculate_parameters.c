#include <stdio.h>          
#include <stdlib.h>
#include <math.h>

float frequencia_nota; 
float fCLKsys = 125000000.f;

int max_wrap = 0;
int best_inteiro = 0;
float best_frac = 0;
float best_fpwm = 0;

int  wrap_limit = 0;

void calcular(){

    float divisor;
    float fpwm_calc;

    for(int wrap = wrap_limit; wrap>=0 ; wrap-- ){
        for(int inteiro = 1; inteiro <= 256; inteiro++){
            for(float frac = 1; frac <= 15; frac++){

                divisor = inteiro + frac/16;

                fpwm_calc = fCLKsys / ( ( divisor) * (wrap + 1) );

                if( fabs(fpwm_calc - frequencia_nota) < fabs(best_fpwm - frequencia_nota) ){
                    max_wrap = wrap;
                    best_inteiro = inteiro;
                    best_frac = frac;
                    best_fpwm = fpwm_calc;
                }

                if (fabs(best_fpwm - frequencia_nota) < 0.000001 ){
                    printf("Calculou os melhores valores!\n");
                    return;
                }                
            }
        }
    }

    return;
}

int main(){

    system("cls");

    wrap_limit =  ((int) pow(2, 16) ) - 1;

    frequencia_nota = 523.2511;

    calcular();
    
    printf("-----Resultados-----\n\n");
    printf("frequencia_nota = %.4f\n", frequencia_nota);
    printf("\n//Best Frequency Found: = %.4f\n", best_fpwm);
    printf("max_wrap = %d\n", max_wrap) ;
    printf("best_inteiro = %d\n", best_inteiro );
    printf("best_frac = %.4f\n", best_frac);
    printf("best_divider = %.4f\n", fCLKsys / ( frequencia_nota * (max_wrap + 1) ) );
    

    return 0;
}