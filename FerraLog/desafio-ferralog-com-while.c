#include <stdio.h>
#include <stdlib.h>

int main() {
    int opcao_menu = 0;
    
    // Variaveis de cadastro
    char nome_ferramenta[50];
    unsigned int codigo_qr = 0;
    float valor_compra = 0.0;
    int possui_garantia = 0;

    // O laço inicia aqui e envelopa todo o fluxo do sistema
    do {
        printf("==================================================\n");
        printf("          SISTEMA FERRALOG - INVENTARIO           \n");
        printf("==================================================\n");
        printf("[1] Cadastrar nova ferramenta\n");
        printf("[2] Consultar ferramenta\n");
        printf("[3] Relatorios\n");
        printf("[4] Sair do sistema\n");
        printf("==================================================\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao_menu);

        system("clear"); // No Windows, lembre de usar "cls"

        switch(opcao_menu) {
            case 1:
                printf("--- MODULO DE CADASTRO ---\n");
                printf("Nome da ferramenta: ");
                scanf("%s", nome_ferramenta); 
                
                printf("Codigo QR: ");
                scanf("%u", &codigo_qr); 
                
                printf("Valor da compra: R$ ");
                scanf("%f", &valor_compra);
                
                printf("Possui garantia? (1 para SIM, 0 para NAO): ");
                scanf("%d", &possui_garantia);

                system("clear");
                printf("--- RECIBO FERRALOG ---\n");
                printf("Ferramenta '%s' (QR: %u) cadastrada com sucesso!\n\n", nome_ferramenta, codigo_qr);
                break; 

            case 2:
                printf("Modulo de consulta em desenvolvimento...\n\n");
                break;

            case 3:
                printf("Modulo de relatorios em desenvolvimento...\n\n");
                break;

            case 4:
                printf("Salvando dados...\nSaindo do sistema. Ate logo!\n");
                break;

            default:
                printf("ERRO: Opcao invalida. Tente novamente.\n\n");
                break;
        }

    // A condicao do loop: volta para o inicio enquanto a opcao nao for 4
    } while (opcao_menu != 4);

    return 0;
}