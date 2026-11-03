#include <stdio.h>

int main(void) {
    float notas[20];
    float soma = 0.0f;
    int acima_da_media = 0;

    printf("==================================================\n");
    printf("              MEDIA DE NOTAS DA TURMA             \n");
    printf("==================================================\n");

    for (int i = 0; i < 20; i++) {
        printf("Digite a nota do aluno [%d]: ", i + 1);
        scanf("%f", &notas[i]);
        soma += notas[i];
    }

    float media = soma / 20.0f;

    // conta quantos ficaram acima da media calculada
    for (int i = 0; i < 20; i++) {
        if (notas[i] > media) {
            acima_da_media++;
        }
    }

    printf("\n==================================================\n");
    printf("Media da turma: %.2f\n", media);
    printf("Alunos acima da media: %d\n", acima_da_media);
    printf("==================================================\n");

    return 0;
}
