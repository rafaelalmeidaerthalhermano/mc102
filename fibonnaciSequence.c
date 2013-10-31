/*
    Autor : Rafael Almeida Erthal Hermano
    Turma : MC102
    RA : 121286

    Programa : Aproximação de Fi
    Versão : 1.0.0
    Concluída : 09/05/2011

    Narrativa Livre : O programa calcula uma aproximação para FI tal que o módulo de FI(i) - FI(i-1) <= episilon  para i>0, onde episilon deve ser definido como constante. O programa também apresenta o número de iterações necessárias para obter a aproximação desejada (isto é, o valor de i correspondente à aproximação calculada).
*/

#include <stdio.h>
#include <math.h>
#define EPISILON 0.000001

int main(void)
{
    double currentFi = 2, lastFi = 1;
    int termPosition = 2;

    while (fabs(currentFi - lastFi) >= EPISILON)
    {
        lastFi = currentFi;
        currentFi = 1 + 1 / lastFi;
        termPosition++;
    }

    printf("Aproximacao de fi:%f \n",currentFi);
    printf("Calculada ate o termo:%d \n",termPosition);


    return 0;
}
