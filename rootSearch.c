/*
    Autor : Rafael Almeida Erthal Hermano
    Turma : MC102
    RA : 121286

    Programa : Raiz do Polinomio - Quest�o 2 da primeira prova pr�tica
    Vers�o : 1.0.0
    Conclu�da : 25/04/2011

    Narrativa Livre : O programa determina e retorna a raiz do polin�mio p(x) no intervalo delimitado pelos valores a e b, inclusive, segundo o m�todo de bissec��o. A cada ciclo ap�s o c�lculo de c e a redefini��o de a ou b, os valores correntes de a, b, c e p(c) s�o apresentados na sa�da padr�o
*/

#include <stdio.h>

#define POLYNOMIAL_EQUATION_SIZE 15
#define EPSILON 0.000001

//M�todo que calcula o valor do polinomio com determinada abscissa
float polynomialValue(int level, float polynomialEquation[], float abscissa)
{
    int currentCoefficient;
    float value = 0.0, multiplicand = 1.0;

    for(currentCoefficient = 0; currentCoefficient <= level; currentCoefficient++)
    {
        value += polynomialEquation[currentCoefficient] * (multiplicand);
        multiplicand *= abscissa;
    }

    return value;
}

//fun��o m�dulo
float module(float number)
{
    if (number < 0) return -number;
    else return number;
}

//M�todo que calcula a raiz do polinomio
float calculatePolynomRoot(int level,float polynomialEquation[], float intervalBeginning, float intervalEnding)
{
    float abscissa;

    do
    {
        //calcular a abscissa utilizada nos calculos do valor do polinomio
        abscissa = (intervalBeginning + intervalEnding) / 2;

        //ajustar intervalo de busca com os valores obtidos
        if (polynomialValue(level, polynomialEquation, intervalBeginning) * polynomialValue(level, polynomialEquation, abscissa) < 0)
            intervalEnding = abscissa;
        else
            intervalBeginning = abscissa;

        //mostrar andamento da busca pela raiz
        printf("Intervalo de busca:[%f, %f] \n",intervalBeginning, intervalEnding);
        printf("P(%f) = %f\n\n", abscissa,polynomialValue(level, polynomialEquation, abscissa));

    }while(module(polynomialValue(level, polynomialEquation, abscissa)) > EPSILON);

    //mostrar a raiz encontrada
    return abscissa;
}

int main(void)
{
    int level, currentCoefficient;

    float polynomialEquation[POLYNOMIAL_EQUATION_SIZE], intervalBeginning, intervalEnding;

    //ler o grau do polinomio
    printf("Grau do polinomio: ");
    scanf("%d", &level);

    //ler coeficientes do polinomio
    if (level < POLYNOMIAL_EQUATION_SIZE)
    {
        printf("Coeficientes do polinomio: ");
        for (currentCoefficient = 0; currentCoefficient <= level; currentCoefficient++) scanf("%f", &polynomialEquation[currentCoefficient]);
    }
    else printf("Grau do polinomio muito elevado!");

    //ler intervalo de busca da raiz real
    printf("\nIntervalo Desejado: ");
    scanf("%f %f", &intervalBeginning, &intervalEnding);

    printf("\nA raiz no intervalo e: %f", calculatePolynomRoot(level, polynomialEquation, intervalBeginning, intervalEnding));

    return 0;
}
