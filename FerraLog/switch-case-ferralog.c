#include <stdio.h>
#include <stdlib.h>

int main() {
    int opcao_menu = 0;
    char nome_ferramenta[50];
    int codigo_qr = 0;
    float valor_compra = 0.0;
    int possui_garantia = 0;

    printf("==================================================\n");
    printf("          SISTEMA FERRALOG - INVENTARIO           \n");
    printf("==================================================\n");
    printf("[1] Cadastrar nova ferramenta\n");
    printf("[2] Consultar ferramenta\n");
    printf("[3] Relatorios\n");
    printf("[4] Sair do sistema\n");
    printf("==================================================\n");
    printf("Digite a opcao desejada: ");
    
    // Leitura da escolha do usuario
    scanf("%d", &opcao_menu);

    system("clear"); // No Windows, alterar para "cls"

    // Estrutura de decisao ideal para menus
    switch(opcao_menu) {
        case 1:
            printf("--- MODULO DE CADASTRO ---\n");
            printf("Nome da ferramenta: ");
            scanf("%s", nome_ferramenta); 
            
            printf("Codigo QR: ");
            scanf("%d", &codigo_qr); 
            
            printf("Valor da compra: R$ ");
            scanf("%f", &valor_compra);
            
            printf("Possui garantia? (1 para SIM, 0 para NAO): ");
            scanf("%d", &possui_garantia);

            system("clear");

            printf("--- RECIBO FERRALOG ---\n");
            printf("Ferramenta: %s\n", nome_ferramenta);
            printf("QR Code: %d\n", codigo_qr);
            printf("Valor: R$ %.2f\n", valor_compra);
            
            // Verifica se a ferramenta custa mais de 1000 e nao possui garantia
            int alto_risco = 0;
            if (valor_compra > 1000.0) {
                if (possui_garantia == 0) {
                    alto_risco = 1;
                }
            }

            if (alto_risco == 1) {
                printf("Status: ALERTA: Equipamento caro cadastrado sem garantia!\n");
            } else {
                printf("Status: Cadastro realizado com sucesso.\n");
            }
            
            // O break impede que o codigo invada o "case 2"
            break; 

        case 2:
            printf("Aviso: O modulo de consulta de QR Code esta em desenvolvimento.\n");
            break;

        case 3:
            printf("Aviso: O modulo de relatorios financeiros esta em desenvolvimento.\n");
            break;

        case 4:
            printf("Salvando dados...\nSaindo do sistema. Ate logo!\n");
            break;

        default:
            // Escudo para entradas invalidas (ex: se o usuario digitar 9)
            printf("ERRO: A opcao %d nao existe no menu.\n", opcao_menu);
            break;
    }

    return 0;
}
