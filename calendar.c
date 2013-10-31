/*
    Autor : Rafael Almeida Erthal Hermano
    Turma : MC102
    RA : 121286

    Programa : Calendario Gregoriano
    Versão : 1.0.0
    Concluída : 04/04/2011

    Narrativa Livre : O programa em questão recebe como entrada dois valores inteiros: o primeiro, um valor entre 1 e 12 representando um mês, e o segundo, um ano. Com base em tais valores, o programa produz uma folha de calendário do respectivo mês.
*/

#include <stdio.h>

#define JANUARY 1
#define FEBRUARY 2
#define MARCH 3
#define APRIL 4
#define MAY 5
#define JUNE 6
#define JULY 7
#define AUGUST 8
#define SEPTEMBER 9
#define OCTOBER 10
#define NOVEMBER 11
#define DECEMBER 12

#define SUNDAY 1
#define MONDAY 2
#define TUESDAY 3
#define WEDNESDAY 4
#define THURSDAY 5
#define FRIDAY 6
#define SATURDAY 7

int main(void)
{
    int year, month, day, currentWeekDay, currentMonthLength, spacer;

    printf("Digite o Mes e o Ano:");
    scanf("%d %d", &month, &year);

    printHeader(month, year);

    currentMonthLength = monthLength(month, year);

    for (day = 1; day <= currentMonthLength ; day++)
    {
        currentWeekDay = weekDay(day, month, year);

        //Alinhar primeiro dia do mes com o dia da semana
        if (day == 1)
            for (spacer = 1; spacer < currentWeekDay; spacer++) printf("    ");

        //Printar o dia
        printf("%3d ", day);

        //Se for o último dia da semana pular linha
        if (currentWeekDay == SATURDAY) printf("\n");
    }

    printf("\n");

    return 0;
}


//MÉTODO QUE DESENHA O CABEÇALHO DO CALENDARIO
int printHeader(int currentMonth, int currentYear)
{
    switch (currentMonth)
    {
    case JANUARY:
        printf("\n      Janeiro de %d", currentYear);
        break;

    case FEBRUARY:
        printf("\n     Fevereiro de %d", currentYear);
        break;

    case MARCH:
        printf("\n       Marco de %d", currentYear);
        break;

    case APRIL:
        printf("\n       Abril de %d", currentYear);
        break;

    case MAY:
        printf("\n        Maio de %d", currentYear);
        break;

    case JUNE:
        printf("\n       Junho de %d", currentYear);
        break;

    case JULY:
        printf("\n       Julho de %d", currentYear);
        break;

    case AUGUST:
        printf("\n       Agosto de %d", currentYear);
        break;

    case SEPTEMBER:
        printf("\n        Setembro de %d", currentYear);
        break;

    case OCTOBER:
        printf("\n      Outubro de %d", currentYear);
        break;

    case NOVEMBER:
        printf("\n      Novembro de %d", currentYear);
        break;

    case DECEMBER:
        printf("\n      Dezembro de %d", currentYear);
        break;
    }
    printf("\n\nDOM SEG TER QUA QUI SEX SAB\n");
}


//MÉTODO QUE RETORNA O NÚMERO DE DIAS DE UM MÊS
int monthLength(int currentMonth, int currentYear)
{
    switch (currentMonth)
    {
    case JANUARY:
    case MARCH:
    case MAY:
    case JULY:
    case AUGUST:
    case OCTOBER:
    case DECEMBER:
        return 31;
        break;

    case APRIL:
    case JUNE:
    case SEPTEMBER:
    case NOVEMBER:
        return 30;
        break;

    case FEBRUARY:
        //Se for ano bissexto fevereiro tem 29 dias
        if (((currentYear % 4 == 0) && (currentYear % 100 != 0)) || (currentYear % 400 == 0)) return 29;
        //caso contrário fevereiro tem 28 dias
        else return 28;
        break;
    }
}


//MÉTODO QUE RETORNA O DIA DA SEMANA DE UMA DATA
int weekDay(int d, int m, int a)
{
    int x, res;

    if (m > 2)
    {
        m = m - 2;
        x = 8;
    }
    else
    {
        a = a - 1;
        x = 13;
    }

    res = (x + d + 2 * m + ((7 * m) / 12) + a % 7 +
           a / 4 % 7 - (3 * (1 + a / 100)) / 4 % 7) % 7;

    //correção da formula pois ela poem sabado como o primeiro dia da semana.
    if (res == 0) return SATURDAY;
    else return res;
}
