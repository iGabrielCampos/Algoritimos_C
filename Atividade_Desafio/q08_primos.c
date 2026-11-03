#include <stdio.h>

int main(void) {
    int numeros[20];
    int primos[20];
    int total_primos = 0;

    printf("==================================================\n");
    printf("             NUMEROS PRIMOS NO VETOR              \n");
    printf("==================================================\n");

    printf("Digite 20 numeros inteiros positivos:\n");
    for (int i = 0; i < 20; i++) {
        printf("Posicao [%d]: ", i + 1);
        scanf("%d", &numeros[i]);

        while (numeros[i] <= 0) {
            printf("Digite apenas positivos! Tente de novo [%d]: ", i + 1);
            if (scanf("%d", &numeros[i]) != 1) {
                break;
            }
        }
    }

    // testa cada numero: 1 nao e primo; testa divisores ate raiz de n
    for (int i = 0; i < 20; i++) {
        int n = numeros[i];
        int eh_primo = 1;

        if (n <= 1) {
            eh_primo = 0;
        } else {
            for (int d = 2; d * d <= n; d++) {
                if (n % d == 0) {
                    eh_primo = 0;
                    break;
                }
            }
        }

        if (eh_primo) {
            primos[total_primos] = n;
            total_primos++;
        }
    }

    printf("\n==================================================\n");
    printf("Quantidade de primos: %d\n", total_primos);

    if (total_primos > 0) {
        printf("Primos encontrados: ");
        for (int i = 0; i < total_primos; i++) {
            printf("%d%s", primos[i], (i == total_primos - 1) ? "" : ", ");
        }
        printf("\n");
    } else {
        printf("Nenhum primo foi digitado.\n");
    }
    printf("==================================================\n");

    return 0;
}
