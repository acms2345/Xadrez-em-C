#include "jogadasvalidas.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


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
/*A função retorna alguns valores de acordo com o seu resultado:
    - "OK" para jogadas válidas;
    - Outros textos para jogadas inválidas, para mostrar ao usuário o erro dele
        (Por exemplo, "Peça do mesmo jogador" quando ocorre tentativa de capturar uma peça do mesmo jogador)
        
*/
const char* JogadaValida(char tabuleiro[8][8], int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int jogadorDaVez) {
    char peca = tabuleiro[linhaOrigem][colunaOrigem];

    if(linhaOrigem == linhaDestino && colunaOrigem == colunaDestino) {
        return "Movimento para a mesma posicao"; // Movimento para a mesma posição

    } else if((jogadorDaVez == 0 && isupper(tabuleiro[linhaDestino][colunaDestino])) || ((jogadorDaVez == 1 && islower(tabuleiro[linhaDestino][colunaDestino])))) {
        return "Peca do mesmo jogador"; // Tentativa de capturar uma peça do mesmo jogador

    } else if ((jogadorDaVez == 0 && islower(tabuleiro[linhaOrigem][colunaOrigem])) || (jogadorDaVez == 1 && isupper(tabuleiro[linhaOrigem][colunaOrigem]))) {
        return "Tentativa de mover peca do oponente"; // Tentativa de mover a peça do oponente
    } else {
        
        switch (toupper(peca))
        {
        case 'P':
            /* Código para movimento do peão */

            if(jogadorDaVez == 0) {
                if ((linhaDestino == linhaOrigem - 1 && colunaDestino == colunaOrigem - 1 && tabuleiro[linhaDestino][colunaDestino] != ' ')) {
                    return "OK"; // Movimento diagonal para capturar
                } else if ((linhaDestino == linhaOrigem - 1 && colunaDestino == colunaOrigem + 1 && tabuleiro[linhaDestino][colunaDestino] != ' ')) {
                    return "OK"; // Movimento diagonal para capturar
                } else if (linhaDestino == linhaOrigem - 1 && colunaDestino == colunaOrigem && tabuleiro[linhaDestino][colunaDestino] == ' '){
                    return "OK"; // Movimento para frente
                } else if (linhaOrigem == 6 && linhaDestino == linhaOrigem - 2 && colunaDestino == colunaOrigem && tabuleiro[linhaDestino - 1][colunaDestino] == ' ' && tabuleiro[linhaDestino][colunaDestino] == ' ') {
                    return "OK"; // Movimento de início para frente (duas casas)
                } else {
                    return "Movimento invalido para o peao"; // Movimento inválido para o peão
                }
            } else {
                if ((linhaDestino == linhaOrigem + 1 && colunaDestino == colunaOrigem - 1 && tabuleiro[linhaDestino][colunaDestino] != ' ')) {
                    return "OK"; // Movimento diagonal para capturar
                } else if ((linhaDestino == linhaOrigem + 1 && colunaDestino == colunaOrigem + 1 && tabuleiro[linhaDestino][colunaDestino] != ' ')) {
                    return "OK"; // Movimento diagonal para capturar
                } else if (linhaDestino == linhaOrigem + 1 && colunaDestino == colunaOrigem && tabuleiro[linhaDestino][colunaDestino] == ' '){
                    return "OK"; // Movimento para frente
                } else if (linhaOrigem == 1 && linhaDestino == linhaOrigem + 2 && tabuleiro[linhaDestino + 1][colunaDestino] == ' ' && tabuleiro[linhaDestino][colunaDestino] == ' ') {
                    return "OK"; // Movimento de início para frente (duas casas)
                } else {
                    return "Movimento invalido para o peao"; // Movimento inválido para o peão
                }
            }
            break;
        
        case 'T':
            /* Código para movimento da torre */

            for(int i = 1; i + linhaOrigem < 8; i++){ //verifica se é movimento para baixo
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem){
                    return "OK";
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem] != ' '){
                    break;
                } 
            }
            for(int i = -1; i + linhaOrigem >= 0; i--){ //verifica se é movimento para cima
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem){
                    return "OK";
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem] != ' '){
                    break;
                }
            }
            for(int i = 1; i + colunaOrigem < 8; i++){ //verifica se é movimento para direita
                if(colunaDestino == colunaOrigem + i && linhaDestino == linhaOrigem){
                    return "OK";
                } else if (tabuleiro[linhaOrigem][colunaOrigem + i] != ' '){
                    break;
                }
            }
            for(int i = -1; i + colunaOrigem >= 0; i--){ //verifica se é movimento para esquerda
                if(colunaDestino == colunaOrigem + i && linhaDestino == linhaOrigem){
                    return "OK";
                } else if (tabuleiro[linhaOrigem][colunaOrigem + i] != ' '){
                    break;
                }
            }
            return "Movimento invalido para a torre";
        
        case 'C':
            /* Código para movimento do cavalo */

            if(linhaDestino == linhaOrigem + 2 && colunaDestino == colunaOrigem - 1){
                return "OK"; // Movimento em "L" em pé para sudoeste
            } else if (linhaDestino == linhaOrigem - 2 && colunaDestino == colunaOrigem - 1){
                return "OK"; // Movimento em "L" em pé para noroeste
            } else if(linhaDestino == linhaOrigem + 2 && colunaDestino == colunaOrigem + 1){
                return "OK"; // Movimento em "L" em pé para sudeste
            } else if (linhaDestino == linhaOrigem - 2 && colunaDestino == colunaOrigem + 1){
                return "OK"; // Movimento em "L" em pé para nordeste
            } else if(linhaDestino == linhaOrigem + 1 && colunaDestino == colunaOrigem - 2){
                return "OK"; // Movimento em "L" deitado para sudoeste
            } else if (linhaDestino == linhaOrigem - 1 && colunaDestino == colunaOrigem - 2){
                return "OK"; // Movimento em "L" deitado para noroeste
            } else if(linhaDestino == linhaOrigem + 1 && colunaDestino == colunaOrigem + 2){
                return "OK"; // Movimento em "L" deitado para sudeste
            } else if (linhaDestino == linhaOrigem - 1 && colunaDestino == colunaOrigem + 2){
                return "OK"; // Movimento em "L" deitado para nordeste
            } else {
                return "Movimento invalido para o cavalo";
            }
            
            break;

        case 'B':
            /* Código para movimento do bispo */
            
            for(int i = 1; linhaOrigem + i < 8 && colunaOrigem + i < 8; i++){//Para ver movimento para sudeste
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem + i){
                    return "OK";
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem + i] != ' '){
                    break;
                }
            }
            for(int i = 1; linhaOrigem - i >= 0 && colunaOrigem + i < 8; i++){//Para ver movimento para nordeste
                if(linhaDestino == linhaOrigem - i && colunaDestino == colunaOrigem + i){
                    return "OK";
                } else if (tabuleiro[linhaOrigem - i][colunaOrigem + i] != ' '){
                    break;
                }
            }
            for(int i = 1; linhaOrigem + i < 8 && colunaOrigem - i >= 0; i++){//Para ver movimento para sudoeste
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem - i){
                    return "OK";
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem - i] != ' '){
                    break;
                }
            }
            for(int i = 1; linhaOrigem - i >= 0 && colunaOrigem - i >= 0; i++){//Para ver movimento para noroeste
                if(linhaDestino == linhaOrigem - i && colunaDestino == colunaOrigem - i){
                    return "OK";
                } else if (tabuleiro[linhaOrigem - i][colunaOrigem - i] != ' '){
                    break;
                }
            }
            return "Movimento invalido para o bispo";
            

        case 'Q':
            /* Código para movimento da rainha */

            //Junção dos movimentos da torre e do bispo

            // Movimento da torre
            for(int i = 1; i + linhaOrigem < 8; i++){ //verifica se é moviemento para baixo
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem){
                    return "OK";
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem] != ' '){
                    break;
                }
            }
            for(int i = -1; i + linhaOrigem >= 0; i--){ //verifica se é movimento para cima
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem){
                    return "OK";
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem] != ' '){
                    break;
                }
            }
            for(int i = 1; i + colunaOrigem < 8; i++){ //verifica se é movimento para direita
                if(colunaDestino == colunaOrigem + i && linhaDestino == linhaOrigem){
                    return "OK";
                } else if (tabuleiro[linhaOrigem][colunaOrigem + i] != ' '){
                    break;
                }
            }
            for(int i = -1; i + colunaOrigem >= 0; i--){ //verifica se é movimento para esquerda
                if(colunaDestino == colunaOrigem + i && linhaDestino == linhaOrigem){
                    return "OK";
                } else if (tabuleiro[linhaOrigem][colunaOrigem + i] != ' '){
                    break;
                }
            }

            // Movimento do bispo
            for(int i = 1; linhaOrigem + i < 8 && colunaOrigem + i < 8; i++){//Para ver movimento para sudeste
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem + i){
                    return "OK";
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem + i] != ' '){
                    break;
                }
            }
            for(int i = 1; linhaOrigem - i >= 0 && colunaOrigem + i < 8; i++){//Para ver movimento para nordeste
                if(linhaDestino == linhaOrigem - i && colunaDestino == colunaOrigem + i){
                    return "OK";
                } else if (tabuleiro[linhaOrigem - i][colunaOrigem + i] != ' '){
                    break;
                }
            }
            for(int i = 1; linhaOrigem + i < 8 && colunaOrigem - i >= 0; i++){//Para ver movimento para sudoeste
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem - i){
                    return "OK";
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem - i] != ' '){
                    break;
                }
            }
            for(int i = 1; linhaOrigem - i >= 0 && colunaOrigem - i >= 0; i++){//Para ver movimento para noroeste
                if(linhaDestino == linhaOrigem - i && colunaDestino == colunaOrigem - i){
                    return "OK";
                } else if (tabuleiro[linhaOrigem - i][colunaOrigem - i] != ' '){
                    break;
                }
            }

            return "Movimento invalido para a rainha";

        case 'K':
            /* Código para movimento do rei */

            if((linhaDestino == linhaOrigem + 1 || linhaDestino == linhaOrigem - 1 || linhaDestino == linhaOrigem) &&
               (colunaDestino == colunaOrigem + 1 || colunaDestino == colunaOrigem - 1 || colunaDestino == colunaOrigem)) {
                if(!CasaAtacada(tabuleiro, linhaDestino, colunaDestino, 1 - jogadorDaVez)){
                    return "OK"; // Movimento válido para o rei (uma casa em qualquer direção)
                } else{
                    return "Casa de destino em xeque";
                }
                    
            } else {
                return "Movimento invalido para o rei"; // Movimento inválido para o rei
            }
            break;

        default: //Se não for nenhuma peça válida
            return "Peça invalida";

        }
        
    }
    
    
    
}
