#include <stdio.h>
#include <string.h>

void remover_quebra_linha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int main(void) {
    char nomes[10][50];
    char nome_busca[50];
    int achou = 0;

    printf("==================================================\n");
    printf("                 BUSCA DE NOMES                   \n");
    printf("==================================================\n");

    printf("Digite 10 nomes:\n");
    for (int i = 0; i < 10; i++) {
        printf("Nome [%d]: ", i + 1);
        if (fgets(nomes[i], sizeof(nomes[i]), stdin) != NULL) {
            remover_quebra_linha(nomes[i]);
        }
    }

    printf("\nDigite um nome para pesquisar: ");
    if (fgets(nome_busca, sizeof(nome_busca), stdin) != NULL) {
        remover_quebra_linha(nome_busca);
    }

    // busca linear pelo nome informado
    for (int i = 0; i < 10; i++) {
        if (strcmp(nomes[i], nome_busca) == 0) {
            achou = 1;
            break;
        }
    }

    printf("\n==================================================\n");
    if (achou) {
        printf("ACHEI\n");
    } else {
        printf("NAO ACHEI\n");
    }
    printf("==================================================\n");

    return 0;
}
