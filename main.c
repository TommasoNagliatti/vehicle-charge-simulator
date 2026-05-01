#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

void menu();
float contador_wallbox();
void menu_escolha();
void escolha_caso();
float contador_tomada();

float contador_tomada() {
    int segundos = 0;
    int minutos  = 0;  // 0 a 59

    const int LIMITE_SEGUNDOS = 70;

    printf("\nPressione qualquer tecla para iniciar...");
    printf("\nO limite maximo eh de 70 'horas'! (tempo para o carregamento completo)");

    while (!kbhit()) {}
    getch();

    printf("\nContando... pressione 'q' para parar\n");

    clock_t ultimo = clock();

    while (segundos < LIMITE_SEGUNDOS) {
        clock_t agora = clock();
        double decorrido = (double)(agora - ultimo) / CLOCKS_PER_SEC;

        if (decorrido >= 0.020) {  // ~1/60 de segundo por tick
            ultimo = agora;
            minutos++;

            if (minutos >= 60) {
                minutos = 0;
                segundos++;
            }

            printf("\rTempo: %d.%02d 'horas'", segundos, minutos);
            fflush(stdout);
        }

        if (kbhit()) {
            char tecla = tolower(getch());
            if (tecla == 'q') break;
        }
    }

    printf("\nSessao encerrada!\n");

    if (segundos >= LIMITE_SEGUNDOS)
        printf("Tempo limite atingido!\n");

    // Ex: 4 horas e 35 minutos = 4 + 35/60 = 4.583...
    float tempo_final = segundos + (minutos / 100.0f);
    return tempo_final;
}

float contador_wallbox(){  
    int segundos = 0;
    int minutos  = 0;  // 0 a 59

    const int LIMITE_SEGUNDOS = 14;

    printf("\nPressione qualquer tecla para iniciar...");
    printf("\nO limite maximo eh de 14 'horas'! (tempo para o carregamento completo)");

    while (!kbhit()) {}
    getch();

    printf("\nContando... pressione 'q' para parar\n");

    clock_t ultimo = clock();

    while (segundos < LIMITE_SEGUNDOS) {
        clock_t agora = clock();
        double decorrido = (double)(agora - ultimo) / CLOCKS_PER_SEC;

        if (decorrido >= 0.020) {  // ~1/60 de segundo por tick
            ultimo = agora;
            minutos++;

            if (minutos >= 60) {
                minutos = 0;
                segundos++;
            }

            printf("\rTempo: %d.%02d 'horas'", segundos, minutos);
            fflush(stdout);
        }

        if (kbhit()) {
            char tecla = tolower(getch());
            if (tecla == 'q') break;
        }
    }

    printf("\nSessao encerrada!\n");

    if (segundos >= LIMITE_SEGUNDOS)
        printf("Tempo limite atingido!\n");

    // Ex: 4 horas e 35 minutos = 4 + 35/60 = 4.583...
    float tempo_final = segundos + (minutos / 100.0f);
    return tempo_final;
}

void menu() {
    printf("\n============================================================\n");
    printf("           SIMULADOR DE RECARGA VEICULAR - V1.0\n");
    printf("============================================================\n");

    printf("\nDESCRICAO:\n");
    printf("Este programa simula uma sessao de recarga de um veiculo eletrico.\n");
    printf("O modelo utilizado como referencia eh o BYD Yangwang U7,\n");
    printf("com capacidade de bateria de 154 kWh.\n");
    printf("O custo de carregamento considerado eh de R$ 0,71 por kWh.\n");

    printf("\nCOMO FUNCIONA:\n");
    printf("Escolha um metodo de carregamento e inicie a simulacao.\n");
    printf("O contador representa o tempo de carga em 'horas' simuladas.\n");
    printf("Pressione 'q' a qualquer momento para encerrar a sessao.\n");
    printf("Ao final, o programa exibe energia consumida, custo e nivel da bateria.\n");

    printf("\nMETODOS DISPONIVEIS:\n");
    printf("1 - Wallbox (11 kW) - carga completa em ate 14.00 'horas'\n");
    printf("2 - Tomada 220V (2,2 kW) - carga completa em ate 70.00 'horas'\n");

    printf("\n============================================================\n");
}

void menu_escolha() {
    printf("\n============================================================\n");
    printf("                INICIANDO SIMULADOR DE RECARGA\n");
    printf("============================================================\n");

    printf("\nVEICULO: BYD Yangwang U7\n");
    printf("Capacidade da bateria: 154 kWh\n");
    printf("Custo por kWh: R$ 0,71\n");

    printf("\nESCOLHA O TIPO DE CARREGAMENTO:\n");

    printf("\n[1] Wallbox - GoodWe HCA G2 (GW11K-HCA-20)\n");
    printf("    Potencia : 11 kW\n");
    printf("    Corrente : 16 A\n");
    printf("    Limite   : 14.00 'horas' simuladas\n");

    printf("\n[2] Tomada residencial 220V\n");
    printf("    Potencia : 2,2 kW\n");
    printf("    Limite   : 70.00 'horas' simuladas\n");

    printf("\nDigite a opcao desejada: ");
}

void wallbox(){
    float tempo;
    float potencia_carregador = 11.0;
    float preco_kwh = 0.71;
    float capacidade_bateria = 154;

    float energia, custo, tempo_carregamento;
    float valor_percentual_tempo;


    tempo = contador_wallbox();

    // energia e custo
    energia = potencia_carregador * tempo;
    custo = energia * preco_kwh;

    // % pelo tempo
    valor_percentual_tempo = (energia / capacidade_bateria) * 100;

    // tempo carga total
    tempo_carregamento = capacidade_bateria / potencia_carregador;

    //tempo para a carga restante
    float tempo_restante = tempo_carregamento - tempo;
    
    printf("\n============================================================\n");
    printf("                  RESUMO DA SESSAO DE RECARGA\n");
    printf("============================================================\n");

    printf("\n  Tempo de carga      : %.2f h\n", tempo);
    printf("  Energia consumida   : %.2f kWh\n", energia);
    printf("  Custo total         : R$ %.2f\n", custo);
    printf("  Nivel da bateria    : %.2f%%\n", valor_percentual_tempo);
    printf("  Tempo restante      : %.2f h\n", tempo_restante);

    printf("\n  Tempo para 0%% a 100%%: %.2f h\n", tempo_carregamento);

    printf("\n============================================================\n");
}

void tomada_comum(){
    float tempo;
    float potencia_carregador = 2.2;
    float preco_kwh = 0.71;
    float capacidade_bateria = 154;

    float energia, custo, tempo_carregamento;
    float valor_percentual_tempo;

    tempo = contador_tomada();

    // energia e custo
    energia = potencia_carregador * tempo;
    custo = energia * preco_kwh;

    // % pelo tempo
    valor_percentual_tempo = (energia / capacidade_bateria) * 100;

    // tempo carga total
    tempo_carregamento = capacidade_bateria / potencia_carregador;
    
    //tempo para a carga restante
    float tempo_restante = tempo_carregamento - tempo;
    
    printf("\n============================================================\n");
    printf("                  RESUMO DA SESSAO DE RECARGA\n");
    printf("============================================================\n");

    printf("\n  Tempo de carga      : %.2f h\n", tempo);
    printf("  Energia consumida   : %.2f kWh\n", energia);
    printf("  Custo total         : R$ %.2f\n", custo);
    printf("  Nivel da bateria    : %.2f%%\n", valor_percentual_tempo);
    printf("  Tempo restante      : %.2f h\n", tempo_restante);

    printf("\n  Tempo para 0%% a 100%%: %.2f h\n", tempo_carregamento);

    printf("\n============================================================\n");
}

void escolha_caso(){
    int opcao;

    menu_escolha();
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
        wallbox();
        break;

    case 2:
        tomada_comum();
        break;

    case 0:
        printf("Saindo...\n");
        break;

    default:
        printf("Opcao invalida\n");
        break;
    }

}

int main() {
        char inicio;

        do {
            menu();
            printf("\nDeseja iniciar a simulacao? [s/n]: ");
            scanf(" %c", &inicio);
            inicio = tolower(inicio);

            if (inicio == 's') {           
                escolha_caso();
            }
            else if (inicio == 'n') {
                printf("Fechando o programa...\n");
            }
            else {
                printf("Opcao invalida! Digite s ou n.\n");
            }

        } while (inicio != 's' && inicio != 'n');

        return 0;
    }