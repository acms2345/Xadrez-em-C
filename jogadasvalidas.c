#include "jogadasvalidas.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


bool JogadaValida(char tabuleiro[8][8], int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int jogadorDaVez) {
    char peca = tabuleiro[linhaOrigem][colunaOrigem];

    if(linhaOrigem == linhaDestino && colunaOrigem == colunaDestino) {
        return false; // Movimento para a mesma posição

    } else if((jogadorDaVez == 0 && isupper(tabuleiro[linhaDestino][colunaDestino])) || ((jogadorDaVez == 1 && islower(tabuleiro[linhaDestino][colunaDestino])))) {
        return false; // Tentativa de capturar uma peça do mesmo jogador

    } else if ((jogadorDaVez == 0 && islower(tabuleiro[linhaOrigem][colunaOrigem])) || (jogadorDaVez == 1 && isupper(tabuleiro[linhaOrigem][colunaOrigem]))) {
        return false; // Tentativa de mover a peça do oponente
        
    } else {
        
        switch (toupper(peca))
        {
        case 'P':
            /* Código para movimento do peão */

            if(jogadorDaVez == 0) {
                if ((linhaDestino == linhaOrigem - 1 && colunaDestino == colunaOrigem - 1 && tabuleiro[linhaDestino][colunaDestino] != ' ')) {
                    return true; // Movimento diagonal para capturar
                } else if ((linhaDestino == linhaOrigem - 1 && colunaDestino == colunaOrigem + 1 && tabuleiro[linhaDestino][colunaDestino] != ' ')) {
                    return true; // Movimento diagonal para capturar
                } else if (linhaDestino == linhaOrigem - 1 && colunaDestino == colunaOrigem && tabuleiro[linhaDestino][colunaDestino] == ' '){
                    return true; // Movimento para frente
                } else if (linhaOrigem == 6 && linhaDestino == linhaOrigem - 2 && tabuleiro[linhaDestino - 1][colunaDestino] == ' ' && tabuleiro[linhaDestino][colunaDestino] == ' ') {
                    return true; // Movimento de início para frente (duas casas)
                } else {
                    return false; // Movimento inválido para o peão
                }
            } else {
                if ((linhaDestino == linhaOrigem + 1 && colunaDestino == colunaOrigem - 1 && tabuleiro[linhaDestino][colunaDestino] != ' ')) {
                    return true; // Movimento diagonal para capturar
                } else if ((linhaDestino == linhaOrigem + 1 && colunaDestino == colunaOrigem + 1 && tabuleiro[linhaDestino][colunaDestino] != ' ')) {
                    return true; // Movimento diagonal para capturar
                } else if (linhaDestino == linhaOrigem + 1 && colunaDestino == colunaOrigem && tabuleiro[linhaDestino][colunaDestino] == ' '){
                    return true; // Movimento para frente
                } else if (linhaOrigem == 1 && linhaDestino == linhaOrigem + 2 && tabuleiro[linhaDestino][colunaDestino] == ' ') {
                    return true; // Movimento de início para frente (duas casas)
                } else {
                    return false; // Movimento inválido para o peão
                }
            }
            break;
        
        case 'T':
            /* Código para movimento da torre */

            for(int i = 1; i + linhaOrigem < 8; i++){ //verifica se é movimento para baixo
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem){
                    return true;
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem] != ' '){
                    break;
                } 
            }
            for(int i = -1; i + linhaOrigem >= 0; i--){ //verifica se é movimento para cima
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem){
                    return true;
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem] != ' '){
                    break;
                }
            }
            for(int i = 1; i + colunaOrigem < 8; i++){ //verifica se é movimento para direita
                if(colunaDestino == colunaOrigem + i && linhaDestino == linhaOrigem){
                    return true;
                } else if (tabuleiro[linhaOrigem][colunaOrigem + i] != ' '){
                    break;
                }
            }
            for(int i = -1; i + colunaOrigem >= 0; i--){ //verifica se é movimento para esquerda
                if(colunaDestino == colunaOrigem + i && linhaDestino == linhaOrigem){
                    return true;
                } else if (tabuleiro[linhaOrigem][colunaOrigem + i] != ' '){
                    break;
                }
            }
            return false; // Movimento inválido para a torre
        
        case 'C':
            /* Código para movimento do cavalo */

            if(linhaDestino == linhaOrigem + 2 && colunaDestino == colunaOrigem - 1){
                return true; // Movimento em "L" em pé para sudoeste
            } else if (linhaDestino == linhaOrigem - 2 && colunaDestino == colunaOrigem - 1){
                return true; // Movimento em "L" em pé para noroeste
            } else if(linhaDestino == linhaOrigem + 2 && colunaDestino == colunaOrigem + 1){
                return true; // Movimento em "L" em pé para sudeste
            } else if (linhaDestino == linhaOrigem - 2 && colunaDestino == colunaOrigem + 1){
                return true; // Movimento em "L" em pé para nordeste
            } else if(linhaDestino == linhaOrigem + 1 && colunaDestino == colunaOrigem - 2){
                return true; // Movimento em "L" deitado para sudoeste
            } else if (linhaDestino == linhaOrigem - 1 && colunaDestino == colunaOrigem - 2){
                return true; // Movimento em "L" deitado para noroeste
            } else if(linhaDestino == linhaOrigem + 1 && colunaDestino == colunaOrigem + 2){
                return true; // Movimento em "L" deitado para sudeste
            } else if (linhaDestino == linhaOrigem - 1 && colunaDestino == colunaOrigem + 2){
                return true; // Movimento em "L" deitado para nordeste
            } else {
                return false; // Movimento inválido para o cavalo
            }
            
            break;

        case 'B':
            /* Código para movimento do bispo */
            
            for(int i = 1; linhaOrigem + i < 8 && colunaOrigem + i < 8; i++){//Para ver movimento para sudeste
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem + i){
                    return true;
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem + i] != ' '){
                    break;
                }
            }
            for(int i = 1; linhaOrigem - i >= 0 && colunaOrigem + i < 8; i++){//Para ver movimento para nordeste
                if(linhaDestino == linhaOrigem - i && colunaDestino == colunaOrigem + i){
                    return true;
                } else if (tabuleiro[linhaOrigem - i][colunaOrigem + i] != ' '){
                    break;
                }
            }
            for(int i = 1; linhaOrigem + i < 8 && colunaOrigem - i >= 0; i++){//Para ver movimento para sudoeste
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem - i){
                    return true;
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem - i] != ' '){
                    break;
                }
            }
            for(int i = 1; linhaOrigem - i >= 0 && colunaOrigem - i >= 0; i++){//Para ver movimento para noroeste
                if(linhaDestino == linhaOrigem - i && colunaDestino == colunaOrigem - i){
                    return true;
                } else if (tabuleiro[linhaOrigem - i][colunaOrigem - i] != ' '){
                    break;
                }
            }
            return false; // Movimento inválido para o bispo
            

        case 'Q':
            /* Código para movimento da rainha */

            //Junção dos movimentos da torre e do bispo

            // Movimento da torre
            for(int i = 1; i + linhaOrigem < 8; i++){ //verifica se é moviemento para baixo
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem){
                    return true;
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem] != ' '){
                    break;
                }
            }
            for(int i = -1; i + linhaOrigem >= 0; i--){ //verifica se é movimento para cima
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem){
                    return true;
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem] != ' '){
                    break;
                }
            }
            for(int i = 1; i + colunaOrigem < 8; i++){ //verifica se é movimento para direita
                if(colunaDestino == colunaOrigem + i && linhaDestino == linhaOrigem){
                    return true;
                } else if (tabuleiro[linhaOrigem][colunaOrigem + i] != ' '){
                    break;
                }
            }
            for(int i = -1; i + colunaOrigem >= 0; i--){ //verifica se é movimento para esquerda
                if(colunaDestino == colunaOrigem + i && linhaDestino == linhaOrigem){
                    return true;
                } else if (tabuleiro[linhaOrigem][colunaOrigem + i] != ' '){
                    break;
                }
            }

            // Movimento do bispo
            for(int i = 1; linhaOrigem + i < 8 && colunaOrigem + i < 8; i++){//Para ver movimento para sudeste
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem + i){
                    return true;
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem + i] != ' '){
                    break;
                }
            }
            for(int i = 1; linhaOrigem - i >= 0 && colunaOrigem + i < 8; i++){//Para ver movimento para nordeste
                if(linhaDestino == linhaOrigem - i && colunaDestino == colunaOrigem + i){
                    return true;
                } else if (tabuleiro[linhaOrigem - i][colunaOrigem + i] != ' '){
                    break;
                }
            }
            for(int i = 1; linhaOrigem + i < 8 && colunaOrigem - i >= 0; i++){//Para ver movimento para sudoeste
                if(linhaDestino == linhaOrigem + i && colunaDestino == colunaOrigem - i){
                    return true;
                } else if (tabuleiro[linhaOrigem + i][colunaOrigem - i] != ' '){
                    break;
                }
            }
            for(int i = 1; linhaOrigem - i >= 0 && colunaOrigem - i >= 0; i++){//Para ver movimento para noroeste
                if(linhaDestino == linhaOrigem - i && colunaDestino == colunaOrigem - i){
                    return true;
                } else if (tabuleiro[linhaOrigem - i][colunaOrigem - i] != ' '){
                    break;
                }
            }

            return false; // Movimento inválido para a rainha

        case 'K':
            /* Código para movimento do rei */

            if((linhaDestino == linhaOrigem + 1 || linhaDestino == linhaOrigem - 1 || linhaDestino == linhaOrigem) &&
               (colunaDestino == colunaOrigem + 1 || colunaDestino == colunaOrigem - 1 || colunaDestino == colunaOrigem)) {
                return true; // Movimento válido para o rei (uma casa em qualquer direção)
            } else {
                return false; // Movimento inválido para o rei
            }
            break;

        default: //Se não for nenhuma peça válida
            return false;

        }
        
    }
    
    
    
}
