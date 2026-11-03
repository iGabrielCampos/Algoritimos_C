#include <stdio.h>

int main() {
    double divida, parcela, taxa;

    printf("=== Financiamento da Empilhadeira (FerraLog) ===\n");
    printf("Digite o valor da divida (ex: 50000): R$ ");
    scanf("%lf", &divida);

    printf("Digite o valor da parcela mensal fixa (ex: 2000): R$ ");
    scanf("%lf", &parcela);

    printf("Digite a taxa de juros mensal em %% (ex: 1 para 1%%): ");
    scanf("%lf", &taxa);

    // verificar se a parcela cobre os juros iniciais
    double juros_primeiro_mes = divida * (taxa / 100.0);

    if (parcela <= juros_primeiro_mes) {
        printf("\n[OPERACAO BARRADA]\n");
        printf("A parcela de R$ %.2f e menor ou igual aos juros do primeiro mes (R$ %.2f).\n", parcela, juros_primeiro_mes);
        printf("Nessas condicoes, a divida nunca sera quitada!\n");
        return 1;
    }

    int meses = 0;
    float anos = 0;
    while (divida > 0) {
        meses++;
        divida += divida * (taxa / 100.0); // acresce os juros sobre o saldo devedor
        divida -= parcela; // desconta a parcela paga
        if (meses % 12 == 0){
            anos++;
        }
    }

    printf("\nSucesso! A divida sera quitada em %d meses. (%.1f anos)\n", meses, anos);

    return 0;
}
