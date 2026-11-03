#include <stdio.h>
#include <string.h>

void remover_quebra_linha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void contar_vogais(void) {
    char mensagem[256];
    int qtd_a = 0;
    int qtd_e = 0;
    int qtd_i = 0;
    int qtd_o = 0;
    int qtd_u = 0;

    printf("Digite uma mensagem: ");
    if (fgets(mensagem, sizeof(mensagem), stdin) == NULL) {
        return;
    }
    remover_quebra_linha(mensagem);

    // conta cada vogal considerando minusculas e maiusculas
    for (int i = 0; mensagem[i] != '\0'; i++) {
        char c = mensagem[i];

        if (c == 'a' || c == 'A') {
            qtd_a++;
        } else if (c == 'e' || c == 'E') {
            qtd_e++;
        } else if (c == 'i' || c == 'I') {
            qtd_i++;
        } else if (c == 'o' || c == 'O') {
            qtd_o++;
        } else if (c == 'u' || c == 'U') {
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

int main(void) {
    printf("==================================================\n");
    printf("                 CONTAGEM DE VOGAIS               \n");
    printf("==================================================\n");

    contar_vogais();

    return 0;
}
