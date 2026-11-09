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

void contar_vogais() {
    char mensagem[256];
    int qtd_a = 0;
    int qtd_e = 0;
    int qtd_i = 0;
    int qtd_o = 0;
    int qtd_u = 0;

    printf("Digite uma mensagem: ");
    fgets(mensagem, 256, stdin);
    remover_quebra_linha(mensagem);

    // conta cada vogal considerando minusculas e maiusculas
    for (int i = 0; mensagem[i] != '\0'; i++) {
        char c = mensagem[i];

        if (c == 'a') {
            qtd_a++;
        } else if (c == 'A') {
            qtd_a++;
        } else if (c == 'e') {
            qtd_e++;
        } else if (c == 'E') {
            qtd_e++;
        } else if (c == 'i') {
            qtd_i++;
        } else if (c == 'I') {
            qtd_i++;
        } else if (c == 'o') {
            qtd_o++;
        } else if (c == 'O') {
            qtd_o++;
        } else if (c == 'u') {
            qtd_u++;
        } else if (c == 'U') {
            qtd_u++;
        }
    }

    printf("\n==================================================\n");
    printf("              CONTAGEM DE VOGAIS                  \n");
    printf("==================================================\n");
    printf("Vogal A: %d\n", qtd_a);
    printf("Vogal E: %d\n", qtd_e);
    printf("Vogal I: %d\n", qtd_i);
    printf("Vogal O: %d\n", qtd_o);
    printf("Vogal U: %d\n", qtd_u);
    printf("Total de vogais: %d\n", qtd_a + qtd_e + qtd_i + qtd_o + qtd_u);
    printf("==================================================\n");
}

int main() {
    printf("==================================================\n");
    printf("                 CONTAGEM DE VOGAIS               \n");
    printf("==================================================\n");

    contar_vogais();

    return 0;
}
