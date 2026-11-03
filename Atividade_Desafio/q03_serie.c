#include <stdio.h>

int main(void) {
    double soma_s = 0.0;

    printf("==================================================\n");
    printf("             CALCULO DA SERIE S                   \n");
    printf("==================================================\n");

    // termo i: numerador impar (2*i - 1) sobre i, de 1 ate 50
    for (int i = 1; i <= 50; i++) {
        int numerador = 2 * i - 1;
        int denominador = i;
        soma_s += (double)numerador / (double)denominador;
    }

    printf("S = 1 + 3/2 + 5/3 + 7/4 + ... + 99/50\n");
    printf("Valor de S: %.4lf\n", soma_s);
    printf("==================================================\n");

    return 0;
}
