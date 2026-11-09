#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_FERRAMENTAS 50

typedef struct {
    char nome[50];
    int codigo_qr;
    float valor_compra;
    int possui_garantia; // 1 = sim, 0 = nao
} Ferramenta;

void limpar_buffer() {
    int c = getchar();
    while (c != '\n') {
        if (c == EOF) {
            break;
        }
        c = getchar();
    }
}

void remover_quebra_linha(char str[]) {
    int len = strlen(str);
    if (len > 0) {
        if (str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }
    }
}

void tela_carregamento() {
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

    system("clear");
}

void exibir_menu() {
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

int cadastrar_ferramenta(Ferramenta inventario[], int total) {
    if (total >= MAX_FERRAMENTAS) {
        printf("ERRO: Limite de armazenamento atingido (maximo de %d ferramentas).\n\n", MAX_FERRAMENTAS);
        return total;
    }

    Ferramenta nova;

    printf("--- MODULO DE CADASTRO ---\n");

    printf("Nome da ferramenta: ");
    fgets(nova.nome, 50, stdin);
    remover_quebra_linha(nova.nome);

    if (strlen(nova.nome) == 0) {
        printf("ERRO: O nome da ferramenta nao pode ser vazio.\n\n");
        return total;
    }

    printf("Codigo QR: ");
    if (scanf("%d", &nova.codigo_qr) != 1) {
        printf("ERRO: Codigo QR invalido! Digite apenas numeros inteiros.\n\n");
        limpar_buffer();
        return total;
    }
    limpar_buffer();

    for (int i = 0; i < total; i++) {
        if (inventario[i].codigo_qr == nova.codigo_qr) {
            printf("ERRO: Ja existe uma ferramenta cadastrada com o Codigo QR %d.\n\n", nova.codigo_qr);
            return total;
        }
    }

    printf("Valor da compra: R$ ");
    if (scanf("%f", &nova.valor_compra) != 1) {
        printf("ERRO: Entrada invalida para o valor da compra!\n\n");
        limpar_buffer();
        return total;
    }
    limpar_buffer();

    if (nova.valor_compra <= 0.0f) {
        printf("ERRO: O valor da compra deve ser maior que zero.\n\n");
        return total;
    }

    printf("Possui garantia? (1 para SIM, 0 para NAO): ");
    int leu_garantia = scanf("%d", &nova.possui_garantia);
    limpar_buffer();

    if (leu_garantia != 1) {
        printf("ERRO: Opcao invalida! Digite 1 para SIM ou 0 para NAO.\n\n");
        return total;
    }

    // so aceita 0 ou 1 como opcao
    if (nova.possui_garantia != 0) {
        if (nova.possui_garantia != 1) {
            printf("ERRO: Opcao invalida! Digite 1 para SIM ou 0 para NAO.\n\n");
            return total;
        }
    }

    inventario[total] = nova;
    total++;

    system("clear");

    printf("==================================================\n");
    printf("               --- RECIBO FERRALOG ---            \n");
    printf("==================================================\n");
    printf("Ferramenta: %s\n", nova.nome);
    printf("QR Code: %d\n", nova.codigo_qr);
    printf("Valor: R$ %.2f\n", nova.valor_compra);

    if (nova.possui_garantia == 1) {
        printf("Garantia: SIM\n");
    } else {
        printf("Garantia: NAO\n");
    }

    // alerta se a ferramenta custar mais de 1000 reais e estiver sem garantia
    int alto_risco = 0;
    if (nova.valor_compra > 1000.0f) {
        if (nova.possui_garantia == 0) {
            alto_risco = 1;
        }
    }

    if (alto_risco == 1) {
        printf("Status: ALERTA: Equipamento caro cadastrado sem garantia!\n");
    } else {
        printf("Status: Cadastro realizado com sucesso.\n");
    }

    printf("--------------------------------------------------\n");
    printf("Ferramenta '%s' (QR: %d) cadastrada com sucesso!\n\n", nova.nome, nova.codigo_qr);

    return total;
}

void consultar_ferramenta(Ferramenta inventario[], int total) {
    if (total == 0) {
        printf("Aviso: Nenhuma ferramenta cadastrada no inventario.\n\n");
        return;
    }

    int codigo_busca = 0;
    printf("--- CONSULTA DE FERRAMENTA ---\n");
    printf("Digite o codigo QR para buscar: ");
    if (scanf("%d", &codigo_busca) != 1) {
        printf("ERRO: Entrada invalida! Digite apenas numeros.\n\n");
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
            printf("QR Code: %d\n", inventario[i].codigo_qr);
            printf("Valor de compra: R$ %.2f\n", inventario[i].valor_compra);

            if (inventario[i].possui_garantia == 1) {
                printf("Garantia: SIM\n");
            } else {
                printf("Garantia: NAO\n");
            }

            // alerta se a ferramenta for cara e nao tiver garantia
            int alto_risco = 0;
            if (inventario[i].valor_compra > 1000.0f) {
                if (inventario[i].possui_garantia == 0) {
                    alto_risco = 1;
                }
            }

            if (alto_risco == 1) {
                printf("Status: ALERTA: Equipamento caro sem garantia!\n");
            } else {
                printf("Status: Sem pendencias de garantia.\n");
            }
            printf("==================================================\n\n");
            encontrada = 1;
            break;
        }
    }

    if (encontrada == 0) {
        printf("Aviso: Ferramenta com Codigo QR %d nao encontrada.\n\n", codigo_busca);
    }
}

void exibir_relatorios(Ferramenta inventario[], int total) {
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

    float media_valor = valor_total / total;

    printf("Valor total investido: R$ %.2f\n", valor_total);
    printf("Media de valor das compras: R$ %.2f\n", media_valor);
    printf("--------------------------------------------------\n");
    printf("LISTA DE ALTO RISCO (Valor > R$ 1000.00 sem garantia):\n");

    for (int i = 0; i < total; i++) {
        // filtra as ferramentas acima de 1000 sem garantia
        if (inventario[i].valor_compra > 1000.0f) {
            if (inventario[i].possui_garantia == 0) {
                qtd_alto_risco++;
                printf("[%d] QR: %d | Nome: %s | Valor: R$ %.2f\n",
                       qtd_alto_risco,
                       inventario[i].codigo_qr,
                       inventario[i].nome,
                       inventario[i].valor_compra);
            }
        }
    }

    if (qtd_alto_risco > 0) {
        printf("\nALERTA: Total de ferramentas caras sem garantia: %d\n", qtd_alto_risco);
    } else {
        printf("\nStatus: Nenhuma ferramenta cara sem garantia no inventario.\n");
    }

    printf("==================================================\n\n");
}

int main() {
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

        system("clear");

        switch (opcao_menu) {
            case 1:
                total_ferramentas = cadastrar_ferramenta(inventario, total_ferramentas);
                break;

            case 2:
                consultar_ferramenta(inventario, total_ferramentas);
                break;

            case 3:
                exibir_relatorios(inventario, total_ferramentas);
                break;

            case 4:
                printf("Salvando dados...\n");
                printf("Saindo do sistema. Ate logo!\n");
                break;

            default:
                printf("ERRO: Opcao invalida. Digite um numero de 1 a 4.\n\n");
                break;
        }

    } while (opcao_menu != 4);

    return 0;
}
