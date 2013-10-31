#include <stdio.h>

#define UNDER_WEIGHT    18.5
#define NORMAL_WEIGHT   25.0
#define PRE_OBESITY     30.0
#define GRADE_1_OBESITY 35.0
#define GRADE_2_OBESITY 40.0


int main(void){
    float height, heightSquared, weight, bodyMassIndex, minimumWeight, maximumWeight;

    printf("Digite a sua altura:");
    scanf("%f", &height);

    printf("Digite o seu peso:");
    scanf("%f", &weight);

    heightSquared    = ( height * height );

    bodyMassIndex   = ( weight )          / heightSquared;
    minimumWeight   = ( NORMAL_WEIGHT )   * heightSquared;
    maximumWeight   = ( PRE_OBESITY )     * heightSquared;

    printf("Sua classificação pela OMS:");
    if      (bodyMassIndex < UNDER_WEIGHT)      printf("Abaixo do peso.");
    else if (bodyMassIndex < NORMAL_WEIGHT)     printf("Peso normal.");
    else if (bodyMassIndex < PRE_OBESITY)       printf("Pre obesidade.");
    else if (bodyMassIndex < GRADE_1_OBESITY)   printf("Obesidade grau 1.");
    else if (bodyMassIndex < GRADE_2_OBESITY)   printf("Obesidade grau 2.");
    else                                        printf("Obesidade grau 3.");

    printf("\n\n");

    printf("A sua faixa de peso recomendada pela OMS:");
    printf("%5.1f", minimumWeight);
    printf(" ate ");
    printf("%5.1f", maximumWeight);

    printf("\n\n");

    return 0;
}
