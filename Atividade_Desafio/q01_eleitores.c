#include <stdio.h>

int main() {
    int total_eleitores = 0;
    int votos_brancos = 0;
    int votos_nulos = 0;
    int votos_validos = 0;

    printf("==================================================\n");
    printf("              APURACAO DE ELEITORES               \n");
    printf("==================================================\n");

    printf("Digite o numero total de eleitores: ");
    scanf("%d", &total_eleitores);

    // evita divisao por zero se o total for invalido
    if (total_eleitores <= 0) {
        printf("\n[ERRO] O total de eleitores precisa ser maior que zero!\n");
        return 1;
    }

    printf("Digite o numero de votos brancos: ");
    scanf("%d", &votos_brancos);

    printf("Digite o numero de votos nulos: ");
    scanf("%d", &votos_nulos);

    printf("Digite o numero de votos validos: ");
    scanf("%d", &votos_validos);

    // percentual de cada tipo de voto sobre o total
    float perc_brancos = ((float)votos_brancos / (float)total_eleitores) * 100.0f;
    float perc_nulos = ((float)votos_nulos / (float)total_eleitores) * 100.0f;
    float perc_validos = ((float)votos_validos / (float)total_eleitores) * 100.0f;

    printf("\n==================================================\n");
    printf("              RESULTADO DA APURACAO               \n");
    printf("==================================================\n");
    printf("Total de eleitores: %d\n", total_eleitores);
    printf("Votos brancos: %d (%.2f%%)\n", votos_brancos, perc_brancos);
    printf("Votos nulos:   %d (%.2f%%)\n", votos_nulos, perc_nulos);
    printf("Votos validos: %d (%.2f%%)\n", votos_validos, perc_validos);
    printf("==================================================\n");

    return 0;
}
