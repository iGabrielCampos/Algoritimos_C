#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_MEMBROS 4
#define META_LEGUAS 100.0f

/* --- ESTRUTURAS DE DADOS (Inspiradas no padrao FerraLog e atividades) --- */

typedef enum {
    ESTADO_SAUDAVEL = 0,
    ESTADO_SEDE = 1,
    ESTADO_FEBRE = 2,
    ESTADO_PICADA_COBRA = 3,
    ESTADO_FALECIDO = 4
} EstadoSaude;

typedef struct {
    char nome[40];
    char papel[50];
    int saude;        // 0 a 100
    EstadoSaude estado;
    int vivo;         // 1 = vivo, 0 = falecido
} Membro;

typedef struct {
    int dia;
    float leguas_andadas;
    float temperatura_ambiente; // inspirada no Termostato.c
    int clima_hoje;             // 1=Sol escaldante, 2=Quente, 3=Ameno, 4=Chuva abencoada
    
    // Mantimentos e recursos
    float agua_litros;
    float rapadura_kg;
    int mezinhas;               // Garrafadas medicinais
    int fumo_rolo;              // Moeda de troca com sertanejos e cangaço
    int dinheiro_reis;          // Moeda da epoca (reis)
    
    // Animal de transporte
    int condicao_jumento;       // 0 a 100% de saude do jumento Faisca
    int jumento_vivo;           // 1 = vivo, 0 = perdido/falecido
    
    // Pessoas
    Membro familia[MAX_MEMBROS];
    int total_vivos;
    
    // Controle de marcos de vilarejos ja visitados
    int vila_25_visitada;
    int vila_50_visitada;
    int vila_75_visitada;
} Caravana;

/* --- FUNCOES UTILITARIAS DE ENTRADA E TELA --- */

void dormir(int s) {
    if (isatty(STDIN_FILENO)) {
        sleep(s);
    }
}

void limpar_buffer(void) {
    int c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

void pausar_tela(void) {
    if (feof(stdin)) return;
    printf("\n[Pressione ENTER para continuar...]");
    limpar_buffer();
}

void cabecalho(void) {
    printf("======================================================================\n");
    printf("        SERTÃO TRAIL: A MARCHA DOS RETIRANTES DA CAATINGA             \n");
    printf("======================================================================\n");
}

const char* descrever_clima(int clima) {
    switch (clima) {
        case 1: return "Sol de Rachar Juazeiro (Calor Extremo)";
        case 2: return "Mormaço Abafado e Seco";
        case 3: return "Vento Manso da Tarde (Ameno)";
        case 4: return "Chuva Abençoada de Relâmpago";
        default: return "Seca Braba";
    }
}

const char* descrever_estado(EstadoSaude estado) {
    switch (estado) {
        case ESTADO_SAUDAVEL: return "Disposto";
        case ESTADO_SEDE: return "Sedento";
        case ESTADO_FEBRE: return "Febre da Seca";
        case ESTADO_PICADA_COBRA: return "Picada de Cascavel";
        case ESTADO_FALECIDO: return "Falecido (Descansa em Deus)";
        default: return "Incerto";
    }
}

/* --- INICIALIZACAO DA CARAVANA --- */

void inicializar_caravana(Caravana *c) {
    c->dia = 1;
    c->leguas_andadas = 0.0f;
    c->temperatura_ambiente = 33.0f;
    c->clima_hoje = 2;
    
    c->agua_litros = 20.0f;
    c->rapadura_kg = 15.0f;
    c->mezinhas = 2;
    c->fumo_rolo = 3;
    c->dinheiro_reis = 4500; // 4 mil e 500 réis
    
    c->condicao_jumento = 100;
    c->jumento_vivo = 1;
    c->total_vivos = 4;
    
    c->vila_25_visitada = 0;
    c->vila_50_visitada = 0;
    c->vila_75_visitada = 0;

    // Familia de retirantes
    strcpy(c->familia[0].nome, "Severino");
    strcpy(c->familia[0].papel, "Pai de Família");
    c->familia[0].saude = 100;
    c->familia[0].estado = ESTADO_SAUDAVEL;
    c->familia[0].vivo = 1;

    strcpy(c->familia[1].nome, "Sinhá Maria");
    strcpy(c->familia[1].papel, "Mãe e Guardiã");
    c->familia[1].saude = 95;
    c->familia[1].estado = ESTADO_SAUDAVEL;
    c->familia[1].vivo = 1;

    strcpy(c->familia[2].nome, "Zé Pequeno");
    strcpy(c->familia[2].papel, "Filho Menino");
    c->familia[2].saude = 90;
    c->familia[2].estado = ESTADO_SAUDAVEL;
    c->familia[2].vivo = 1;

    strcpy(c->familia[3].nome, "Vô Chico");
    strcpy(c->familia[3].papel, "Ancião Contador de Histórias");
    c->familia[3].saude = 80;
    c->familia[3].estado = ESTADO_SAUDAVEL;
    c->familia[3].vivo = 1;
}

/* --- RELATORIO E PAINEL DA CARAVANA --- */

void exibir_painel(const Caravana *c) {
    system("clear");
    cabecalho();
    printf("📅 DIA %d | 🗺️  LÉGUAS: %.1f / %.1f (Faltam %.1f léguas)\n",
           c->dia, c->leguas_andadas, META_LEGUAS,
           (META_LEGUAS - c->leguas_andadas > 0) ? (META_LEGUAS - c->leguas_andadas) : 0.0f);
    printf("☀️  Temperatura: %.1f °C | Tempo: %s\n", c->temperatura_ambiente, descrever_clima(c->clima_hoje));
    printf("----------------------------------------------------------------------\n");
    printf("ALFORJE & RECURSOS:\n");
    printf("  💧 Água Fresca: %.1f L  |  🍬 Rapadura: %.1f kg  |  🌿 Mezinhas: %d frascos\n",
           c->agua_litros, c->rapadura_kg, c->mezinhas);
    printf("  🍂 Fumo de Rolo: %d rolos |  💰 Moedas: %d réis     |  🫏 Jumento Faísca: %d%% %s\n",
           c->fumo_rolo, c->dinheiro_reis,
           c->jumento_vivo ? c->condicao_jumento : 0,
           c->jumento_vivo ? "(Firme no passo)" : "(Perdido na caatinga)");
    printf("----------------------------------------------------------------------\n");
    printf("ESTADO DA FAMÍLIA:\n");
    for (int i = 0; i < MAX_MEMBROS; i++) {
        if (c->familia[i].vivo) {
            printf("  [%d] %-14s (%-30s) : Saúde: %3d/100 | Condição: %s\n",
                   i + 1,
                   c->familia[i].nome,
                   c->familia[i].papel,
                   c->familia[i].saude,
                   descrever_estado(c->familia[i].estado));
        } else {
            printf("  [X] %-14s (%-30s) : [FALECIDO NA ESTRADA]\n",
                   c->familia[i].nome,
                   c->familia[i].papel);
        }
    }
    printf("======================================================================\n");
}

/* --- LOGICA DIARIA DE CLIMA E CONSUMO (Inspirada no Termostato e Empilhadeira) --- */

void atualizar_clima_e_temperatura(Caravana *c) {
    int r = rand() % 100;
    if (r < 25) {
        c->clima_hoje = 1; // Sol escaldante
        c->temperatura_ambiente = 38.0f + (float)(rand() % 50) / 10.0f; // 38.0 a 42.9 °C
    } else if (r < 70) {
        c->clima_hoje = 2; // Mormaço
        c->temperatura_ambiente = 32.0f + (float)(rand() % 50) / 10.0f; // 32.0 a 36.9 °C
    } else if (r < 90) {
        c->clima_hoje = 3; // Ameno
        c->temperatura_ambiente = 27.0f + (float)(rand() % 40) / 10.0f; // 27.0 a 30.9 °C
    } else {
        c->clima_hoje = 4; // Chuva
        c->temperatura_ambiente = 24.0f + (float)(rand() % 30) / 10.0f; // 24.0 a 26.9 °C
    }
}

void consumir_recursos_diarios(Caravana *c, int fator_esforco) {
    if (c->total_vivos <= 0) return;

    // Consumo de agua depende do clima e do esforco da marcha
    float consumo_base_agua_por_pessoa = 1.0f;
    if (c->clima_hoje == 1) { // Calor escaldante
        consumo_base_agua_por_pessoa += 0.8f;
    } else if (c->clima_hoje == 4) { // Chuva passageira: coleta um pouco de agua!
        c->agua_litros += 3.5f;
        printf("\n🌧️  A chuva de relâmpago encheu as cuias e potes! (+3.5 L de água colhida)\n");
    }

    if (fator_esforco == 3) { // Passo forçado
        consumo_base_agua_por_pessoa += 0.5f;
    } else if (fator_esforco == 0) { // Descanso
        consumo_base_agua_por_pessoa -= 0.3f;
    }

    float agua_necessaria = c->total_vivos * consumo_base_agua_por_pessoa;
    if (c->jumento_vivo) {
        agua_necessaria += 2.0f; // Jumento bebe agua
    }

    float comida_necessaria = c->total_vivos * 0.5f; // Meio quilo de rapadura por pessoa

    // Descontar agua
    if (c->agua_litros >= agua_necessaria) {
        c->agua_litros -= agua_necessaria;
    } else {
        float deficit = agua_necessaria - c->agua_litros;
        c->agua_litros = 0.0f;
        printf("\n⚠️  ALERTA CRÍTICO: Falta de água no sertão! Faltaram %.1f L para a caravana.\n", deficit);
        // Pessoas sofrem desidratacao
        for (int i = 0; i < MAX_MEMBROS; i++) {
            if (c->familia[i].vivo) {
                c->familia[i].saude -= 15;
                if (c->familia[i].estado == ESTADO_SAUDAVEL) {
                    c->familia[i].estado = ESTADO_SEDE;
                }
            }
        }
        if (c->jumento_vivo) {
            c->condicao_jumento -= 20;
        }
    }

    // Descontar comida
    if (c->rapadura_kg >= comida_necessaria) {
        c->rapadura_kg -= comida_necessaria;
    } else {
        c->rapadura_kg = 0.0f;
        printf("⚠️  A rapadura acabou! A família passou o dia com o estômago roncando.\n");
        for (int i = 0; i < MAX_MEMBROS; i++) {
            if (c->familia[i].vivo) {
                c->familia[i].saude -= 10;
            }
        }
    }

    // Impacto de doencas ativas
    for (int i = 0; i < MAX_MEMBROS; i++) {
        if (!c->familia[i].vivo) continue;

        if (c->familia[i].estado == ESTADO_FEBRE) {
            c->familia[i].saude -= 10;
            printf("🤒 %s treme de febre alta provocada pelo sol e poeira.\n", c->familia[i].nome);
        } else if (c->familia[i].estado == ESTADO_PICADA_COBRA) {
            c->familia[i].saude -= 20;
            printf("🐍 O veneno da cascavel ainda queima nas veias de %s!\n", c->familia[i].nome);
        }

        // Checar morte
        if (c->familia[i].saude <= 0) {
            c->familia[i].saude = 0;
            c->familia[i].vivo = 0;
            c->familia[i].estado = ESTADO_FALECIDO;
            c->total_vivos--;
            printf("\n✝️  LUTO NO SERTÃO: Com pesar na alma, %s não resistiu e descansou.\n", c->familia[i].nome);
            printf("   Severino fincou uma cruz de mandacaru na beira da estrada...\n");
        }
    }

    // Checar condicao do jumento
    if (c->jumento_vivo && c->condicao_jumento <= 0) {
        c->jumento_vivo = 0;
        c->condicao_jumento = 0;
        printf("\n🫏 O fiel jumento Faísca dobrou os joelhos e não levantou mais.\n");
        printf("   A família teve que deixar parte dos trastes e carregar o fardo nas costas!\n");
        if (c->agua_litros > 15.0f) c->agua_litros = 15.0f;
        if (c->rapadura_kg > 10.0f) c->rapadura_kg = 10.0f;
    }
}

/* --- EVENTOS ALEATORIOS DA CAATINGA --- */

void disparar_evento_aleatorio(Caravana *c) {
    if (c->total_vivos <= 0 || !c->familia[0].vivo) return;

    int chance = rand() % 100;
    // 40% de chance de ocorrer evento na marcha
    if (chance > 40) return;

    int tipo = rand() % 6;
    printf("\n------------------- [ ACONTECIMENTO NA VEREDA ] -------------------\n");

    switch (tipo) {
        case 0: { // Encontro com o Bando de Cangaceiros
            printf("🌵 Três cavaleiros armados de bacamarte e punhal surgem por entre as juremas!\n");
            printf("   É o Bando do Capitão Sabiá, cobrando pedágio de quem cruza a caatinga.\n");
            if (c->fumo_rolo > 0) {
                c->fumo_rolo--;
                printf("   Severino ofereceu um generoso rolo de fumo de Arapiraca.\n");
                printf("   'Gostei do respeito, cabra bom. Que Padre Cícero vos acompanhe!'\n");
                printf("   O bando seguiu em paz (-1 rolo de fumo).\n");
            } else if (c->dinheiro_reis >= 1000) {
                c->dinheiro_reis -= 1000;
                printf("   Sem fumo, Severino teve que abrir a algibeira e pagar 1000 réis de salvo-conduto.\n");
            } else if (c->rapadura_kg >= 2.0f) {
                c->rapadura_kg -= 2.0f;
                printf("   Sem fumo nem réis, o bando levou 2 rapaduras para a merenda da tropa.\n");
            } else {
                printf("   Vendo que eram retirantes na mais pura penúria, o Capitão se apiedou:\n");
                printf("   'Sigam com Deus, retirantes. A fome de vocês já é castigo bastante.'\n");
            }
            break;
        }
        case 1: { // Olho d'agua ou cacimba na serra
            float agua_achada = 6.0f + (float)(rand() % 7);
            c->agua_litros += agua_achada;
            printf("💧 MILAGRE: Vô Chico avistou um olho d'água vertendo numa grota de pedras!\n");
            printf("   A caravana encheu os cantis com %.1f litros de água pura e cristalina!\n", agua_achada);
            break;
        }
        case 2: { // Cobra cascavel
            int vivos_indices[MAX_MEMBROS];
            int n_vivos = 0;
            for (int i = 0; i < MAX_MEMBROS; i++) {
                if (c->familia[i].vivo) {
                    vivos_indices[n_vivos++] = i;
                }
            }
            if (n_vivos == 0) break;

            int alvo = vivos_indices[rand() % n_vivos];
            printf("🐍 Zzzzzzz... Uma cascavel estava enrodilhada sob a touceira de macambira!\n");
            printf("   A cobra deu o bote na perna de %s!\n", c->familia[alvo].nome);
            c->familia[alvo].estado = ESTADO_PICADA_COBRA;
            c->familia[alvo].saude -= 15;
            printf("   A pele inchou ligeiro. É preciso aplicar uma mezinha urgente!\n");

            if (c->familia[alvo].saude <= 0) {
                c->familia[alvo].saude = 0;
                c->familia[alvo].vivo = 0;
                c->familia[alvo].estado = ESTADO_FALECIDO;
                c->total_vivos--;
                printf("\n✝️  LUTO NO SERTÃO: O veneno agiu rápido demais e %s descansou em Deus.\n", c->familia[alvo].nome);
            }
            break;
        }
        case 3: { // Encontro com outros retirantes solidarios
            printf("👥 Um comboio de retirantes de Canudos cruzou a mesma vereda empoeirada.\n");
            printf("   Sentaram-se ao redor da fogueira para trocar prosas e rezas.\n");
            if (c->mezinhas == 0 && c->rapadura_kg >= 3.0f) {
                c->rapadura_kg -= 2.0f;
                c->mezinhas += 1;
                printf("   Uma rezadeira trocou uma garrafada de ervas por 2 kg de rapadura.\n");
            } else {
                printf("   As palavras de esperança renovaram o ânimo de todos (+10 de saúde geral).\n");
                for (int i = 0; i < MAX_MEMBROS; i++) {
                    if (c->familia[i].vivo && c->familia[i].saude < 90) {
                        c->familia[i].saude += 10;
                    }
                }
            }
            break;
        }
        case 4: { // Jumento Faisca empaca ou espeta o casco
            if (c->jumento_vivo) {
                printf("🫏 Faísca pisou num espinho de jurema-preta e empacou rinchando!\n");
                printf("   Severino e Zé Pequeno tiveram que parar para tirar o estrepe com a ponta da peixeira.\n");
                c->condicao_jumento -= 15;
                if (c->condicao_jumento < 0) c->condicao_jumento = 0;
                printf("   O animal perdeu 15%% de firmeza, mas segue viagem.\n");
            } else {
                printf("🌪️ Um redemoinho de poeira e cinzas cegou a caravana por horas!\n");
            }
            break;
        }
        case 5: { // Cacto Coroa-de-Frade e Mandacaru
            printf("🌵 Vô Chico ensina a família a descascar o coração de uma coroa-de-frade.\n");
            printf("   A polpa suculenta amenizou a sede e deu sustança (+3.0 L de água, +1.5 kg rapadura).\n");
            c->agua_litros += 3.0f;
            c->rapadura_kg += 1.5f;
            break;
        }
    }
    printf("-------------------------------------------------------------------\n");
}

/* --- VILAREJOS E FEIRAS LIVRES (Comercio com Reis) --- */

void visitar_feira_livre(Caravana *c, const char *nome_vila) {
    int opcao = 0;
    do {
        system("clear");
        cabecalho();
        printf("🏛️  CHEGADA AO POVOADO: %s\n", nome_vila);
        printf("   A agitação dos tropeiros, cheiro de fumo, queijo e carne de sol trazem alívio.\n");
        printf("----------------------------------------------------------------------\n");
        printf("Seus Recursos: 💰 %d réis  |  💧 %.1f L Água  |  🍬 %.1f kg Rapadura  |  🌿 %d Mezinhas  |  🍂 %d Fumos\n",
               c->dinheiro_reis, c->agua_litros, c->rapadura_kg, c->mezinhas, c->fumo_rolo);
        printf("----------------------------------------------------------------------\n");
        printf("COMPRAS NA FEIRA:\n");
        printf("[1] Encher 10 Litros de água fresca de cacimba ........ 300 réis\n");
        printf("[2] Fardo de 5 kg de rapadura tijolo ................. 400 réis\n");
        printf("[3] Garrafada medicinal da rezadeira (Mezinha) ....... 600 réis\n");
        printf("[4] Rolo de fumo forte de Arapiraca .................. 350 réis\n");
        printf("[5] Ferradura nova e trato no jumento Faísca ......... 500 réis\n");
        printf("[6] Hospedagem em rancho coberto (Noite segura) ...... 800 réis (+20 saúde da família)\n");
        printf("----------------------------------------------------------------------\n");
        printf("VENDAS E TROCAS:\n");
        printf("[7] Vender 1 rolo de fumo de Arapiraca ............... Ganha +250 réis\n");
        printf("[8] Vender 2 kg de rapadura ou carne de caça ......... Ganha +180 réis\n");
        printf("[9] Encerrar as compras e seguir marcha na estrada\n");
        printf("======================================================================\n");
        printf("Escolha uma opção: ");

        int leu = scanf("%d", &opcao);
        if (leu == EOF || feof(stdin)) {
            break;
        }
        if (leu != 1) {
            limpar_buffer();
            opcao = 0;
            continue;
        }
        limpar_buffer();

        switch (opcao) {
            case 1:
                if (c->dinheiro_reis >= 300) {
                    c->dinheiro_reis -= 300;
                    c->agua_litros += 10.0f;
                    printf("\n✔️  Cantis e ancoretas cheios com água limpa! (+10 L)\n");
                } else {
                    printf("\n❌ Dinheiro insuficiente em réis!\n");
                }
                pausar_tela();
                break;
            case 2:
                if (c->dinheiro_reis >= 400) {
                    c->dinheiro_reis -= 400;
                    c->rapadura_kg += 5.0f;
                    printf("\n✔️  Rapadura guardada no alforje do jumento! (+5 kg)\n");
                } else {
                    printf("\n❌ Dinheiro insuficiente em réis!\n");
                }
                pausar_tela();
                break;
            case 3:
                if (c->dinheiro_reis >= 600) {
                    c->dinheiro_reis -= 600;
                    c->mezinhas += 1;
                    printf("\n✔️  Frasco de garrafada com cascas de aroeira e jatobá adquirido! (+1 mezinha)\n");
                } else {
                    printf("\n❌ Dinheiro insuficiente em réis!\n");
                }
                pausar_tela();
                break;
            case 4:
                if (c->dinheiro_reis >= 350) {
                    c->dinheiro_reis -= 350;
                    c->fumo_rolo += 1;
                    printf("\n✔️  Fumo cheiroso de rolo adquirido! (+1 fumo)\n");
                } else {
                    printf("\n❌ Dinheiro insuficiente em réis!\n");
                }
                pausar_tela();
                break;
            case 5:
                if (!c->jumento_vivo) {
                    printf("\n❌ O jumento Faísca já não está mais com a caravana.\n");
                } else if (c->dinheiro_reis >= 500) {
                    c->dinheiro_reis -= 500;
                    c->condicao_jumento = 100;
                    printf("\n✔️  O ferreiro cravou ferraduras novas e Faísca comeu milho graúdo! (Condição: 100%%)\n");
                } else {
                    printf("\n❌ Dinheiro insuficiente em réis!\n");
                }
                pausar_tela();
                break;
            case 6:
                if (c->dinheiro_reis >= 800) {
                    c->dinheiro_reis -= 800;
                    for (int i = 0; i < MAX_MEMBROS; i++) {
                        if (c->familia[i].vivo) {
                            c->familia[i].saude += 20;
                            if (c->familia[i].saude > 100) c->familia[i].saude = 100;
                            c->familia[i].estado = ESTADO_SAUDAVEL;
                        }
                    }
                    printf("\n✔️  Uma noite de sono sob telhas de barro e banho de ervas curou enfermidades e restaurou as forças!\n");
                } else {
                    printf("\n❌ Dinheiro insuficiente em réis!\n");
                }
                pausar_tela();
                break;
            case 7:
                if (c->fumo_rolo > 0) {
                    c->fumo_rolo--;
                    c->dinheiro_reis += 250;
                    printf("\n✔️  Você vendeu 1 rolo de fumo e recebeu 250 réis!\n");
                } else {
                    printf("\n❌ Você não tem fumo de rolo para vender.\n");
                }
                pausar_tela();
                break;
            case 8:
                if (c->rapadura_kg >= 2.0f) {
                    c->rapadura_kg -= 2.0f;
                    c->dinheiro_reis += 180;
                    printf("\n✔️  Você vendeu 2 kg de provisões e recebeu 180 réis!\n");
                } else {
                    printf("\n❌ Você não tem alimento suficiente para vender.\n");
                }
                pausar_tela();
                break;
            case 9:
                printf("\nA caravana se despede dos feirantes e retoma a poeira da estrada...\n");
                dormir(1);
                break;
            default:
                printf("\nOpção inválida. Digite de 1 a 9.\n");
                pausar_tela();
                break;
        }
    } while (opcao != 9);
}

void verificar_marcos_estrada(Caravana *c) {
    if (c->total_vivos <= 0 || !c->familia[0].vivo) return;

    if (c->leguas_andadas >= 25.0f && !c->vila_25_visitada) {
        c->vila_25_visitada = 1;
        printf("\n🔔 MARCO ALCANÇADO: Chegada à Vila de Teixeira (25 léguas percorridas)!\n");
        pausar_tela();
        visitar_feira_livre(c, "Feira da Vila de Teixeira");
    } else if (c->leguas_andadas >= 50.0f && !c->vila_50_visitada) {
        c->vila_50_visitada = 1;
        printf("\n🔔 MARCO ALCANÇADO: Chegada à Cidade de Patos (Meio do caminho - 50 léguas)!\n");
        pausar_tela();
        visitar_feira_livre(c, "Grande Feira Livre de Patos");
    } else if (c->leguas_andadas >= 75.0f && !c->vila_75_visitada) {
        c->vila_75_visitada = 1;
        printf("\n🔔 MARCO ALCANÇADO: Chegada a Campina Grande (Portão do Brejo - 75 léguas)!\n");
        pausar_tela();
        visitar_feira_livre(c, "Feira Central dos Tropeiros de Campina Grande");
    }
}

/* --- ACOES DO JOGADOR --- */

void acao_marchar(Caravana *c) {
    int ritmo = 0;
    printf("\nEscolha o ritmo da marcha para hoje:\n");
    printf("[1] Passo Manso   (~2.0 léguas) - Pouco cansaço, preserva o fôlego e o jumento\n");
    printf("[2] Passo Normal  (~4.0 léguas) - Marcha equilibrada de sol a sol\n");
    printf("[3] Passo Forçado (~6.5 léguas) - Cruzar o lombo da seca a galope (Alto desgaste)\n");
    printf("[4] Voltar ao acampamento (Cancelar marcha)\n");
    printf("Escolha: ");

    int leu_ritmo = scanf("%d", &ritmo);
    if (leu_ritmo == EOF || feof(stdin)) return;
    if (leu_ritmo != 1) {
        limpar_buffer();
        ritmo = 2; // padrao
    } else {
        limpar_buffer();
    }

    if (ritmo == 4) {
        printf("\nSeverino decidiu esperar mais um pouco no acampamento antes de marchar.\n");
        dormir(1);
        return;
    }

    float distancia = 0.0f;
    int desgaste_jumento = 0;

    switch (ritmo) {
        case 1:
            distancia = 1.8f + (float)(rand() % 8) / 10.0f; // 1.8 a 2.5
            desgaste_jumento = 2;
            break;
        case 3:
            distancia = 5.5f + (float)(rand() % 15) / 10.0f; // 5.5 a 6.9
            desgaste_jumento = 12;
            break;
        case 2:
        default:
            ritmo = 2;
            distancia = 3.5f + (float)(rand() % 12) / 10.0f; // 3.5 a 4.6
            desgaste_jumento = 6;
            break;
    }

    if (!c->jumento_vivo) {
        distancia *= 0.65f;
        printf("\nSem o jumento Faísca, a família avança pesada carregando os sacos nos ombros...\n");
    } else {
        c->condicao_jumento -= desgaste_jumento;
        if (c->condicao_jumento < 0) c->condicao_jumento = 0;
    }

    c->leguas_andadas += distancia;
    printf("\n🚶 A caravana marchou com determinação e venceu %.1f léguas hoje!\n", distancia);

    consumir_recursos_diarios(c, ritmo);
    if (c->total_vivos > 0 && c->familia[0].vivo) {
        disparar_evento_aleatorio(c);
        verificar_marcos_estrada(c);
    }
    c->dia++;
    atualizar_clima_e_temperatura(c);
    pausar_tela();
}

void acao_descansar(Caravana *c) {
    printf("\nSeverino avistou a copa copada de um juazeiro verdejante.\n");
    printf("A caravana arriou os sacos para descansar o corpo e proteger a moleira do sol.\n");

    for (int i = 0; i < MAX_MEMBROS; i++) {
        if (c->familia[i].vivo) {
            c->familia[i].saude += 15;
            if (c->familia[i].saude > 100) c->familia[i].saude = 100;
            if (c->familia[i].estado == ESTADO_SEDE && c->agua_litros > 0.0f) {
                c->familia[i].estado = ESTADO_SAUDAVEL;
            } else if (c->familia[i].estado == ESTADO_FEBRE && (rand() % 100 < 40)) {
                c->familia[i].estado = ESTADO_SAUDAVEL;
                printf("🌿 O repouso à sombra do juazeiro fez a febre de %s baixar!\n", c->familia[i].nome);
            }
        }
    }

    if (c->jumento_vivo) {
        c->condicao_jumento += 15;
        if (c->condicao_jumento > 100) c->condicao_jumento = 100;
        printf("Faísca pastou capim seco na sombra e recuperou o fôlego (+15%%).\n");
    }

    consumir_recursos_diarios(c, 0); // esforco 0 = descanso
    c->dia++;
    atualizar_clima_e_temperatura(c);
    pausar_tela();
}

/* --- EXPLORACAO DA CAATINGA (AGUA E COMIDA) --- */

void acao_procurar_recursos(Caravana *c) {
    int opcao_busca = 0;
    printf("\n======================================================================\n");
    printf("            EXPLORAÇÃO DA CAATINGA - PROCURAR RECURSOS                \n");
    printf("======================================================================\n");
    printf("Severino conhece as manhas da terra seca. O que a caravana vai priorizar?\n\n");
    printf("[1] Procurar fontes de ÁGUA (Cacimbas de rio seco, raízes de umbuzeiro)\n");
    printf("[2] Caçar para obter ALIMENTO (Preá na loca, tatu, arribações)\n");
    printf("[3] Coleta geral balanceada (Cactos, mandacaru, xique-xique e frutos)\n");
    printf("[4] Voltar ao acampamento (Cancelar expedição)\n");
    printf("======================================================================\n");
    printf("Escolha o foco da busca: ");

    int leu_busca = scanf("%d", &opcao_busca);
    if (leu_busca == EOF || feof(stdin)) return;
    if (leu_busca != 1) {
        limpar_buffer();
        opcao_busca = 4;
    } else {
        limpar_buffer();
    }

    if (opcao_busca == 4) {
        printf("\nSeverino decidiu não arriscar a família nos carrascais hoje.\n");
        dormir(1);
        return;
    }

    printf("\nSeverino e a comitiva entram nas veredas da caatinga brava...\n");
    dormir(1);

    float agua_encontrada = 0.0f;
    float comida_encontrada = 0.0f;
    int sorte = rand() % 100;

    if (opcao_busca == 1) { // FOCO EXCLUSIVO EM AGUA
        if (sorte < 40) { // Cacimba viva em leito seco
            agua_encontrada = 14.0f + (float)(rand() % 9); // 14.0 a 22.0 L
            printf("💧 SUCESSO BENTO! Cavando a areia branca de um rio seco, acharam uma CACIMBA VIVA!\n");
            printf("   Água límpida e fresca brotou da pedra! Encheram os potes e ancoretas (+%.1f L)!\n", agua_encontrada);
        } else if (sorte < 85) { // Raizes de umbuzeiro ("batatas d'agua")
            agua_encontrada = 9.0f + (float)(rand() % 6); // 9.0 a 14.0 L
            printf("🌳 SAGRADO UMBUZEIRO! Cavando ao redor do tronco, desenterraram batatas d'água cheias de suco doce!\n");
            printf("   A família matou a sede e guardou muita água (+%.1f L)!\n", agua_encontrada);
        } else { // Pouco achado
            agua_encontrada = 3.0f + (float)(rand() % 3); // 3.0 a 5.0 L
            printf("🌵 O sol tostou quase tudo. Só conseguiram extrair seiva de cardeiros espinhosos (+%.1f L).\n", agua_encontrada);
        }
    } else if (opcao_busca == 2) { // FOCO EM CACA / ALIMENTO
        if (sorte < 50) { // Prea e tatu
            comida_encontrada = 4.5f + (float)(rand() % 4); // 4.5 a 7.5 kg
            printf("🎯 TIRO CERTEIRO! Pegaram um tatu-bola gordo e três preás nas locas de pedra (+%.1f kg)!\n", comida_encontrada);
            printf("   Hoje haverá carne assada no espeto de jurema!\n");
        } else if (sorte < 85) { // Arribações
            comida_encontrada = 3.0f + (float)(rand() % 3); // 3.0 a 5.0 kg
            printf("🕊️ Um bando de arribações pousou no juazeiro. Severino armou arapucas e colheu caça (+%.1f kg)!\n", comida_encontrada);
        } else { // Pouca caca
            comida_encontrada = 1.0f + (float)(rand() % 2); // 1.0 a 2.0 kg
            printf("🍂 A bimarada sumiu com o calor. Apenas um mocó magro foi apanhado (+%.1f kg).\n", comida_encontrada);
        }
    } else { // COLETA BALANCEADA
        agua_encontrada = 6.0f + (float)(rand() % 6);   // 6.0 a 11.0 L
        comida_encontrada = 2.5f + (float)(rand() % 3); // 2.5 a 4.5 kg
        printf("🌵 COLHEITA SERTANEJA: Cortaram palmas de mandacaru e apanharam juás maduros!\n");
        printf("   Garantiram água fresca (+%.1f L) e sustança para o alforje (+%.1f kg)!\n", agua_encontrada, comida_encontrada);
    }

    // Adiciona o que foi encontrado
    c->agua_litros += agua_encontrada;
    c->rapadura_kg += comida_encontrada;

    // Consumo diario: como beberam e comeram na expedicao, o consumo do dia e mais brando
    float agua_consumida = (c->total_vivos * 0.8f) + (c->jumento_vivo ? 1.5f : 0.0f);
    float comida_consumida = (opcao_busca == 2) ? 0.0f : (c->total_vivos * 0.4f); // Se cacou, carne ja cobre a fome

    printf("\n--- BALANÇO DO DIA DE EXPEDIÇÃO ---\n");
    if (agua_encontrada > 0.0f) {
        printf("💧 Água encontrada: +%.1f L | Consumida pela caravana: -%.1f L\n", agua_encontrada, agua_consumida);
        float saldo_agua = agua_encontrada - agua_consumida;
        if (saldo_agua >= 0) {
            printf("⭐ SALDO LÍQUIDO POSITIVO: +%.1f Litros de água fresca guardados no alforje!\n", saldo_agua);
        } else {
            printf("⚠️ Saldo líquido: %.1f L (Consumo superou a coleta sob calor forte).\n", saldo_agua);
        }
    }
    if (comida_encontrada > 0.0f) {
        printf("🍬 Alimento obtido: +%.1f kg | Consumido hoje: -%.1f kg\n", comida_encontrada, comida_consumida);
    }

    if (c->agua_litros >= agua_consumida) {
        c->agua_litros -= agua_consumida;
    } else {
        c->agua_litros = 0.0f;
    }

    if (c->rapadura_kg >= comida_consumida) {
        c->rapadura_kg -= comida_consumida;
    } else {
        c->rapadura_kg = 0.0f;
    }

    c->dia++;
    atualizar_clima_e_temperatura(c);
    pausar_tela();
}

void acao_curar_enfermos(Caravana *c) {
    if (c->mezinhas <= 0) {
        printf("\n❌ Não há mais frascos de garrafada ou mezinha no alforje!\n");
        printf("   É preciso conseguir com rezadeiras nas feiras dos povoados.\n");
        pausar_tela();
        return;
    }

    printf("\n--- TRATAR ENFERMOS COM MEZINHA MEDICINAL ---\n");
    printf("Você possui %d frasco(s) de garrafada com ervas curativas da caatinga.\n\n", c->mezinhas);

    for (int i = 0; i < MAX_MEMBROS; i++) {
        if (c->familia[i].vivo) {
            printf("[%d] %-14s : Saúde: %3d/100 | Condição: %s\n",
                   i + 1, c->familia[i].nome, c->familia[i].saude, descrever_estado(c->familia[i].estado));
        }
    }
    if (c->jumento_vivo) {
        printf("[5] Jumento Faísca : Condição: %3d%%  | Cascos e lombo\n", c->condicao_jumento);
    }
    printf("[0] Cancelar tratamento (Não usar mezinha)\n");
    printf("----------------------------------------------------------------------\n");
    printf("Escolha quem deseja medicar: ");

    int escolha = 0;
    int leu_esc = scanf("%d", &escolha);
    if (leu_esc == EOF || feof(stdin)) return;
    if (leu_esc != 1) {
        limpar_buffer();
        return;
    }
    limpar_buffer();

    if (escolha == 0) {
        printf("\nNenhum remédio foi administrado.\n");
        pausar_tela();
        return;
    }

    if (escolha >= 1 && escolha <= MAX_MEMBROS) {
        int idx = escolha - 1;
        if (c->familia[idx].vivo) {
            c->mezinhas--;
            c->familia[idx].saude += 40;
            if (c->familia[idx].saude > 100) c->familia[idx].saude = 100;
            c->familia[idx].estado = ESTADO_SAUDAVEL;
            printf("\n🌿 Sinhá Maria aplicou a garrafada benzida em %s.\n", c->familia[idx].nome);
            printf("   O veneno cedeu, a febre baixou e a saúde subiu para %d/100!\n", c->familia[idx].saude);
        } else {
            printf("\nEssa pessoa já descansou em Deus.\n");
        }
    } else if (escolha == 5 && c->jumento_vivo) {
        c->mezinhas--;
        c->condicao_jumento += 35;
        if (c->condicao_jumento > 100) c->condicao_jumento = 100;
        printf("\n🌿 Severino passou sebo de carneiro e aroeira nos cascos de Faísca!\n");
        printf("   O jumento relinchou agradecido! Firmeza recuperada para %d%%.\n", c->condicao_jumento);
    } else {
        printf("\nOpção inválida!\n");
    }
    pausar_tela();
}

void acao_ver_diario_bordo(const Caravana *c) {
    system("clear");
    cabecalho();
    printf("📜 DIÁRIO DE BORDO & PROVISÕES DE SEVERINO (Dia %d)\n", c->dia);
    printf("----------------------------------------------------------------------\n");
    printf("Progresso da Marcha:\n");
    printf("  Distância percorrida: %.1f léguas sertanejas\n", c->leguas_andadas);
    printf("  Faltam para o Brejo/Litoral: %.1f léguas\n", (META_LEGUAS - c->leguas_andadas > 0) ? (META_LEGUAS - c->leguas_andadas) : 0.0f);
    printf("  Média de marcha: %.2f léguas por dia\n", c->leguas_andadas / (c->dia > 0 ? c->dia : 1));
    printf("----------------------------------------------------------------------\n");
    printf("Estimativa de Autonomia dos Mantimentos:\n");
    float consumo_agua_estimado = (c->total_vivos * 1.3f) + (c->jumento_vivo ? 2.0f : 0.0f);
    float consumo_comida_estimado = (c->total_vivos * 0.5f);
    
    printf("  Água restante: %.1f L (~%.1f dias de autonomia)\n",
           c->agua_litros,
           (consumo_agua_estimado > 0) ? (c->agua_litros / consumo_agua_estimado) : 0.0f);
    printf("  Rapadura restante: %.1f kg (~%.1f dias de autonomia)\n",
           c->rapadura_kg,
           (consumo_comida_estimado > 0) ? (c->rapadura_kg / consumo_comida_estimado) : 0.0f);
    printf("----------------------------------------------------------------------\n");
    printf("Vilarejos no Roteiro:\n");
    printf("  [Légua 25] Vila do Teixeira ............ %s\n", c->vila_25_visitada ? "[VISITADO]" : "[ADIANTE]");
    printf("  [Légua 50] Feira de Patos .............. %s\n", c->vila_50_visitada ? "[VISITADO]" : "[ADIANTE]");
    printf("  [Légua 75] Tropeiros de Campina ........ %s\n", c->vila_75_visitada ? "[VISITADO]" : "[ADIANTE]");
    printf("  [Légua 100] Brejo Paraibano (Destino) .. %s\n", (c->leguas_andadas >= 100.0f) ? "[ALCANÇADO]" : "[DESTINO FINAL]");
    printf("======================================================================\n");
    pausar_tela();
}

/* --- TELAS DE FIM DE JOGO --- */

void exibir_vitoria(const Caravana *c) {
    system("clear");
    printf("======================================================================\n");
    printf("           GLÓRIA! A CARAVANA AVISTOU AS MATAS DO BREJO!              \n");
    printf("======================================================================\n\n");
    printf("Depois de vencer %.1f léguas de poeira, pedregulho e espinho em %d dias,\n", c->leguas_andadas, c->dia);
    printf("o ar seco deu lugar ao vento úmido da serra. As águas correm fartas!\n\n");

    printf("🌿 CORDEL DA VITÓRIA DOS RETIRANTES:\n");
    printf("   'Adeus, sertão de poeira,\n");
    printf("    Adeus, tempo de penar!\n");
    printf("    Chegamos na terra fresca,\n");
    printf("    Onde a cana vai brotar.\n");
    printf("    A família foi valente,\n");
    printf("    Não deixou o passo errar!'\n\n");

    int pontuacao = (c->total_vivos * 1000) + (int)(c->agua_litros * 50) + (c->dinheiro_reis / 10) + (c->jumento_vivo ? 500 : 0) - (c->dia * 20);
    if (pontuacao < 0) pontuacao = 0;

    printf("RESULTADO DA JORNADA:\n");
    printf("- Sobreviventes: %d de %d membros da família\n", c->total_vivos, MAX_MEMBROS);
    printf("- Jumento Faísca: %s\n", c->jumento_vivo ? "Sobreviveu firme!" : "Ficou na memória da estrada");
    printf("- Economias finais: %d réis\n", c->dinheiro_reis);
    printf("- Pontuação de Honra Sertaneja: %d pontos\n", pontuacao);
    printf("======================================================================\n");
}

void exibir_derrota(const Caravana *c, const char *motivo) {
    system("clear");
    printf("======================================================================\n");
    printf("                   TRAGÉDIA NA CAATINGA                               \n");
    printf("======================================================================\n\n");
    printf("A caminhada foi interrompida no dia %d, na légua %.1f do sertão.\n", c->dia, c->leguas_andadas);
    printf("Motivo do fim da jornada: %s\n\n", motivo);

    printf("✝️  CORDEL DO LUTO:\n");
    printf("   'O sol que nasce vermelho\n");
    printf("    Queimou todo o cariri,\n");
    printf("    A cruz de pau no terreiro\n");
    printf("    Marca quem tombou ali.\n");
    printf("    Fica a reza da lembrança\n");
    printf("    De quem lutou até o fim.'\n\n");
    printf("======================================================================\n");
}

/* --- TELA INICIAL COM APRESENTACAO CULTURAL --- */

void tela_abertura(void) {
    system("clear");
    printf("======================================================================\n");
    printf("           SERTÃO TRAIL: A MARCHA DOS RETIRANTES                      \n");
    printf("======================================================================\n");
    printf("Ano de 1877. A Grande Seca castiga o Nordeste.\n");
    printf("O gado definhou, o açude secou até o lodo e o mandacaru chora espinhos.\n\n");
    printf("Você assume o comando de Severino e sua família, partindo do Cariri\n");
    printf("rumo às terras férteis e úmidas do Brejo, percorrendo 100 léguas de estrada.\n\n");
    printf("Sua missão:\n");
    printf("  - Gerenciar água, rapadura, remédios e dinheiro (réis).\n");
    printf("  - Cuidar da saúde da família e do jumento Faísca.\n");
    printf("  - Negociar nas feiras de Teixeira, Patos e Campina Grande.\n");
    printf("  - Sobreviver ao calor extremo, cobras e cangaceiros.\n");
    printf("======================================================================\n");
    printf("[1] Iniciar a caminhada pelo sertão\n");
    printf("[2] Ler as regras e conselhos de sobrevivência\n");
    printf("[3] Sair do jogo\n");
    printf("----------------------------------------------------------------------\n");
    printf("Digite sua escolha: ");
}

void exibir_manual(void) {
    system("clear");
    cabecalho();
    printf("📖 MANUAL DE SOBREVIVÊNCIA DO RETIRANTE:\n\n");
    printf("1. ÁGUA É VIDA:\n");
    printf("   Em dias de calor escaldante, a temperatura passa dos 40°C e o consumo sobe.\n");
    printf("   Se faltar água, use a Ação [3] para cavar cacimbas e achar batatas de umbuzeiro.\n\n");
    printf("2. O JUMENTO FAÍSCA:\n");
    printf("   O jumento carrega até 60 kg de carga. Se ele sucumbir, a velocidade cai\n");
    printf("   e o excesso de bagagem precisa ser abandonado na estrada.\n\n");
    printf("3. MEZINHAS E REMÉDIOS:\n");
    printf("   Picadas de cascavel e febres da seca enfraquecem e matam. Use mezinhas\n");
    printf("   para curar pessoas ou tratar o jumento.\n\n");
    printf("4. FEIRAS LIVRES & COMÉRCIO:\n");
    printf("   Nas léguas 25, 50 e 75, você pode tanto COMPRAR quanto VENDER mercadorias por réis.\n");
    printf("======================================================================\n");
    pausar_tela();
}

/* --- LOOP PRINCIPAL DO JOGO --- */

int main(void) {
    srand((unsigned int)time(NULL));

    int escolha_inicial = 0;
    do {
        tela_abertura();
        int leu_ini = scanf("%d", &escolha_inicial);
        if (leu_ini == EOF || feof(stdin)) {
            return 0;
        }
        if (leu_ini != 1) {
            limpar_buffer();
            escolha_inicial = 0;
            continue;
        }
        limpar_buffer();

        if (escolha_inicial == 2) {
            exibir_manual();
        } else if (escolha_inicial == 3) {
            printf("\nAté a próxima jornada, sertanejo!\n");
            return 0;
        }
    } while (escolha_inicial != 1);

    Caravana caravana;
    inicializar_caravana(&caravana);
    atualizar_clima_e_temperatura(&caravana);

    printf("\nArreando o jumento e aprontando os cantis...\n");
    dormir(1);

    int jogo_ativo = 1;
    while (jogo_ativo) {
        exibir_painel(&caravana);

        // Menu de escolhas diárias
        printf("AÇÕES DO DIA:\n");
        printf("[1] Marchar na estrada (Avançar léguas)\n");
        printf("[2] Descansar à sombra do juazeiro (Recuperar saúde e fôlego)\n");
        printf("[3] Explorar a caatinga (Cavar cacimbas de ÁGUA ou caçar)\n");
        printf("[4] Tratar enfermos com mezinha medicinal\n");
        printf("[5] Abrir o diário de bordo e calcular autonomia\n");
        printf("[6] Desistir e buscar abrigo em fazenda próxima (Abandonar jogo)\n");
        printf("======================================================================\n");
        printf("Severino, o que a caravana fará hoje? ");

        int acao = 0;
        int leu_acao = scanf("%d", &acao);
        if (leu_acao == EOF || feof(stdin)) {
            break;
        }
        if (leu_acao != 1) {
            limpar_buffer();
            continue;
        }
        limpar_buffer();

        switch (acao) {
            case 1:
                acao_marchar(&caravana);
                break;
            case 2:
                acao_descansar(&caravana);
                break;
            case 3:
                acao_procurar_recursos(&caravana);
                break;
            case 4:
                acao_curar_enfermos(&caravana);
                break;
            case 5:
                acao_ver_diario_bordo(&caravana);
                break;
            case 6: {
                printf("\nTem certeza de que deseja abandonar a marcha? (1 = SIM, 2 = NÃO): ");
                int confirm = 0;
                int leu_conf = scanf("%d", &confirm);
                if (leu_conf == EOF || feof(stdin)) {
                    jogo_ativo = 0;
                    break;
                }
                if (leu_conf == 1 && confirm == 1) {
                    limpar_buffer();
                    exibir_derrota(&caravana, "Severino decidiu parar a jornada e virou meeiro em fazenda alheia.");
                    jogo_ativo = 0;
                } else {
                    limpar_buffer();
                    printf("Severino reuniu as forças e decidiu continuar lutando!\n");
                    dormir(1);
                }
                break;
            }
            default:
                printf("\nOpção inválida! Digite um número de 1 a 6.\n");
                dormir(1);
                break;
        }

        // 1. CHECAGEM OBRIGATÓRIA DE DERROTA PRIMEIRO
        if (!caravana.familia[0].vivo) { // Severino faleceu
            exibir_derrota(&caravana, "Severino, o líder da família, faleceu na caminhada. A caravana se dispersou na caatinga.");
            jogo_ativo = 0;
            break;
        }

        if (caravana.total_vivos <= 0) { // Todos faleceram
            exibir_derrota(&caravana, "Nenhum membro da família resistiu à dureza da seca.");
            jogo_ativo = 0;
            break;
        }

        // 2. CHECAGEM DE VITÓRIA DEPOIS
        if (caravana.leguas_andadas >= META_LEGUAS) {
            exibir_vitoria(&caravana);
            jogo_ativo = 0;
            break;
        }
    }

    printf("\nObrigado por jogar Sertão Trail!\n\n");
    return 0;
}
