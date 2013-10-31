/*
    Autor : Rafael Almeida Erthal Hermano
    Turma : MC102
    RA : 121286

    Programa : Validação do CPF
    Versão : 1.0.0
    Concluída : 21/03/2011

    Narrativa Livre : O programa pega os 11 primeiros digitos que podem ser convertidos para inteiro do teclado e avalia se eles podem ser entendidos como um CPF
*/

#include <stdio.h>
#define DIGITS_NUMBER 11
#define MINIMUM_ASCII_NUMBER '0'
#define MAXIMUM_ASCII_NUMBER '9'

int main(void){
    int digitIndex = 1, term10sum = 0, term11sum = 0, digit10, digit11, term10, term11;
    char digit;

    printf("DIGITE O SEU CPF:");

    //Laço para pegar os digitos válidos
    while(digitIndex <= DIGITS_NUMBER)
    {
        digit = getchar();

        if(digit >= MINIMUM_ASCII_NUMBER && digit <= MAXIMUM_ASCII_NUMBER)
        {
            //Caso o digito entrado esteja na posição de verificação armazena-lo separadamente
            if      (digitIndex == 10) digit10 = (int)(digit - MINIMUM_ASCII_NUMBER);
            else if (digitIndex == 11) digit11 = (int)(digit - MINIMUM_ASCII_NUMBER);
            //Caso contrário alimentar somatórios para calculo dos digitos de verificação
            else
            {
                term10sum += (int)(digit - MINIMUM_ASCII_NUMBER) * (digitIndex);
                term11sum += (int)(digit - MINIMUM_ASCII_NUMBER) * (digitIndex - 1);
            }

            digitIndex++;
        }
    }

    //Calculo do primeiro digito de verificação
    term10 = ((term10sum % 11) % 10);

    //Calculo do segundo dígito de verificação
    term11sum += term10 * 9;
    term11 = ((term11sum % 11) % 10);

    //Validação dos digitos coletados
    if((term10 == digit10) && (term11 == digit11)) printf("\nCPF VALIDO.");
    else printf("\nCPF INVALIDO.");

    return 0;
}
