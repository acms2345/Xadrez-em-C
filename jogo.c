#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "jogadasvalidas.h"
#include "jogo.h"
#include "traducao.h"
#include "cores.h"

/*Note: The source code is entirely written in Portuguese now.*/

void limpezaBuffer(){
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void trim(char *str){
    str[strcspn(str, "\n\r")] = '\0'; //Tira o newline

    int contagemInicio = 0;
    while(str[contagemInicio] == ' ' || str[contagemInicio] == '\t') contagemInicio++;
    /*O while acima conta onde realmente começa o texto da string.
    Por exemplo, na string " desistir", haverá uma contagem até onde realmente começa o texto
    (que é o caractere 'd').
    OBS: '\t' = caractere Tab.*/

    int contagemFinal = (int)strlen(str) - 1;
    while(contagemFinal >= contagemInicio && (str[contagemFinal] == ' ' || str[contagemFinal] == '\t')) contagemFinal--;

    if (contagemInicio <= contagemFinal){ //Ou seja, se houver algum texto (não-espaço) na string:
        memmove(str, &str[contagemInicio], contagemFinal - contagemInicio + 1);
        str[contagemFinal - contagemInicio + 1] = '\0';
    } else{
        str[0] = '\0'; //String vazia.
    }
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

static const char* ObterSimboloPeca(char peca) {
    static const char* simbolos[] = {
        ['P'] = "♙",
        ['T'] = "♖",
        ['C'] = "♘",
        ['B'] = "♗",
        ['Q'] = "♕",
        ['K'] = "♔",

        ['p'] = "♟",
        ['t'] = "♜",
        ['c'] = "♞",
        ['b'] = "♝",
        ['q'] = "♛",
        ['k'] = "♚",

        [' '] = " "
    };

    int ConversorIndice = (int)peca;
    if(ConversorIndice < sizeof(simbolos) / sizeof(simbolos[0]) && simbolos[ConversorIndice] != NULL){
        return simbolos[ConversorIndice];
    }
    return " "; // Caso de segurança
}

static void ExibirTabuleiro() {
    printf("  ╔═════════════════╗\n");
    printf("  ║ a b c d e f g h ║\n");
    printf("  ╠═════════════════╣\n");
    for (int i = 8; i >= 1; i--) {
        int conversaoLinha = 8 - i;
        printf("%d ║ ", i);
        
        for (int j = 0; j < 8; j++) {
            char* backgroundColor = (conversaoLinha + j) % 2 == 0 ? BRANCO_BACKGROUND : PRETO_BACKGROUND;
            char* textColor = (conversaoLinha + j) % 2 == 0 ? PRETO_FOREGROUND : BRANCO_FOREGROUND;
            
            printf("%s", backgroundColor);
            printf("%s ", ObterSimboloPeca(tabuleiro[conversaoLinha][j]));
            printf("%s", RESET);
        }
        printf("║\n");
    }
    printf("  ╚═════════════════╝\n");
}

/**
 * Solicita ao jogador que insira uma jogada no formato de notação algébrica.
 * Parâmetros:
 *   linhaOrigem, colunaOrigem: ponteiros para armazenar a linha e coluna de origem.
 *   linhaDestino, colunaDestino: ponteiros para armazenar a linha e coluna de destino.
 * O jogador pode digitar "salvar" para salvar o jogo atual.
 * O jogador pode digitar "desistir" para dar a vitória ao oponente.
 */
static bool obterCoordenada(int *linhaOrigem, int *colunaOrigem, int *linhaDestino, int *colunaDestino){
    char input[10];

    while(1){
        printf(Msg(MSG_JOGO_DIGITE_JOGADA), jogadores[jogadorDaVez].nome);
        
        char* retornoInput = fgets(input, sizeof(input), stdin);
        if(retornoInput == NULL){
            if(feof(stdin)){//Verifica se é EOF para encerrar o jogo, caso o jogador use Ctrl+D ou Ctrl+Z
                printf(Msg(MSG_JOGO_ENCERRAMENTO_EOF));
                ganhou = true;
                return false; // Indica que o jogo deve ser encerrado
            }

            else if(ferror(stdin)){// Verifica se é erro de leitura (problema no stream)
                printfColor(VERMELHO_FOREGROUND, Msg(MSG_JOGO_JOGADA_INVALIDA));

                clearerr(stdin); // Limpa o estado de erro do stream
                
                limpezaBuffer();
                
                continue;
            }

            //O bloco abaixo serve como caso anômalo
            printfColor(VERMELHO_FOREGROUND, Msg(MSG_JOGO_JOGADA_INVALIDA));
            continue;

        }  
        // Após fgets, antes de strcmp:
        trim(input);
        

        

        if(strcmp(input, "salvar") == 0 || strcmp(input, "SALVAR") == 0 || 
        strcmp(input, "save") == 0 || strcmp(input, "SAVE") == 0){
            if(SalvarJogo()){
                printfColor(VERDE_FOREGROUND, Msg(MSG_JOGO_SALVAR_SUCESSO));
            } else {
                printfColor(VERMELHO_FOREGROUND, Msg(MSG_JOGO_SALVAR_ERRO));
            }
            continue;
        }

        if(strcmp(input, "desistir") == 0 || strcmp(input, "DESISTIR") == 0 || strcmp(input, "resign") == 0 || strcmp(input, "RESIGN") == 0){
            printf(Msg(MSG_JOGO_DESISTENCIA), jogadores[jogadorDaVez].nome, jogadores[1 - jogadorDaVez].nome);
            ganhou = true;
            return false;
        }

        if (strcmp(input, "empatar") == 0 || strcmp(input, "EMPATAR") == 0 || strcmp(input, "draw") == 0 || strcmp(input, "DRAW") == 0){
            printf(Msg(MSG_JOGO_EMPATE_SUGESTAO), jogadores[jogadorDaVez].nome, jogadores[1 - jogadorDaVez].nome);
            char resposta[4];
            char *inputResposta = fgets(resposta, sizeof(resposta), stdin);

            if(inputResposta){
                trim(resposta);
                
                if((strcmp(resposta, "y") == 0 || strcmp(resposta, "Y") == 0) || (strcmp(resposta, "s") == 0 || strcmp(resposta, "S") == 0)){
                    printf(Msg(MSG_JOGO_EMPATE_ACEITO), jogadores[1 - jogadorDaVez].nome);
                    ganhou = true;
                    return false;
                } else if(strcmp(resposta, "n") == 0 || strcmp(resposta, "N") == 0){
                    continue;
                } else {
                    printfColor(VERMELHO_FOREGROUND, Msg(MSG_JOGO_JOGADA_INVALIDA));
                    continue;
                }
            } else{
                printfColor(VERMELHO_FOREGROUND, Msg(MSG_JOGO_JOGADA_INVALIDA));
                continue;
            }
            continue; //Impede que caia para a verificação de casas.
        }
        

        //Para notação sem separação (ex: e2e4)
        if(strlen(input) == 4){
            if(tolower(input[0]) < 'a' || tolower(input[0]) > 'h'){
                printfColor(VERMELHO_FOREGROUND, Msg(MSG_JOGO_COLUNA_ORIGEM_INVALIDA));
                continue;
            }
            *colunaOrigem = tolower(input[0]) - 'a';
        
            if(input[1] < '1' || input[1] > '8'){
                printfColor(VERMELHO_FOREGROUND, Msg(MSG_JOGO_LINHA_ORIGEM_INVALIDA));
                continue;
            }
            
            int conversaoLinhaOrigem = input[1] - '0';
            *linhaOrigem = 8 - conversaoLinhaOrigem;

            if(tolower(input[2]) < 'a' || tolower(input[2]) > 'h'){
                printfColor(VERMELHO_FOREGROUND, Msg(MSG_JOGO_COLUNA_DESTINO_INVALIDA));
                continue;
            }
            *colunaDestino = tolower(input[2]) - 'a';

            if(input[3] < '1' || input[3] > '8'){
                printfColor(VERMELHO_FOREGROUND, Msg(MSG_JOGO_LINHA_DESTINO_INVALIDA));
                continue;
            }
            
            
            int conversaoLinhaDestino = input[3] - '0';
            *linhaDestino = 8 - conversaoLinhaDestino;
                
            
            break;
        } 
        //Notação com separador (ex: e2-e4)
        else if (strlen(input) == 5){
            if ((input[2] != ' ') && (input[2] != '-')){
                printfColor(VERMELHO_FOREGROUND, Msg(MSG_JOGO_SEPARADOR_COORDENADAS_INVALIDO));
                continue;
            }
            if(tolower(input[0]) < 'a' || tolower(input[0]) > 'h'){
                printfColor(VERMELHO_FOREGROUND, Msg(MSG_JOGO_COLUNA_ORIGEM_INVALIDA));
                continue;
            }
            *colunaOrigem = tolower(input[0]) - 'a';
        
            if(input[1] < '1' || input[1] > '8'){
                printfColor(VERMELHO_FOREGROUND, Msg(MSG_JOGO_LINHA_ORIGEM_INVALIDA));
                continue;
            }
            
            int conversaoLinhaOrigem = input[1] - '0';
            *linhaOrigem = 8 - conversaoLinhaOrigem;

            if(tolower(input[3]) < 'a' || tolower(input[3]) > 'h'){
                printfColor(VERMELHO_FOREGROUND, Msg(MSG_JOGO_COLUNA_DESTINO_INVALIDA));
                continue;
            }
            *colunaDestino = tolower(input[3]) - 'a';

            if(input[4] < '1' || input[4] > '8'){
                printfColor(VERMELHO_FOREGROUND, Msg(MSG_JOGO_LINHA_DESTINO_INVALIDA));
                continue;
            }
            
            
            int conversaoLinhaDestino = input[4] - '0';
            *linhaDestino = 8 - conversaoLinhaDestino;
                
            
            break;
        } else{
            printfColor(VERMELHO_FOREGROUND, Msg(MSG_JOGO_FORMATO_COORDENADAS_INVALIDO));
            continue;
        }
        
    }
    
    return true;
}
/*Função para a promoção de peão.
Ela solicita a peça para a qual o usuário vai querer promover.*/
static char PromocaoPeao(int linhaDestino, int colunaDestino, int jogadorDaVez) {
    char escolha;
    printf(Msg(MSG_JOGO_PROMOCAO_PEAO_ESCOLHA_PECA));
    while (1) {
        scanf(" %c", &escolha);
        
        limpezaBuffer();

        if(jogadorDaVez == 0) {
            escolha = toupper(escolha);
        } else {
            escolha = tolower(escolha);
        }
        if (((escolha == 'Q' || escolha == 'C' || escolha == 'B' || escolha == 'T') && jogadorDaVez == 0) ||
            ((escolha == 'q' || escolha == 'c' || escolha == 'b' || escolha == 't') && jogadorDaVez == 1)) {
            return escolha;
        } else {
            printfColor(VERMELHO_FOREGROUND, Msg(MSG_JOGO_PROMOCAO_PEAO_PECA_INVALIDA));
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
        printfColor(VERMELHO_FOREGROUND, Msg(MSG_JOGO_SALVAR_ERRO_ABERTURA_ARQUIVO));
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
        printfColor(VERMELHO_FOREGROUND, Msg(MSG_JOGO_CARREGAR_ERRO));
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
            printf(Msg(MSG_JOGO_DIGITE_JOGADOR), i + 1);
            scanf("%19s", jogadores[i].nome);
            jogadores[i].pontos = 0;
        }
        limpezaBuffer();
        movimentosSemCapturaouPiao = 0;
        movimentosFeitos = 0;
    } else {
        if(!CarregarJogo()){
            for(int i = 0; i < 2; i++){
                printf(Msg(MSG_JOGO_DIGITE_JOGADOR), i + 1);
                scanf("%19s", jogadores[i].nome);
                jogadores[i].pontos = 0;
             }
             limpezaBuffer();
             movimentosSemCapturaouPiao = 0;
             movimentosFeitos = 0;
        }
    }
    


    while(!ganhou){
        capturaOuPiao = false;
        
        printf("\n");
        ExibirTabuleiro();

        printf(Msg(MSG_JOGO_VEZ_JOGADOR), jogadores[jogadorDaVez].nome, (jogadorDaVez == 0) 
        ? Msg(MSG_JOGO_MAIUSCULAS) : Msg(MSG_JOGO_MINUSCULAS));

        int linhaOrigem, colunaOrigem, linhaDestino, colunaDestino;

        if(!obterCoordenada(&linhaOrigem, &colunaOrigem, &linhaDestino, &colunaDestino)){
            break; // Sai do loop principal do jogo se o jogador desistir
        }
        


        if(tabuleiro[linhaOrigem][colunaOrigem] == ' '){
            printfColor(VERMELHO_FOREGROUND, Msg(MSG_JOGO_POSICAO_ORIGEM_VAZIA));
            
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
                printfSColor(NEGRITO, AMARELO_FOREGROUND, Msg(MSG_JOGO_XEQUEMATE_REI_CAPTURADO_TITULO));
                printf(Msg(MSG_JOGO_XEQUEMATE_VENCEDOR), jogadores[jogadorDaVez].nome);
                printf(Msg(MSG_JOGO_XEQUEMATE_PLACAR), jogadores[0].nome, jogadores[0].pontos, jogadores[1].nome, jogadores[1].pontos);
                printf(Msg(MSG_JOGO_XEQUEMATE_TOTAL_MOVIMENTOS), movimentosFeitos);
                break; // Sai do loop principal do jogo
            }
            
            
        
            if(capturaOuPiao){
                movimentosSemCapturaouPiao = 0;
            } else {
                movimentosSemCapturaouPiao++;
            }

            if(movimentosSemCapturaouPiao >= 100){
                printf(Msg(MSG_JOGO_EMPATE_50MOVIMENTOS_TITULO));
                printf(Msg(MSG_JOGO_XEQUEMATE_PLACAR), jogadores[0].nome, jogadores[0].pontos, jogadores[1].nome, jogadores[1].pontos);
                printf(Msg(MSG_JOGO_XEQUEMATE_TOTAL_MOVIMENTOS), movimentosFeitos);
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

            if(XequeMate(tabuleiro, jogadorDaVez)){
                ganhou = true;
                printfSColor(NEGRITO, AMARELO_FOREGROUND, Msg(MSG_JOGO_XEQUEMATE_TITULO));
                printf(Msg(MSG_JOGO_XEQUEMATE_VENCEDOR), jogadores[1 - jogadorDaVez].nome);
                printf(Msg(MSG_JOGO_XEQUEMATE_PLACAR), jogadores[0].nome, jogadores[0].pontos, jogadores[1].nome, jogadores[1].pontos);
                printf(Msg(MSG_JOGO_XEQUEMATE_TOTAL_MOVIMENTOS), movimentosFeitos);
                break; // Sai do loop principal do jogo
            }
            if(Afogamento(tabuleiro, jogadorDaVez)){
                ganhou = true;
                printfSColor(NEGRITO, AMARELO_FOREGROUND, Msg(MSG_JOGO_AFOGAMENTO_TITULO));
                printf(Msg(MSG_JOGO_EMPATE_TEXTO));
                printf(Msg(MSG_JOGO_XEQUEMATE_PLACAR), jogadores[0].nome, jogadores[0].pontos, jogadores[1].nome, jogadores[1].pontos);
                printf(Msg(MSG_JOGO_XEQUEMATE_TOTAL_MOVIMENTOS), movimentosFeitos);
                break; // Sai do loop principal do jogo
            }

        } else {
            printf("%s", VERMELHO_FOREGROUND);
            printf(Msg(MSG_JOGO_JOGADA_INVALIDA), resultadoJogadaValida);
            printf("%s", RESET);
        }

    }
    
    printf("-----------------------------------------------\n\n");

    return 0;
}