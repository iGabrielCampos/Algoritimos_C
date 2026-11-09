#include <stdio.h>
#include <string.h>

void remover_quebra_linha(char str[]) {
    int len = strlen(str);
    if (len > 0) {
        if (str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }
    }
}

int main() {
    char nomes[10][50];
    char nome_busca[50];
    int achou = 0;

    printf("==================================================\n");
    printf("                 BUSCA DE NOMES                   \n");
    printf("==================================================\n");

    printf("Digite 10 nomes:\n");
    for (int i = 0; i < 10; i++) {
        printf("Nome [%d]: ", i + 1);
        fgets(nomes[i], 50, stdin);
        remover_quebra_linha(nomes[i]);
    }

    printf("\nDigite um nome para pesquisar: ");
    fgets(nome_busca, 50, stdin);
    remover_quebra_linha(nome_busca);

    // busca linear pelo nome informado
    for (int i = 0; i < 10; i++) {
        if (strcmp(nomes[i], nome_busca) == 0) {
            achou = 1;
            break;
        }
    }

    printf("\n==================================================\n");
    if (achou == 1) {
        printf("ACHEI\n");
    } else {
        printf("NAO ACHEI\n");
    }
    printf("==================================================\n");

    return 0;
}
