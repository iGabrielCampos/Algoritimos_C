#include <stdio.h>

int main() {
    // Desenhando o cabecalho do sistema FerraLog
    printf("==================================================\n");
    printf("          SISTEMA FERRALOG - INVENTARIO           \n");
    printf("==================================================\n");

    printf("\nBem-vindo ao controle logistico de ferramentas.\n\n");

    // Apresentando as opcoes do menu principal
    printf("Selecione uma opcao no menu abaixo:\n");
    printf("[1] Cadastrar nova ferramenta\n");
    printf("[2] Consultar ferramenta por Setor\n");
    printf("[3] Verificar status de garantia\n");
    printf("[4] Sair do sistema\n");

    printf("==================================================\n");
    printf("Digite a opcao desejada: ");

    // O cursor ficara piscando aqui. A leitura (scanf) sera o assunto da proxima aula!

    return 0;
}
