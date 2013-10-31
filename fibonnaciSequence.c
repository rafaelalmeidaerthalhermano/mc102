/*
    Autor : Rafael Almeida Erthal Hermano
    Turma : MC102
    RA : 121286

    Programa : Aproxima��o de Fi
    Vers�o : 1.0.0
    Conclu�da : 09/05/2011

    Narrativa Livre : O programa calcula uma aproxima��o para FI tal que o m�dulo de FI(i) - FI(i-1) <= episilon  para i>0, onde episilon deve ser definido como constante. O programa tamb�m apresenta o n�mero de itera��es necess�rias para obter a aproxima��o desejada (isto �, o valor de i correspondente � aproxima��o calculada).
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
