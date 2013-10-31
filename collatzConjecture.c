/*
    Autor : Rafael Almeida Erthal Hermano
    Turma : MC102
    RA : 121286

    Programa : Conjectura de Collatz - Quest�o 1 da primeira prova pr�tica
    Vers�o : 1.0.0
    Conclu�da : 25/04/2011

    Narrativa Livre : O programa le o primeiro elemento de uma sequ�ncia de Collatz e reproduz o resto da sequencia, na sa�da padr�o, a sequ�ncia a partir do primeiro elemento dado at� ser alcan�ado o valor 1. A fun��o retorna o n�mero de elementos da sequ�ncia gerada a partir do valor inicial at� o 1, inclusive
*/

#include <stdio.h>

//m�todo que verifica se um n�mero inteiro � par
int isOdd(int number)
{
    return(number % 2 == 0);
}

//m�todo que organiza as quebras de linha
void formatedOutput(int numberOfTerms)
{
    if(numberOfTerms % 10 == 0) printf("\n");
}

//m�todo que imprimie a sequencia de collatz
void printCollatzSequence(int term)
{
    int numberOfTerms = 1;

    //printa o primeiro termo
    printf("\n%d  ", term);

    while(term != 1)
    {
        //calcula o proximo termo da sequencia
        if(isOdd(term)) term = term / 2;
        else term = 3*term + 1;

        //printa o termo
        printf("%d  ", term);

        //formata a saida do programa
        formatedOutput(++numberOfTerms);
    }

    //printa o n�mero de termos
    printf("\n\n%d  ", numberOfTerms);
}

int main(void)
{
    int term;

    //ler o primeiro n�mero da sequencia
    printf("Digite o primeiro termo da s�rie de Collatz:");
    scanf("%d",&term);

    printCollatzSequence(term);

    return 0;
}
