/*
    Autor : Rafael Almeida Erthal Hermano
    Turma : MC102
    RA : 121286

    Programa : Conjectura de Collatz - Questão 1 da primeira prova prática
    Versão : 1.0.0
    Concluída : 25/04/2011

    Narrativa Livre : O programa le o primeiro elemento de uma sequência de Collatz e reproduz o resto da sequencia, na saída padrão, a sequência a partir do primeiro elemento dado até ser alcançado o valor 1. A função retorna o número de elementos da sequência gerada a partir do valor inicial até o 1, inclusive
*/

#include <stdio.h>

//método que verifica se um número inteiro é par
int isOdd(int number)
{
    return(number % 2 == 0);
}

//método que organiza as quebras de linha
void formatedOutput(int numberOfTerms)
{
    if(numberOfTerms % 10 == 0) printf("\n");
}

//método que imprimie a sequencia de collatz
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

    //printa o número de termos
    printf("\n\n%d  ", numberOfTerms);
}

int main(void)
{
    int term;

    //ler o primeiro número da sequencia
    printf("Digite o primeiro termo da série de Collatz:");
    scanf("%d",&term);

    printCollatzSequence(term);

    return 0;
}
