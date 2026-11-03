#include <stdio.h>
#include <stdlib.h>

int main() {
    char nome_ferramenta[50];
    int codigo_qr;
    float valor_compra;

    printf("--- SISTEMA FERRALOG ---\n");
    
    printf("Nome da ferramenta: ");
    scanf("%s", nome_ferramenta); 
    
    printf("Codigo QR: ");
    scanf("%d", &codigo_qr);
    
    printf("Valor da compra: R$ ");
    scanf("%f", &valor_compra);

    system("cls"); 

    // O pulo do gato: Pesquisar e aplicar a condicional IF
    if (valor_compra > 0) {
        printf("--- RECIBO FERRALOG ---\n");
        printf("Ferramenta: %s\n", nome_ferramenta);
        printf("QR Code: %d\n", codigo_qr);
        printf("Valor: R$ %.2f\n", valor_compra);
    } else {
        // Se o valor for negativo ou zero, exibe o erro
