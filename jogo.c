#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "jogadasvalidas.h"
#include "jogo.h"

/*Note: The source code is entirely written in Portuguese now.*/

void limpezaBuffer(){
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}



static const char TABULEIRO_INICIAL[8][8] = {
    {'t', 'c', 'b', 'q', 'k', 'b', 'c', 't'},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'T', 'C', 'B', 'Q', 'K', 'B', 'C', 'T'}
};

static char tabuleiro[8][8];

static int jogadorDaVez = 0; // 0 para o Jogador 1 (maiúsculas), 1 para o Jogador 2 (minúsculas)

static int movimentosSemCapturaouPiao = 0;

typedef struct {
    char nome[20];
    int pontos;
} Jogador;

static Jogador jogadores[2];

static int movimentosFeitos = 0;

static bool ganhou = false;

static bool SalvarJogo();
static bool CarregarJogo();

static void ExibirTabuleiro() {
    printf("\n  a b c d e f g h\n");
    for (int i = 8; i >= 1; i--) {
        int conversaoLinha = 8 - i;
        printf("%d ", i);
        
        for (int j = 0; j < 8; j++) {
            printf("%c ", tabuleiro[conversaoLinha][j]);
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
static bool obterCoordenada(int *linhaOrigem, int *colunaOrigem, int *linhaDestino, int *colunaDestino){
    char input[10];

    while(1){
        printf("\n%s, digite a jogada em notacao algebrica (ex: e2e4): ", jogadores[jogadorDaVez].nome);
        scanf("%9s", input);

        limpezaBuffer();

        if(strcmp(input, "salvar") == 0 || strcmp(input, "SALVAR") == 0){
            if(SalvarJogo()){
                printf("Jogo salvo com sucesso!\n");
            } else {
                printf("Erro ao salvar o jogo.\n");
            }
            continue;
        }

        if(strcmp(input, "desistir") == 0 || strcmp(input, "DESISTIR") == 0){
            printf("%s desistiu do jogo. %s e o vencedor!\n", jogadores[jogadorDaVez].nome, jogadores[1 - jogadorDaVez].nome);
            ganhou = true;
            return false;
        }

        //Para notação sem separação (ex: e2e4)
        if(strlen(input) == 4){
            if(tolower(input[0]) < 'a' || tolower(input[0]) > 'h'){
                printf("ERRO: Coluna origem invalida. Use letras de a-h.\n");
                continue;
            }
            *colunaOrigem = tolower(input[0]) - 'a';
        
            if(input[1] < '1' || input[1] > '8'){
                printf("ERRO: Linha origem invalida. Use numeros de 1-8.\n");
                continue;
            }
            
            int conversaoLinhaOrigem = input[1] - '0';
            *linhaOrigem = 8 - conversaoLinhaOrigem;

            if(tolower(input[2]) < 'a' || tolower(input[2]) > 'h'){
                printf("ERRO: Coluna destino invalida. Use letras de a-h.\n");
                continue;
            }
            *colunaDestino = tolower(input[2]) - 'a';

            if(input[3] < '1' || input[3] > '8'){
                printf("ERRO: Linha destino invalida. Use numeros de 1-8.\n");
                continue;
            }
            
            
            int conversaoLinhaDestino = input[3] - '0';
            *linhaDestino = 8 - conversaoLinhaDestino;
                
            
            break;
        } 
        //Notação com separador (ex: e2-e4)
        else if (strlen(input) == 5){
            if ((input[2] != ' ') && (input[2] != '-')){
                printf("ERRO: Digito invalido. Para separar, use espaco ou hifen.\n");
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
            
            int conversaoLinhaOrigem = input[1] - '0';
            *linhaOrigem = 8 - conversaoLinhaOrigem;

            if(tolower(input[3]) < 'a' || tolower(input[3]) > 'h'){
                printf("ERRO: Coluna destino invalida. Use letras de a-h.\n");
                continue;
            }
            *colunaDestino = tolower(input[3]) - 'a';

            if(input[4] < '1' || input[4] > '8'){
                printf("ERRO: Linha destino invalida. Use numeros de 1-8.\n");
                continue;
            }
            
            
            int conversaoLinhaDestino = input[4] - '0';
            *linhaDestino = 8 - conversaoLinhaDestino;
                
            
            break;
        } else{
            printf("ERRO: Formato invalido. Use 4 caracteres (ex: e2e4) ou use 5 caracteres (ex: e2-e4)\n");
            continue;
        }
        
    }
    
    return true;
}

static char PromocaoPeao(int linhaDestino, int colunaDestino, int jogadorDaVez) {
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
    int movimentosSemCapturaouPiao;
    Jogador jogadores[2];
};

static bool SalvarJogo() {
    FILE *arquivo = fopen("salvamento.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar o jogo.\n");
        return false;
    }
    
    
    struct Salvamento salvamento;
    memcpy(salvamento.tabuleiro, tabuleiro, sizeof(tabuleiro));
    salvamento.jogadorDaVez = jogadorDaVez;
    salvamento.movimentosFeitos = movimentosFeitos;
    salvamento.movimentosSemCapturaouPiao = movimentosSemCapturaouPiao;
    memcpy(salvamento.jogadores, jogadores, sizeof(jogadores));

    fwrite(&salvamento, sizeof(salvamento), 1, arquivo);
    fclose(arquivo);
    
    return true;
}

static bool CarregarJogo() {
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
    movimentosSemCapturaouPiao = salvamento.movimentosSemCapturaouPiao;
    memcpy(jogadores, salvamento.jogadores, sizeof(jogadores));
    
    return true;
}

static bool capturaOuPiao = false;

static void atualizarPontuacao(int *pontos, char pecaCapturada){
    switch(toupper(pecaCapturada)){
                case 'P':
                    *pontos += 1; // Incrementa o ponto do jogador que capturou
                    capturaOuPiao = true;
                    break;
                case 'C':
                case 'B':
                    *pontos += 3; // Incrementa 3 pontos para cavalo ou bispo
                    capturaOuPiao = true;
                    break;
                case 'T':
                    *pontos += 5; // Incrementa 5 pontos para torre
                    capturaOuPiao = true;
                    break;
                case 'Q':
                    *pontos += 9; // Incrementa 9 pontos para rainha
                    capturaOuPiao = true;
                    break;
                default:
                    break; // Nenhuma peça capturada
    }
}

static void reiniciarJogo(){
    memcpy(tabuleiro, TABULEIRO_INICIAL, sizeof(TABULEIRO_INICIAL));
    jogadorDaVez = 0;
    movimentosSemCapturaouPiao = 0;
    movimentosFeitos = 0;
    capturaOuPiao = false;
    ganhou = false;
}

int iniciarJogo(int opcao) {
    
    limpezaBuffer();

    reiniciarJogo();

    printf("--------------------------------------------\n\n");

    if (opcao == 1){
        for(int i = 0; i < 2; i++){
            printf("Digite o nome do %d jogador: ", i + 1);
            scanf("%19s", jogadores[i].nome);
            jogadores[i].pontos = 0;
        }
        movimentosSemCapturaouPiao = 0;
        movimentosFeitos = 0;
    } else {
        CarregarJogo();
    }
    


    while(!ganhou){
        capturaOuPiao = false;
        
        printf("\n");
        ExibirTabuleiro();

        printf("E a vez de %s!\n (%s)", jogadores[jogadorDaVez].nome, (jogadorDaVez == 0) ? "MAIUSCULAS" : "minusculas");

        int linhaOrigem, colunaOrigem, linhaDestino, colunaDestino;

        if(!obterCoordenada(&linhaOrigem, &colunaOrigem, &linhaDestino, &colunaDestino)){
            break; // Sai do loop principal do jogo se o jogador desistir
        }
        


        if(tabuleiro[linhaOrigem][colunaOrigem] == ' '){
            printf("Jogada invalida! Nao ha peca na posicao de origem.\n");
            
            continue;
            
        }


        const char* resultadoJogadaValida = JogadaValida(tabuleiro, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino, jogadorDaVez);

        if(strcmp(resultadoJogadaValida, "OK") == 0){
            
            movimentosFeitos++;

            if(toupper(tabuleiro[linhaOrigem][colunaOrigem]) == 'P'){
                capturaOuPiao = true;
            }

            //Verifica a captura de peças e atualiza a pontuação
            atualizarPontuacao(&jogadores[jogadorDaVez].pontos, tabuleiro[linhaDestino][colunaDestino]);
            
            if(toupper(tabuleiro[linhaDestino][colunaDestino]) == 'K'){
                ganhou = true;
                printf("O jogador %s ganhou o jogo!\n", jogadores[jogadorDaVez].nome);
                printf("Placar final: %s: %d pontos, %s: %d pontos\n", jogadores[0].nome, jogadores[0].pontos, jogadores[1].nome, jogadores[1].pontos);
                printf("Total de movimentos feitos: %d\n", movimentosFeitos);
                break; // Sai do loop principal do jogo
            }
            
            
        
            if(capturaOuPiao){
                movimentosSemCapturaouPiao = 0;
            } else {
                movimentosSemCapturaouPiao++;
            }

            if(movimentosSemCapturaouPiao >= 100){
                printf("Empate por regra dos 50 movimentos sem captura ou movimento de peao!\n");
                printf("Placar final: %s: %d pontos, %s: %d pontos\n", jogadores[0].nome, jogadores[0].pontos, jogadores[1].nome, jogadores[1].pontos);
                printf("Total de movimentos feitos: %d\n", movimentosFeitos);
                ganhou = true;
                break; // Sai do loop principal do jogo
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
    
    printf("-----------------------------------------------\n\n");

    return 0;
}