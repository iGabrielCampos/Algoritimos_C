#include <stdio.h>

int main() {
    // a sala começa em 22°C antes de iniciar o turno
    float temp_interna = 22.0f;
    float temp_externa;

    printf("=== Monitoramento do Servidor - FerraLog ===\n");
    printf("Temperatura interna inicial: %.1f C\n\n", temp_interna);

    // turno de trabalho: acompanhamos hora a hora, de 1 a 8
    for (int hora = 1; hora <= 8; hora++) {
        printf("--- Hora %d de 8 ---\n", hora);

        // pergunta quanto esta marcando os termometros la fora na rua
        printf("Digite a temperatura externa atual (C): ");
        scanf("%f", &temp_externa);

        // se na rua estiver um forno (acima de 30°C), a sala esquenta junto e sobe 2°C
        if (temp_externa > 30.0f) {
            temp_interna += 2.0f;
        }

        // o ar de emergencia entra em acao caso o calor aperte (28°C ou mais)
        // ele da aquele alivio imediato puxando a temperatura 5°C pra baixo
        int ar_emergencia_ligado = 0;
        if (temp_interna >= 28.0f) {
            ar_emergencia_ligado = 1;
            temp_interna -= 5.0f;
        }

        // limite de desastre: se passar de 35°C, os servidores vão derreterkk
        // interromppe o turno imediatamente com o break pra evitar o piorkkkk
        if (temp_interna >= 35.0f) {
            printf("\n=========================================\n");
            printf("[ALERTA CRITICO] Servidores derreteram!\n");
            printf("Temperatura interna atingiu %.1f C na hora %d!\n", temp_interna, hora);
            printf("=========================================\n");
            break; 
        }

        // resumo da hora para o operador acompanhar no painel
        printf("Temperatura interna resultante: %.1f C\n", temp_interna);
        if (ar_emergencia_ligado) {
            printf("Ar-condicionado de emergencia: LIGADO (reduziu 5 C)\n\n");
        } else {
            printf("Ar-condicionado de emergencia: DESLIGADO\n\n");
        }
    }

    return 0;
}
