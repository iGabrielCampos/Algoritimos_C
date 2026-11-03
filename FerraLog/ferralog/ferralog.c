#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_FERRAMENTAS 50

typedef struct {
    char nome[50];
    unsigned int codigo_qr;
    float valor_compra;
    int possui_garantia; /* 1 para SIM, 0 para NAO */
} Ferramenta;

void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void remover_quebra_linha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void tela_carregamento(void) {
    printf("Iniciando o sistema FerraLog...\n\n");
    sleep(1);
    printf("[*] Conectando ao banco de dados de inventario...\n");
    sleep(1);
    printf("[*] Carregando modulo de leitura de QR Code...\n");
    sleep(1);
    printf("[*] Verificando status e validade das garantias...\n");
    sleep(1);
    printf("[*] Sincronizando dados...\n\n");
    sleep(1);

    system("clear"); /* No Windows: "cls" */
}

void exibir_menu(void) {
    printf("==================================================\n");
    printf("          SISTEMA FERRALOG - INVENTARIO           \n");
    printf("==================================================\n");
    printf("[1] Cadastrar ferramenta\n");
    printf("[2] Consultar ferramenta\n");
    printf("[3] Relatorios\n");
    printf("[4] Sair do sistema\n");
    printf("==================================================\n");
    printf("Digite a opcao desejada: ");
}

void cadastrar_ferramenta(Ferramenta inventario[], int *total) {
    if (*total >= MAX_FERRAMENTAS) {
        printf("ERRO: Limite de armazenamento atingido (maximo de %d ferramentas).\n\n", MAX_FERRAMENTAS);
        return;
    }

    Ferramenta nova;

    printf("--- MODULO DE CADASTRO ---\n");

    printf("Nome da ferramenta: ");
    if (fgets(nova.nome, sizeof(nova.nome), stdin) == NULL) {
        printf("ERRO: Falha ao ler o nome da ferramenta.\n\n");
        return;
    }
    remover_quebra_linha(nova.nome);

    if (strlen(nova.nome) == 0) {
        printf("ERRO: O nome da ferramenta nao pode ser vazio.\n\n");
        return;
    }

    printf("Codigo QR: ");
    if (scanf("%u", &nova.codigo_qr) != 1) {
        printf("ERRO: Codigo QR invalido! Digite apenas numeros inteiros positivos.\n\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    for (int i = 0; i < *total; i++) {
        if (inventario[i].codigo_qr == nova.codigo_qr) {
            printf("ERRO: Ja existe uma ferramenta cadastrada com o Codigo QR %u.\n\n", nova.codigo_qr);
            return;
        }
    }

    printf("Valor da compra: R$ ");
    if (scanf("%f", &nova.valor_compra) != 1) {
        printf("ERRO: Entrada invalida para o valor da compra!\n\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    if (nova.valor_compra <= 0.0f) {
        printf("ERRO: O valor da compra deve ser maior que zero (R$ %.2f informado).\n\n", nova.valor_compra);
        return;
    }

    printf("Possui garantia? (1 para SIM, 0 para NAO): ");
    if (scanf("%d", &nova.possui_garantia) != 1 || (nova.possui_garantia != 0 && nova.possui_garantia != 1)) {
        printf("ERRO: Opcao de garantia invalida! Digite 1 para SIM ou 0 para NAO.\n\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    inventario[*total] = nova;
    (*total)++;

    system("clear"); /* No Windows: "cls" */

    printf("==================================================\n");
    printf("               --- RECIBO FERRALOG ---            \n");
    printf("==================================================\n");
    printf("Ferramenta: %s\n", nova.nome);
    printf("QR Code: %u\n", nova.codigo_qr);
    printf("Valor: R$ %.2f\n", nova.valor_compra);
    printf("Garantia: %s\n", nova.possui_garantia == 1 ? "SIM" : "NAO");

    if (nova.valor_compra > 1000.0f && nova.possui_garantia == 0) {
        printf("STATUS: *** ALERTA DE ALTO RISCO FINANCEIRO ***\n");
        printf("Motivo: Equipamento de alto valor alocado sem cobertura de garantia.\n");
    } else {
        printf("STATUS: Cadastro em conformidade.\n");
    }

    printf("--------------------------------------------------\n");
    printf("Ferramenta '%s' (QR: %u) cadastrada com sucesso!\n\n", nova.nome, nova.codigo_qr);
}

void consultar_ferramenta(const Ferramenta inventario[], int total) {
    if (total == 0) {
        printf("Aviso: Nenhuma ferramenta cadastrada no inventario.\n\n");
        return;
    }

    unsigned int codigo_busca = 0;
    printf("--- CONSULTA DE FERRAMENTA ---\n");
    printf("Digite o codigo QR para buscar: ");
    if (scanf("%u", &codigo_busca) != 1) {
        printf("ERRO: Entrada invalida! O codigo QR deve conter apenas digitos.\n\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    int encontrada = 0;
    for (int i = 0; i < total; i++) {
        if (inventario[i].codigo_qr == codigo_busca) {
            printf("\n==================================================\n");
            printf("            DADOS DA FERRAMENTA ENCONTRADA        \n");
            printf("==================================================\n");
            printf("Ferramenta: %s\n", inventario[i].nome);
            printf("QR Code: %u\n", inventario[i].codigo_qr);
            printf("Valor de compra: R$ %.2f\n", inventario[i].valor_compra);
            printf("Garantia: %s\n", inventario[i].possui_garantia == 1 ? "SIM" : "NAO");

            if (inventario[i].valor_compra > 1000.0f && inventario[i].possui_garantia == 0) {
                printf("STATUS: *** ALERTA DE ALTO RISCO FINANCEIRO ***\n");
                printf("Motivo: Equipamento de alto valor alocado sem cobertura de garantia.\n");
            } else {
                printf("STATUS: Cadastro em conformidade.\n");
            }
            printf("==================================================\n\n");
            encontrada = 1;
            break;
        }
    }

    if (!encontrada) {
        printf("Aviso: Ferramenta com Codigo QR %u nao encontrada no inventario.\n\n", codigo_busca);
    }
}

void exibir_relatorios(const Ferramenta inventario[], int total) {
    printf("==================================================\n");
    printf("          RELATORIOS FINANCEIROS E INVENTARIO     \n");
    printf("==================================================\n");
    printf("Total de ferramentas cadastradas: %d\n", total);

    if (total == 0) {
        printf("Valor total investido: R$ 0.00\n");
        printf("Media de valor das compras: R$ 0.00\n");
        printf("Nenhuma ferramenta cadastrada para analise de risco.\n");
        printf("==================================================\n\n");
        return;
    }

    float valor_total = 0.0f;
    int qtd_alto_risco = 0;

    for (int i = 0; i < total; i++) {
        valor_total += inventario[i].valor_compra;
    }

    float media_valor = valor_total / (float)total;

    printf("Valor total investido: R$ %.2f\n", valor_total);
    printf("Media de valor das compras: R$ %.2f\n", media_valor);
    printf("--------------------------------------------------\n");
    printf("LISTA DE ALTO RISCO (Valor > R$ 1000.00 sem garantia):\n");

    for (int i = 0; i < total; i++) {
        if (inventario[i].valor_compra > 1000.0f && inventario[i].possui_garantia == 0) {
            qtd_alto_risco++;
            printf("[%d] QR: %u | Nome: %-20s | Valor: R$ %8.2f\n",
                   qtd_alto_risco,
                   inventario[i].codigo_qr,
                   inventario[i].nome,
                   inventario[i].valor_compra);
        }
    }

    if (qtd_alto_risco > 0) {
        printf("\nSTATUS: *** ALERTA DE ALTO RISCO FINANCEIRO ***\n");
        printf("Total de ferramentas em risco: %d\n", qtd_alto_risco);
        printf("Motivo: Equipamento(s) de alto valor sem cobertura de garantia.\n");
    } else {
        printf("STATUS: Nenhuma ferramenta em situacao de alto risco financeiro.\n");
    }

    printf("==================================================\n\n");
}

int main(void) {
    Ferramenta inventario[MAX_FERRAMENTAS];
    int total_ferramentas = 0;
    int opcao_menu = 0;

    tela_carregamento();

    do {
        exibir_menu();

        if (scanf("%d", &opcao_menu) != 1) {
            limpar_buffer();
            opcao_menu = -1;
        } else {
            limpar_buffer();
        }

        system("clear"); /* No Windows: "cls" */

        switch (opcao_menu) {
            case 1:
                cadastrar_ferramenta(inventario, &total_ferramentas);
                break;

            case 2:
                consultar_ferramenta(inventario, total_ferramentas);
                break;

            case 3:
                exibir_relatorios(inventario, total_ferramentas);
                break;

            case 4:
                printf("Desconectando do banco de dados...\n");
                printf("Saindo do sistema. Ate logo!\n");
                break;

            default:
                printf("ERRO: Opcao invalida. Digite um numero de 1 a 4.\n\n");
                break;
        }

    } while (opcao_menu != 4);

    return 0;
}
