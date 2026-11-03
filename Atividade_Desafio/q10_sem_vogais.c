#include <stdio.h>
#include <string.h>

void remover_quebra_linha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int main(void) {
    char texto[256];
    char sem_vogais[256];
    int j = 0;

    printf("==================================================\n");
    printf("                REMOVER VOGAIS                    \n");
    printf("==================================================\n");

    printf("Digite um texto: ");
    if (fgets(texto, sizeof(texto), stdin) != NULL) {
        remover_quebra_linha(texto);
    }

    // copia tudo que nao for vogal
    for (int i = 0; texto[i] != '\0'; i++) {
        char c = texto[i];

        if (c != 'a' && c != 'A' &&
            c != 'e' && c != 'E' &&
            c != 'i' && c != 'I' &&
            c != 'o' && c != 'O' &&
            c != 'u' && c != 'U') {
            sem_vogais[j] = c;
            j++;
        }
    }
    sem_vogais[j] = '\0';

    printf("\n==================================================\n");
    printf("Original:   %s\n", texto);
    printf("Sem vogais: %s\n", sem_vogais);
    printf("==================================================\n");

    return 0;
}
