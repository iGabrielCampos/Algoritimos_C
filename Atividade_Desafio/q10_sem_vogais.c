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
    char texto[256];
    char sem_vogais[256];
    int j = 0;

    printf("==================================================\n");
    printf("                REMOVER VOGAIS                    \n");
    printf("==================================================\n");

    printf("Digite um texto: ");
    fgets(texto, 256, stdin);
    remover_quebra_linha(texto);

    // copia apenas os caracteres que nao sao vogais
    for (int i = 0; texto[i] != '\0'; i++) {
        char c = texto[i];
        int eh_vogal = 0;

        switch (c) {
            case 'a':
            case 'A':
            case 'e':
            case 'E':
            case 'i':
            case 'I':
            case 'o':
            case 'O':
            case 'u':
            case 'U':
                eh_vogal = 1;
                break;
        }

        if (eh_vogal == 0) {
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
