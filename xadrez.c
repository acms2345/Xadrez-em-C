#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "jogadasvalidas.h"

char tabuleiro[8][8] = {
    {'t', 'c', 'b', 'k', 'q', 'b', 'c', 't'},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'T', 'C', 'B', 'K', 'Q', 'B', 'C', 'T'}
};

int jogadorDaVez = 0; // 0 para o Jogador 1 (maiúsculas), 1 para o Jogador 2 (minúsculas)

typedef struct {
    char nome[20];
    int pontos;
} Jogador;

Jogador jogadores[2];

int movimentosFeitos = 0;

bool ganhou = false;

void ExibirTabuleiro() {
    printf("\n  1 2 3 4 5 6 7 8\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < 8; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

/**
 * Solicita ao jogador atual que digite uma coordenada (linha ou coluna) entre 1 e 8.
 * Valida a entrada, garantindo que seja um número inteiro dentro do intervalo permitido.
 * Retorna o valor da coordenada ajustado para índice de array (0-7).
 */
int ObterCoordenada(const char* eixo) {
    int coordenada, ch;

    for (;;) {
        printf("\n%s, digite a coordenada %s (1-8): ", jogadores[jogadorDaVez].nome, eixo);

        if (scanf("%d", &coordenada) != 1) {
            while ((ch = getchar()) != '\n' && ch != EOF) {} // descarta linha
            printf("ERRO: Entrada invalida. Por favor, digite um numero entre 1 e 8.\n");
            continue;
        }

        // sempre descarta o restante da linha (inclui "lixo" como abc)
        while ((ch = getchar()) != '\n' && ch != EOF) {}

        if (coordenada < 1 || coordenada > 8) {
            printf("ERRO: Entrada invalida. Por favor, digite um numero entre 1 e 8.\n");
            continue;
        }

        return coordenada - 1;
    }
}

char PromocaoPeao(int linhaDestino, int colunaDestino, int jogadorDaVez) {
    char escolha;
    printf("Seu peao chegou na ultima linha! Escolha a peca para promover (Q, C, B, T): ");
    while (1) {
        scanf(" %c", &escolha);
        if(jogadorDaVez == 0) {
            escolha = toupper(escolha);
        } else {
            escolha = tolower(escolha);
        }
        if (((escolha == 'Q' || escolha == 'C' || escolha == 'B' || escolha == 'T') && jogadorDaVez == 0) ||
            ((escolha == 'q' || escolha == 'c' || escolha == 'b' || escolha == 't') && jogadorDaVez == 1)) {
            return escolha;
        } else {
            printf("Escolha invalida. Por favor, escolha entre Q, C, B, T: ");
        }
    }
}

int main() {
    
    
    printf("----------------------XADREZ----------------------\n\n");

    for(int i = 0; i < 2; i++){
        printf("Digite o nome do %d jogador: ", i + 1);
        scanf("%19s", jogadores[i].nome);
        jogadores[i].pontos = 0;
    }



    while(!ganhou){
        printf("\n");
        ExibirTabuleiro();

        printf("E a vez de %s!\n (%s)", jogadores[jogadorDaVez].nome, (jogadorDaVez == 0) ? "MAIUSCULAS" : "minusculas");

        int linhaOrigem = ObterCoordenada("da linha da peca que queres mover");
        int colunaOrigem = ObterCoordenada("da coluna da peca que queres mover");

        if(tabuleiro[linhaOrigem][colunaOrigem] == ' '){
            printf("Jogada invalida! Nao ha peca na posicao de origem.\n");
            
            continue;
            
        }

        int linhaDestino = ObterCoordenada("da linha da posicao para a qual queres mover");
        int colunaDestino = ObterCoordenada("da coluna da posicao para a qual queres mover");

        const char* resultadoJogadaValida = JogadaValida(tabuleiro, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino, jogadorDaVez);

        if(strcmp(resultadoJogadaValida, "OK") == 0){
            
            movimentosFeitos++;

            //Verifica a captura de peças e atualiza a pontuação
            switch(toupper(tabuleiro[linhaDestino][colunaDestino])){
                case 'P':
                    jogadores[jogadorDaVez].pontos += 1; // Incrementa o ponto do jogador que capturou
                    break;
                case 'C':
                case 'B':
                    jogadores[jogadorDaVez].pontos += 3; // Incrementa 3 pontos para cavalo ou bispo
                    break;
                case 'T':
                    jogadores[jogadorDaVez].pontos += 5; // Incrementa 5 pontos para torre
                    break;
                case 'Q':
                    jogadores[jogadorDaVez].pontos += 9; // Incrementa 9 pontos para rainha
                    break;
                case 'K':
                    ganhou = true;
                    printf("O jogador %s ganhou o jogo!\n", jogadores[jogadorDaVez].nome);
                    printf("Placar final: %s: %d pontos, %s: %d pontos\n", jogadores[0].nome, jogadores[0].pontos, jogadores[1].nome, jogadores[1].pontos);
                    printf("Total de movimentos feitos: %d\n", movimentosFeitos);
                    break; // Sai do loop principal do jogo
                
                default:
                    break; // Nenhuma peça capturada
            }
            if(ganhou){
                break; // Sai do loop principal do jogo se alguém ganhou
            }
            


            tabuleiro[linhaDestino][colunaDestino] = tabuleiro[linhaOrigem][colunaOrigem];
            tabuleiro[linhaOrigem][colunaOrigem] = ' ';

            if((tabuleiro[linhaDestino][colunaDestino] == 'p' && linhaDestino == 7) || (tabuleiro[linhaDestino][colunaDestino] == 'P' && linhaDestino == 0)){
                tabuleiro[linhaDestino][colunaDestino] = PromocaoPeao(linhaDestino, colunaDestino, jogadorDaVez);

            }


            jogadorDaVez = 1 - jogadorDaVez; // Alterna entre 0 e 1, trocando o jogador da vez
        } else {
            printf("Jogada invalida! %s.\n", resultadoJogadaValida);
        }

    }
    system("pause");


    return 0;
}