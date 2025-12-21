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

bool SalvarJogo();
bool CarregarJogo();

void ExibirTabuleiro() {
    printf("\n  a b c d e f g h\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < 8; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

/**
 * Solicita ao jogador que insira uma jogada no formato de notação algébrica.
 * Parâmetros:
 *   linhaOrigem, colunaOrigem: ponteiros para armazenar a linha e coluna de origem.
 *   linhaDestino, colunaDestino: ponteiros para armazenar a linha e coluna de destino.
 * O jogador pode digitar "salvar" para salvar o jogo atual.
 */
void obterCoordenada(int *linhaOrigem, int *colunaOrigem, int *linhaDestino, int *colunaDestino){
    char input[10];
    int ch;

    while(1){
        printf("\n%s, digite a jogada em notacao algebrica (ex: e2e4): ", jogadores[jogadorDaVez].nome);
        scanf("%9s", input);

        while ((ch = getchar()) != '\n' && ch != EOF);

        if(strcmp(input, "salvar") == 0 || strcmp(input, "SALVAR") == 0){
            if(SalvarJogo()){
                printf("Jogo salvo com sucesso!\n");
            } else {
                printf("Erro ao salvar o jogo.\n");
            }
            continue;
        }

        if(strlen(input) != 4){
            printf("ERRO: Formato invalido. Use 4 caracteres (ex: e2e4)\n");
            continue;
        }
        if(tolower(input[0]) < 'a' || tolower(input[0]) > 'h'){
            printf("ERRO: Coluna origem invalida. Use letras de a-h.\n");
            continue;
        }
        *colunaOrigem = tolower(input[0]) - 'a';
        
        if(input[1] < '1' || input[1] > '8'){
            printf("ERRO: Linha origem invalida. Use numeros de 1-8.\n");
            continue;
        }
        *linhaOrigem = input[1] - '1';

        if(tolower(input[2]) < 'a' || tolower(input[2]) > 'h'){
            printf("ERRO: Coluna destino invalida. Use letras de a-h.\n");
            continue;
        }
        *colunaDestino = tolower(input[2]) - 'a';

        if(input[3] < '1' || input[3] > '8'){
            printf("ERRO: Linha destino invalida. Use numeros de 1-8.\n");
            continue;
        }
        *linhaDestino = input[3] - '1';
            
        
        break;
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
struct Salvamento
{
    char tabuleiro[8][8];
    int jogadorDaVez;
    int movimentosFeitos;
    Jogador jogadores[2];
};
bool SalvarJogo() {
    FILE *arquivo = fopen("salvamento.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar o jogo.\n");
        return false;
    }
    
    
    struct Salvamento salvamento;
    memcpy(salvamento.tabuleiro, tabuleiro, sizeof(tabuleiro));
    salvamento.jogadorDaVez = jogadorDaVez;
    salvamento.movimentosFeitos = movimentosFeitos;
    memcpy(salvamento.jogadores, jogadores, sizeof(jogadores));

    fwrite(&salvamento, sizeof(salvamento), 1, arquivo);
    fclose(arquivo);
    
    return true;
}

bool CarregarJogo() {
    FILE *arquivo = fopen("salvamento.dat", "rb");
    if (arquivo == NULL) {
        printf("Nenhum jogo salvo encontrado.\n");
        return false;
    }
    
    struct Salvamento salvamento;

    fread(&salvamento, sizeof(salvamento), 1, arquivo);
    fclose(arquivo);
    
    memcpy(tabuleiro, salvamento.tabuleiro, sizeof(tabuleiro));
    jogadorDaVez = salvamento.jogadorDaVez;
    movimentosFeitos = salvamento.movimentosFeitos;
    memcpy(jogadores, salvamento.jogadores, sizeof(jogadores));
    
    return true;
}

int iniciarJogo(int opcao) {
    
    
    printf("--------------------------------------------\n\n");

    if (opcao == 1){
        for(int i = 0; i < 2; i++){
            printf("Digite o nome do %d jogador: ", i + 1);
            scanf("%19s", jogadores[i].nome);
            jogadores[i].pontos = 0;
        }
    } else {
        CarregarJogo();
    }
    


    while(!ganhou){
        printf("\n");
        ExibirTabuleiro();

        printf("E a vez de %s!\n (%s)", jogadores[jogadorDaVez].nome, (jogadorDaVez == 0) ? "MAIUSCULAS" : "minusculas");

        int linhaOrigem, colunaOrigem, linhaDestino, colunaDestino;

        obterCoordenada(&linhaOrigem, &colunaOrigem, &linhaDestino, &colunaDestino);
        

        if(tabuleiro[linhaOrigem][colunaOrigem] == ' '){
            printf("Jogada invalida! Nao ha peca na posicao de origem.\n");
            
            continue;
            
        }


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
    printf("Pressione Enter para sair...");
    while(getchar() != '\n'); // Limpa o buffer de entrada
    getchar();

    return 0;
}