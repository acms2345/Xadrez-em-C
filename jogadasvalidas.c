#include "jogadasvalidas.h"
#include "traducao.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/*Note: The source code is entirely written in Portuguese now.*/

bool CasaAtacada(char tabuleiro[8][8], int linha, int coluna, int oponente){
    //Verificação de ataque de peões
    if(oponente == 0){
        if(linha + 1 < 8 && coluna - 1 >= 0 && tabuleiro[linha + 1][coluna - 1] == 'P') return true;
        if(linha + 1 < 8 && coluna + 1 < 8 && tabuleiro[linha + 1][coluna + 1] == 'P') return true;
    } else{
        if(linha - 1 >= 0 && coluna - 1 >= 0 && tabuleiro[linha - 1][coluna - 1] == 'p') return true;
        if(linha - 1 >= 0 && coluna + 1 < 8 && tabuleiro[linha - 1][coluna + 1] == 'p') return true;
    }

    char torre = (oponente == 0) ? 'T': 't';
    char rainha = (oponente == 0) ? 'Q' : 'q';

    //Verificação de ataques verticais (Torre ou rainha)
    for(int i = linha + 1; i < 8; i++){// Ataque de cima
        char peca = tabuleiro[i][coluna];
        if(peca != ' '){
            if (peca == torre || peca == rainha) return true;
            break;
        }
    }
    for(int i = linha - 1; i >= 0; i--){// Ataque de baixo
        char peca = tabuleiro[i][coluna];
        if(peca != ' '){
            if (peca == torre || peca == rainha) return true;
            break;
        }
    }
    //Verificação de ataques horizontais (Torre ou rainha)
    for(int i = coluna + 1; i < 8; i++){// Ataque da direita
        char peca = tabuleiro[linha][i];
        if(peca != ' '){
            if (peca == torre || peca == rainha) return true;
            break;
        }
    }
    for(int i = coluna - 1; i >= 0; i--){// Ataque da esquerda
        char peca = tabuleiro[linha][i];
        if(peca != ' '){
            if (peca == torre || peca == rainha) return true;
            break;
        }
    }

    //Verifica se há ataque de cavalo
    int movimentosCavalo[8][2] = {
    {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
    {1, -2}, {1, 2}, {2, -1}, {2, 1}
    };

    char cavalo = (oponente == 0) ? 'C' : 'c';

    /*Verifica as 8 possíveis posições de um cavalo,
    com base em movimentosCavalo[8][2]*/
    for(int i = 0; i < 8; i++){
        int linhaNova = linha + movimentosCavalo[i][0];
        int colunaNova = coluna + movimentosCavalo[i][1];

        if(linhaNova >= 0 && linhaNova < 8 && colunaNova >= 0 && colunaNova < 8){
            if (tabuleiro[linhaNova][colunaNova] == cavalo){
                return true;
            }
        }
    }

    //Verificação de ataques na diagonal (Bispo ou rainha)

    char bispo = (oponente == 0) ? 'B' : 'b';

    for(int i = 1; linha + i < 8 && coluna + i < 8; i++){//Para ver ataque a sudeste
        char peca = tabuleiro[linha + i][coluna + i];
        if(peca != ' '){
            if(peca == bispo || peca == rainha) return true;
            break;
        }
    }
    for(int i = 1; linha - i >= 0 && coluna + i < 8; i++){//Para ver ataque a nordeste
        char peca = tabuleiro[linha - i][coluna + i];
        if(peca != ' '){
            if(peca == bispo || peca == rainha) return true;
            break;
        }
    }
    for(int i = 1; linha + i < 8 && coluna - i >= 0; i++){//Para ver movimento para sudoeste
        char peca = tabuleiro[linha + i][coluna - i];
        if(peca != ' '){
            if(peca == bispo || peca == rainha) return true;
            break;
        }
    }
    for(int i = 1; linha - i >= 0 && coluna - i >= 0; i++){//Para ver movimento para noroeste
        char peca = tabuleiro[linha - i][coluna - i];
        if(peca != ' '){
            if(peca == bispo || peca == rainha) return true;
            break;
        }
    }

    //Verifica ataques do rei inimigo
    char reiInimigo = (oponente == 0) ? 'K' : 'k';

    int movimentosRei[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},  // Noroeste, Norte, Nordeste
        {0, -1},           {0, 1},    // Oeste, Leste
        {1, -1},  {1, 0},  {1, 1}     // Sudoeste, Sul, Sudeste
    };

    /*Verifica as 8 possíveis posições de um rei,
    com base em movimentosRei[8][2]*/
    for(int i = 0; i < 8; i++){
        int linhaNova = linha + movimentosRei[i][0];
        int colunaNova = coluna + movimentosRei[i][1];

        if(linhaNova >= 0 && linhaNova < 8 && colunaNova >= 0 && colunaNova < 8){
            if (tabuleiro[linhaNova][colunaNova] == reiInimigo){
                return true;
            }
        }
    }


    //Caso nenhuma das condições acima se aplicarem...
    return false; 
}
bool movimentoDeixaReiemXeque(char tabuleiro[8][8], int jogadorDaVez, int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino){
    char tabuleiroTemp[8][8];
    memcpy(tabuleiroTemp, tabuleiro, sizeof(char) * 8 * 8);

    tabuleiroTemp[linhaDestino][colunaDestino] = tabuleiroTemp[linhaOrigem][colunaOrigem];
    tabuleiroTemp[linhaOrigem][colunaOrigem] = ' ';

    char ReiDoJogador = (jogadorDaVez == 0) ? 'K' : 'k';

    int CoordenadaLinhaRei = -1;
    int CoordenadaColunaRei = -1;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if (tabuleiroTemp[i][j] == ReiDoJogador){
                CoordenadaLinhaRei = i;
                CoordenadaColunaRei = j;
            }
        }
    }

    return CasaAtacada(tabuleiroTemp, CoordenadaLinhaRei, CoordenadaColunaRei, (jogadorDaVez + 1) % 2);


}
bool ReiEmXeque(char tabuleiro[8][8], int jogadorDaVez){
    char ReiDoJogador = (jogadorDaVez == 0) ? 'K' : 'k';

    int CoordenadaLinhaRei = -1;
    int CoordenadaColunaRei = -1;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if (tabuleiro[i][j] == ReiDoJogador){
                CoordenadaLinhaRei = i;
                CoordenadaColunaRei = j;
            }
        }
    }
    return CasaAtacada(tabuleiro, CoordenadaLinhaRei, CoordenadaColunaRei, (jogadorDaVez + 1) % 2);
}
/*A função verifica se há algum movimento em que o jogador possa impedir o xeque-mate.*/
bool XequeMate(char tabuleiro[8][8], int JogadorDaVez){
    // 1️⃣ Primeiro verifica se está em xeque
    if(!ReiEmXeque(tabuleiro, JogadorDaVez)){
        return false; //O rei pode ficar na posição, se protegendo de um xeque-mate.
    }
    
    //Verifica todas as peças e possíveis movimentos.
    for(int linha = 0; linha < 8; linha++){
        for(int coluna = 0; coluna < 8; coluna++){
            char peca = tabuleiro[linha][coluna];

            if(peca == ' ') continue;

            if((JogadorDaVez == 0 && !isupper(peca)) || (JogadorDaVez == 1 && isupper(peca)))
                continue;
            
            for (int linhaDestino = 0; linhaDestino < 8; linhaDestino++)
            {
                for (int colunaDestino = 0; colunaDestino < 8; colunaDestino++)
                {
                    const char* resultado = JogadaValida(tabuleiro, linha, coluna, linhaDestino, colunaDestino, JogadorDaVez);

                    //Verifica se é um movimento válido.
                    if(strcmp(resultado, "OK") == 0){
                        //Verifica se esse movimento ESCAPA do xeque
                        if(!movimentoDeixaReiemXeque(tabuleiro, JogadorDaVez, linha, coluna, linhaDestino, colunaDestino)){
                            return false; //Tal movimento não deixa o rei em xeque-mate
                        }
                    }
                }
                
            }
            
        }
    }
    return true; //É xeque-mate.
}
/*A função retorna alguns valores de acordo com o seu resultado:
    - "OK" para jogadas válidas;
    - Outros textos para jogadas inválidas, para mostrar ao usuário o erro dele
        (Por exemplo, "Peça do mesmo jogador" quando ocorre tentativa de capturar uma peça do mesmo jogador)
        
*/
const char* JogadaValida(char tabuleiro[8][8], int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int jogadorDaVez) {
    char peca = tabuleiro[linhaOrigem][colunaOrigem];

    if(linhaOrigem == linhaDestino && colunaOrigem == colunaDestino) {
        return Msg(MSG_JOGADAS_MOVIMENTO_MESMA_POSICAO); // Movimento para a mesma posição

    } else if((jogadorDaVez == 0 && isupper(tabuleiro[linhaDestino][colunaDestino])) || ((jogadorDaVez == 1 && islower(tabuleiro[linhaDestino][colunaDestino])))) {
        return Msg(MSG_JOGADAS_PECA_MESMO_JOGADOR); // Tentativa de capturar uma peça do mesmo jogador

    } else if ((jogadorDaVez == 0 && islower(tabuleiro[linhaOrigem][colunaOrigem])) || (jogadorDaVez == 1 && isupper(tabuleiro[linhaOrigem][colunaOrigem]))) {
        return Msg(MSG_JOGADAS_MOVER_PECA_OPONENTE); // Tentativa de mover a peça do oponente
    } else {
        
        switch (toupper(peca))
        {
        case 'P':
            /* Código para movimento do peão */

            if(jogadorDaVez == 0) {
                if ((linhaDestino == linhaOrigem - 1 && colunaDestino == colunaOrigem - 1 && tabuleiro[linhaDestino][colunaDestino] != ' ')) {
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK"; // Movimento diagonal para capturar
                } else if ((linhaDestino == linhaOrigem - 1 && colunaDestino == colunaOrigem + 1 && tabuleiro[linhaDestino][colunaDestino] != ' ')) {
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK"; // Movimento diagonal para capturar
                } else if (linhaDestino == linhaOrigem - 1 && colunaDestino == colunaOrigem && tabuleiro[linhaDestino][colunaDestino] == ' '){
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK"; // Movimento para frente
                } else if (linhaOrigem == 6 && linhaDestino == linhaOrigem - 2 && colunaDestino == colunaOrigem && tabuleiro[linhaDestino - 1][colunaDestino] == ' ' && tabuleiro[linhaDestino][colunaDestino] == ' ') {
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK"; // Movimento de início para frente (duas casas)
                } else {
                    return Msg(MSG_JOGADAS_MOVIMENTO_INVALIDO_PEAO); // Movimento inválido para o peão
                }
            } else {
                if ((linhaDestino == linhaOrigem + 1 && colunaDestino == colunaOrigem - 1 && tabuleiro[linhaDestino][colunaDestino] != ' ')) {
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK"; // Movimento diagonal para capturar
                } else if ((linhaDestino == linhaOrigem + 1 && colunaDestino == colunaOrigem + 1 && tabuleiro[linhaDestino][colunaDestino] != ' ')) {
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK"; // Movimento diagonal para capturar
                } else if (linhaDestino == linhaOrigem + 1 && colunaDestino == colunaOrigem && tabuleiro[linhaDestino][colunaDestino] == ' '){
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK"; // Movimento para frente
                } else if (linhaOrigem == 1 && linhaDestino == linhaOrigem + 2 && colunaDestino == colunaOrigem && tabuleiro[linhaDestino - 1][colunaDestino] == ' ' && tabuleiro[linhaDestino][colunaDestino] == ' ') {
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK"; // Movimento de início para frente (duas casas)
                } else {
                    return Msg(MSG_JOGADAS_MOVIMENTO_INVALIDO_PEAO); // Movimento inválido para o peão
                }
            }
            break;
        
        case 'T':
            /* Código para movimento da torre */

            for(int i = 1; i + linhaOrigem < 8; i++){ //verifica se é movimento para baixo
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem){
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK";
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem] != ' '){
                    break;
                } 
            }
            for(int i = -1; i + linhaOrigem >= 0; i--){ //verifica se é movimento para cima
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem){
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK";
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem] != ' '){
                    break;
                }
            }
            for(int i = 1; i + colunaOrigem < 8; i++){ //verifica se é movimento para direita
                if(colunaDestino == colunaOrigem + i && linhaDestino == linhaOrigem){
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK";
                } else if (tabuleiro[linhaOrigem][colunaOrigem + i] != ' '){
                    break;
                }
            }
            for(int i = -1; i + colunaOrigem >= 0; i--){ //verifica se é movimento para esquerda
                if(colunaDestino == colunaOrigem + i && linhaDestino == linhaOrigem){
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK";
                } else if (tabuleiro[linhaOrigem][colunaOrigem + i] != ' '){
                    break;
                }
            }
            return Msg(MSG_JOGADAS_MOVIMENTO_INVALIDO_TORRE); // Movimento inválido para a torre
        
        case 'C':
            /* Código para movimento do cavalo */

            if(linhaDestino == linhaOrigem + 2 && colunaDestino == colunaOrigem - 1){
                if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                    return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                }
                return "OK"; // Movimento em "L" em pé para sudoeste
            } else if (linhaDestino == linhaOrigem - 2 && colunaDestino == colunaOrigem - 1){
                if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                    return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                }
                return "OK"; // Movimento em "L" em pé para noroeste
            } else if(linhaDestino == linhaOrigem + 2 && colunaDestino == colunaOrigem + 1){
                if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                    return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                }
                return "OK"; // Movimento em "L" em pé para sudeste
            } else if (linhaDestino == linhaOrigem - 2 && colunaDestino == colunaOrigem + 1){
                if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                    return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                }
                return "OK"; // Movimento em "L" em pé para nordeste
            } else if(linhaDestino == linhaOrigem + 1 && colunaDestino == colunaOrigem - 2){
                if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                    return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                }
                return "OK"; // Movimento em "L" deitado para sudoeste
            } else if (linhaDestino == linhaOrigem - 1 && colunaDestino == colunaOrigem - 2){
                if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                    return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                }
                return "OK"; // Movimento em "L" deitado para noroeste
            } else if(linhaDestino == linhaOrigem + 1 && colunaDestino == colunaOrigem + 2){
                if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                    return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                }
                return "OK"; // Movimento em "L" deitado para sudeste
            } else if (linhaDestino == linhaOrigem - 1 && colunaDestino == colunaOrigem + 2){
                if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                    return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                }
                return "OK"; // Movimento em "L" deitado para nordeste
            } else {
                return Msg(MSG_JOGADAS_MOVIMENTO_INVALIDO_CAVALO); // Movimento inválido para o cavalo
            }
            
            break;

        case 'B':
            /* Código para movimento do bispo */
            
            for(int i = 1; linhaOrigem + i < 8 && colunaOrigem + i < 8; i++){//Para ver movimento para sudeste
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem + i){
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK";
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem + i] != ' '){
                    break;
                }
            }
            for(int i = 1; linhaOrigem - i >= 0 && colunaOrigem + i < 8; i++){//Para ver movimento para nordeste
                if(linhaDestino == linhaOrigem - i && colunaDestino == colunaOrigem + i){
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK";
                } else if (tabuleiro[linhaOrigem - i][colunaOrigem + i] != ' '){
                    break;
                }
            }
            for(int i = 1; linhaOrigem + i < 8 && colunaOrigem - i >= 0; i++){//Para ver movimento para sudoeste
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem - i){
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK";
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem - i] != ' '){
                    break;
                }
            }
            for(int i = 1; linhaOrigem - i >= 0 && colunaOrigem - i >= 0; i++){//Para ver movimento para noroeste
                if(linhaDestino == linhaOrigem - i && colunaDestino == colunaOrigem - i){
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK";
                } else if (tabuleiro[linhaOrigem - i][colunaOrigem - i] != ' '){
                    break;
                }
            }
            return Msg(MSG_JOGADAS_MOVIMENTO_INVALIDO_BISPO);
            

        case 'Q':
            /* Código para movimento da rainha */

            //Junção dos movimentos da torre e do bispo

            // Movimento da torre
            for(int i = 1; i + linhaOrigem < 8; i++){ //verifica se é movimento para baixo
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem){
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK";
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem] != ' '){
                    break;
                }
            }
            for(int i = -1; i + linhaOrigem >= 0; i--){ //verifica se é movimento para cima
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem){
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK";
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem] != ' '){
                    break;
                }
            }
            for(int i = 1; i + colunaOrigem < 8; i++){ //verifica se é movimento para direita
                if(colunaDestino == colunaOrigem + i && linhaDestino == linhaOrigem){
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK";
                } else if (tabuleiro[linhaOrigem][colunaOrigem + i] != ' '){
                    break;
                }
            }
            for(int i = -1; i + colunaOrigem >= 0; i--){ //verifica se é movimento para esquerda
                if(colunaDestino == colunaOrigem + i && linhaDestino == linhaOrigem){
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK";
                } else if (tabuleiro[linhaOrigem][colunaOrigem + i] != ' '){
                    break;
                }
            }

            // Movimento do bispo
            for(int i = 1; linhaOrigem + i < 8 && colunaOrigem + i < 8; i++){//Para ver movimento para sudeste
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem + i){
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK";
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem + i] != ' '){
                    break;
                }
            }
            for(int i = 1; linhaOrigem - i >= 0 && colunaOrigem + i < 8; i++){//Para ver movimento para nordeste
                if(linhaDestino == linhaOrigem - i && colunaDestino == colunaOrigem + i){
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK";
                } else if (tabuleiro[linhaOrigem - i][colunaOrigem + i] != ' '){
                    break;
                }
            }
            for(int i = 1; linhaOrigem + i < 8 && colunaOrigem - i >= 0; i++){//Para ver movimento para sudoeste
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem - i){
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK";
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem - i] != ' '){
                    break;
                }
            }
            for(int i = 1; linhaOrigem - i >= 0 && colunaOrigem - i >= 0; i++){//Para ver movimento para noroeste
                if(linhaDestino == linhaOrigem - i && colunaDestino == colunaOrigem - i){
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE);
                    }
                    return "OK";
                } else if (tabuleiro[linhaOrigem - i][colunaOrigem - i] != ' '){
                    break;
                }
            }

            return Msg(MSG_JOGADAS_MOVIMENTO_INVALIDO_RAINHA);

        case 'K':
            /* Código para movimento do rei */

            if((linhaDestino == linhaOrigem + 1 || linhaDestino == linhaOrigem - 1 || linhaDestino == linhaOrigem) &&
               (colunaDestino == colunaOrigem + 1 || colunaDestino == colunaOrigem - 1 || colunaDestino == colunaOrigem)) {
                if(CasaAtacada(tabuleiro, linhaDestino, colunaDestino, 1 - jogadorDaVez)){
                    return Msg(MSG_JOGADAS_CASA_DESTINO_XEQUE); // Casa de destino está sob ataque
                } else{
                    
                    if(movimentoDeixaReiemXeque(tabuleiro, jogadorDaVez, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)){
                        return Msg(MSG_JOGADAS_DEIXA_REI_XEQUE); // Movimento colocaria o rei em xeque
                    } else {
                        return "OK"; // Movimento válido
                    }
                }
                    
            } else {
                return Msg(MSG_JOGADAS_MOVIMENTO_INVALIDO_REI); // Movimento inválido para o rei
            }
            break;

        default: //Se não for nenhuma peça válida
            return Msg(MSG_JOGADAS_PECA_INVALIDA);

        }
        
    }
    
    
    
}
