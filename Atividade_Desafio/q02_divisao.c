#include <stdio.h>

int main() {
    float primeiro_valor = 0.0f;
    float segundo_valor = 0.0f;

    printf("==================================================\n");
    printf("              DIVISAO DE DOIS VALORES             \n");
    printf("==================================================\n");

    printf("Digite o primeiro valor: ");
    scanf("%f", &primeiro_valor);

    printf("Digite o segundo valor: ");
    scanf("%f", &segundo_valor);

    // segundo valor nao pode ser zero; repete enquanto for invalido
    while (segundo_valor == 0.0f) {
        printf("VALOR INVALIDO\n");
        printf("Digite um segundo valor diferente de zero: ");
        if (scanf("%f", &segundo_valor) != 1) {
            break;
        }
    }

    float resultado = primeiro_valor / segundo_valor;

    printf("\n==================================================\n");
    printf("Resultado da divisao: %.2f\n", resultado);
    printf("==================================================\n");

    return 0;
}
