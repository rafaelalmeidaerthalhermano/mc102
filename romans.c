/*
    Autor : Rafael Almeida Erthal Hermano
    Turma : MC102
    RA : 121286

    Programa : Valor de número romano
    Versão : 1.0.0
    Concluída : 26/03/2011

    Narrativa Livre : O programa apresenta na tela o valor em algarismos arábicos de um número romano entre I e MMMCMXCIX (entre 1 e 3999) fornecido em uma linha, via teclado.
*/

#include <stdio.h>

#define VALUE_ONE_UPPERCASE 'I'
#define VALUE_FIVE_UPPERCASE 'V'
#define VALUE_TEN_UPPERCASE 'X'
#define VALUE_FIFTY_UPPERCASE 'L'
#define VALUE_ONE_HUNDRED_UPPERCASE 'C'
#define VALUE_FIVE_HUNDRED_UPPERCASE 'D'
#define VALUE_ONE_THOUSAND_UPPERCASE 'M'

#define VALUE_ONE_LOWERCASE 'i'
#define VALUE_FIVE_LOWERCASE 'v'
#define VALUE_TEN_LOWERCASE 'x'
#define VALUE_FIFTY_LOWERCASE 'l'
#define VALUE_ONE_HUNDRED_LOWERCASE 'c'
#define VALUE_FIVE_HUNDRED_LOWERCASE 'd'
#define VALUE_ONE_THOUSAND_LOWERCASE 'm'

int main(void)
{
    char digit = 'a';
    int currentDigitValue = 0, previousDigitValue = 0, numberValue = 0;

    printf("Digite o numero romano:");

    while((digit = getchar()) != '\n')
    {
        //Converter o valor de romano para inteiro
        switch (digit)
        {
            case VALUE_ONE_UPPERCASE:
            case VALUE_ONE_LOWERCASE:
                currentDigitValue = 1;
                break;
            case VALUE_FIVE_UPPERCASE:
            case VALUE_FIVE_LOWERCASE:
                currentDigitValue = 5;
                break;
            case VALUE_TEN_UPPERCASE:
            case VALUE_TEN_LOWERCASE:
                currentDigitValue = 10;
                break;
            case VALUE_FIFTY_UPPERCASE:
            case VALUE_FIFTY_LOWERCASE:
                currentDigitValue = 50;
                break;
            case VALUE_ONE_HUNDRED_UPPERCASE:
            case VALUE_ONE_HUNDRED_LOWERCASE:
                currentDigitValue = 100;
                break;
            case VALUE_FIVE_HUNDRED_UPPERCASE:
            case VALUE_FIVE_HUNDRED_LOWERCASE:
                currentDigitValue = 500;
                break;
            case VALUE_ONE_THOUSAND_UPPERCASE:
            case VALUE_ONE_THOUSAND_LOWERCASE:
                currentDigitValue = 1000;
                break;
            default:
                currentDigitValue = 0;
        }

        //acrescentar o valor coletado no valor total
        numberValue += currentDigitValue;

        //caso o digito coletado anteriormente seja menor que o digito coletado retirar o digito anterior duas vezes
        if(previousDigitValue < currentDigitValue) numberValue -= 2 * previousDigitValue;

        //gravar o valor do digito coletado
        previousDigitValue = currentDigitValue;
    }

    printf("O numero em arabico:%d\n", numberValue);

    return 0;
}
