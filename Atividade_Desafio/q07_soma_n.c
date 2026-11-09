#include <stdio.h>

int main() {
    int valor_a = 0;
    int valor_n = 0;
    int soma = 0;

    printf("==================================================\n");
    printf("         SOMA DE N NUMEROS A PARTIR DE A          \n");
    printf("==================================================\n");

    printf("Digite o valor de A: ");
    scanf("%d", &valor_a);

    printf("Digite o valor de N: ");
    scanf("%d", &valor_n);

    // N precisa ser estritamente maior que zero
    while (valor_n <= 0) {
        printf("Valor de N invalido! Digite novamente: ");
        if (scanf("%d", &valor_n) != 1) {
            break;
        }
    }

    for (int i = 0; i < valor_n; i++) {
        soma += (valor_a + i);
    }

    printf("\n==================================================\n");
    printf("Soma = %d\n", soma);
    printf("==================================================\n");

    return 0;
}
