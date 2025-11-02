#include <stdio.h>
#include <stdbool.h>

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

char jogador[2] [20]; //Armazena os nomes dos jogadores

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

int ObterCoordenada(const char* eixo) {//Verifica se a entrada do usuario é valida, e a ajusta para o indice do array
    int coordenada;
    bool entradaValida = false;

    while (!entradaValida) {
        printf("\n%s, digite a coordenada %s (1-8): ", jogador[jogadorDaVez], eixo);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if(scanf("%d", &coordenada) != 1 || (coordenada > 8 || coordenada < 1)){
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("ERRO: Entrada invalida. Por favor, digite um numero entre 1 e 8.\n");
            
            continue;
        }

        entradaValida = true;
        
        
    }
    return coordenada - 1; // Ajusta para índice de array (0-7)
}


int main() {
    

    
    int pontos[2] = {0, 0};
    
    printf("----------------------XADREZ----------------------\n\n");

    for(int i = 0; i < 2; i++){
        printf("Digite o nome do %d jogador: ", i + 1);
        scanf("%19s", jogador[i]);
    }



    while(!ganhou){
        printf("\n");
        ExibirTabuleiro();

        printf("E a vez de %s!\n", jogador[jogadorDaVez]);

        int linhaOrigem = ObterCoordenada("da linha da peca que queres mover");
        int colunaOrigem = ObterCoordenada("da coluna da peca que queres mover");

        if(tabuleiro[linhaOrigem][colunaOrigem] == ' '){
            printf("Jogada invalida! Nao ha peca na posicao de origem.\n");
            
            continue;
            
        }

        int linhaDestino = ObterCoordenada("da linha da posicao para a qual queres mover");
        int colunaDestino = ObterCoordenada("da coluna da posicao para a qual queres mover");

        if(JogadaValida(tabuleiro, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino, jogadorDaVez)){
            
            movimentosFeitos++;

            //Verifica a captura de peças e atualiza a pontuação
            if (tabuleiro[linhaDestino][colunaDestino] == 'p' || tabuleiro[linhaDestino][colunaDestino] == 'P'){
                // Captura de peão
                pontos[jogadorDaVez] += 1; // Incrementa o ponto do jogador que capturou
            } else if(tabuleiro[linhaDestino][colunaDestino] == 'c' || tabuleiro[linhaDestino][colunaDestino] == 'C' || tabuleiro[linhaDestino][colunaDestino] == 'b' || tabuleiro[linhaDestino][colunaDestino] == 'B'){
                // Captura de cavalo ou bispo
                pontos[jogadorDaVez] += 3; // Incrementa 3 pontos para cavalo ou bispo
            } else if(tabuleiro[linhaDestino][colunaDestino] == 't' || tabuleiro[linhaDestino][colunaDestino] == 'T'){
                // Captura de torre
                pontos[jogadorDaVez] += 5; // Incrementa 5 pontos para torre
            } else if(tabuleiro[linhaDestino][colunaDestino] == 'q' || tabuleiro[linhaDestino][colunaDestino] == 'Q'){
                // Captura de rainha
                pontos[jogadorDaVez] += 9; // Incrementa 9 pontos para rainha
            } else if(tabuleiro[linhaDestino][colunaDestino] == 'k' || tabuleiro[linhaDestino][colunaDestino] == 'K'){
                // Captura de rei
                ganhou = true;
                printf("O jogador %s ganhou o jogo!\n", jogador[jogadorDaVez]);
                printf("Placar final: %s: %d pontos, %s: %d pontos\n", jogador[0], pontos[0], jogador[1], pontos[1]);
                printf("Total de movimentos feitos: %d\n", movimentosFeitos);
                break; // Sai do loop principal do jogo
            }
            
            tabuleiro[linhaDestino][colunaDestino] = tabuleiro[linhaOrigem][colunaOrigem];
            tabuleiro[linhaOrigem][colunaOrigem] = ' ';


            jogadorDaVez = 1 - jogadorDaVez; // Alterna entre 0 e 1, trocando o jogador da vez
        } else {
            printf("Jogada invalida! Tente novamente.\n");
        }

    }


    return 0;
}