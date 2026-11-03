#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Iniciando o sistema FerraLog...\n\n");
    sleep(1);
    printf("[*] Conectando ao banco de dados de inventario...\n");
    sleep(1);

    printf("[*] Carregando modulo de leitura de QR Code...\n");
    sleep(1);

    printf("[*] Verificando status e validade das garantias...\n");
    sleep(2);

    printf("[*] Sincronizando dados...\n\n");
    sleep(1);	

    system("cls");

    printf("==================================================\n");
    printf("          SISTEMA FERRALOG - INVENTARIO           \n");
    printf("==================================================\n");
    printf("Sistema carregado com sucesso!\n\n");

    printf("Selecione uma opcao no menu abaixo:\n");
    printf("[1] Cadastrar nova ferramenta\n");
    printf("[2] Consultar ferramenta por QR Code\n");
    printf("[3] Verificar status de garantia\n");
    printf("[4] Sair do sistema\n");

    printf("==================================================\n");
    printf("Digite a opcao desejada: ");

    return 0;
}