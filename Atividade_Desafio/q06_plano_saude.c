#include <stdio.h>

int main(void) {
    int idade = 0;
    int tem_doenca = 0;
    int qtd_doencas = 0;
    double taxa_basica = 0.0;
    double perc_adicional = 0.0;

    printf("==================================================\n");
    printf("              PLANO DE SAUDE - MENSALIDADE        \n");
    printf("==================================================\n");

    printf("Informe a idade: ");
    scanf("%d", &idade);

    if (idade < 0) {
        printf("\n[ERRO] Idade invalida!\n");
        return 1;
    }

    // faixas de idade e percentual de acrescimo por doenca
    if (idade <= 18) {
        taxa_basica = 83.15;
        perc_adicional = 0.00;
    } else if (idade <= 33) {
        taxa_basica = 133.88;
        perc_adicional = 0.05;
    } else if (idade <= 44) {
        taxa_basica = 203.73;
        perc_adicional = 0.10;
    } else if (idade <= 58) {
        taxa_basica = 312.44;
        perc_adicional = 0.15;
    } else {
        taxa_basica = 498.53;
        perc_adicional = 0.30;
    }

    printf("Possui alguma doenca cronica? (1 para SIM, 0 para NAO): ");
    scanf("%d", &tem_doenca);

    if (tem_doenca == 1) {
        printf("Informe a quantidade de doencas: ");
        scanf("%d", &qtd_doencas);

        if (qtd_doencas < 0) {
            qtd_doencas = 0;
        }
    }

    double valor_acrescimo = taxa_basica * (double)qtd_doencas * perc_adicional;
    double valor_total = taxa_basica + valor_acrescimo;

    printf("\n==================================================\n");
    printf("                 VALOR DA MENSALIDADE             \n");
    printf("==================================================\n");
    printf("Taxa basica:            R$ %.2lf\n", taxa_basica);
    printf("Acrescimo por doenca:   R$ %.2lf\n", valor_acrescimo);
    printf("--------------------------------------------------\n");
    printf("Total a pagar:          R$ %.2lf\n", valor_total);
    printf("==================================================\n");

    return 0;
}
