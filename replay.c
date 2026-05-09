#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "jogadasvalidas.h"
#include "cores.h"
#include "traducao.h"
#include "jogo.h"
#include "replay.h"
#include "utils.h"


/*A função exibe o tabuleiro:
    - As casas a-h;
    - Exibe as peças, colocando o backgruond com a coloração do tabuleiro do xadrez;
    - E ao lado, os números das linhas.*/
static void ExibirTabuleiroReplay(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int ultimoMovimentoOrigem[2], int ultimoMovimentoDestino[2]) {
    printf("  ╔═════════════════╗\n");
    printf("  ║ a b c d e f g h ║\n");
    printf("  ╠═════════════════╣\n");
    for (int i = TAMANHO_TABULEIRO; i >= 1; i--) {
        int conversaoLinha = TAMANHO_TABULEIRO - i;
        printf("%d ║ ", i);
        
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            char* backgroundColor = ((conversaoLinha == ultimoMovimentoOrigem[0] && j == ultimoMovimentoOrigem[1]) ||
        (conversaoLinha == ultimoMovimentoDestino[0] && j == ultimoMovimentoDestino[1])) ? AMARELO_BACKGROUND :
            ((conversaoLinha + j) % 2 == 0 ? BRANCO_BACKGROUND : PRETO_BACKGROUND);
            char* textColor = (islower(tabuleiro[conversaoLinha][j]))  ? AMARELO_FOREGROUND : CIANO_FOREGROUND;
            
            printf("%s%s", backgroundColor, textColor);
            printf("%s ", ObterSimboloPeca(tabuleiro[conversaoLinha][j]));
            printf("%s", RESET);
        }
        printf("║\n");
    }
    printf("  ╚═════════════════╝\n");
}



void ExibirReplay(){
    EstadoPosicao* historicoPos = ObterHistoricoPositoes();
    int countPos = ObterCountHistoricoPositoes();

    Movimento historicoMovimentos[MAX_HISTORICO];
    int countMovimentos;
    obterHistoricoMovimentos(historicoMovimentos, &countMovimentos);

    int contagemReplay = 0;

    char input[10];

    while (1)
    {
        int origem[2] = {-1, -1};
        int destino[2] = {-1, -1};
        if(contagemReplay > 0 && contagemReplay <= countMovimentos){
            origem[0] = historicoMovimentos[contagemReplay].linhaOrigem;
            origem[1] = historicoMovimentos[contagemReplay].colunaOrigem;
            destino[0] = historicoMovimentos[contagemReplay].linhaDestino;
            destino[1] = historicoMovimentos[contagemReplay].colunaDestino;
        }
        ExibirTabuleiroReplay(historicoPos[contagemReplay].tabuleiro, origem, destino);
        printf("\n");

        if (contagemReplay > 0 && contagemReplay <= countMovimentos) {
            char origemCol = 'a' + origem[1];
            char destCol = 'a' + destino[1];
            int origemLinha = 8 - origem[0];
            int destLinha = 8 - destino[0];
            
            printfSColor(NEGRITO, VERDE_FOREGROUND, "Movimento %d: ", contagemReplay);
            printf("%c%d → %c%d\n\n", origemCol, origemLinha, destCol, destLinha);
        } else {
            printfSColor(NEGRITO, VERDE_FOREGROUND, "Posição Inicial\n\n");
        }

        printfSColor(NEGRITO, AMARELO_FOREGROUND, "Opções:\n");
        printf("  [P] Anterior   [N] Próximo   [I] Ir para   [S] Sair\n");
        printf("> ");
        fflush(stdout);
        
        fgets(input, sizeof(input), stdin);
        trim(input);

        if (comparar_case_insensitive(input, "n") == 0) {
            if (contagemReplay < countPos - 1) contagemReplay++;
        }
        else if (comparar_case_insensitive(input, "p") == 0) {
            if (contagemReplay > 0) contagemReplay--;
        }
        else if (comparar_case_insensitive(input, "i") == 0) {
            printf("Ir para movimento (0-%d): ", countPos - 1);
            fflush(stdout);
            fgets(input, sizeof(input), stdin);
            int movimento = atoi(input);
            if (movimento >= 0 && movimento < countPos) {
                contagemReplay = movimento;
            }
        }
        else if (comparar_case_insensitive(input, "s") == 0) {
            break;
        }
        
        
    }
    
}