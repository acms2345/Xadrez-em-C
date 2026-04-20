#ifndef JOGADASVALIDAS_H
#define JOGADASVALIDAS_H
#include <stdbool.h>

const char* JogadaValida(char tabuleiro[8][8], int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int jogadorDaVez, int ultimoMovimentoOrigem[2], int ultimoMovimentoDestino[2]);
bool XequeMate(char tabuleiro[8][8], int JogadorDaVez, int ultimoMovimentoOrigem[2], int ultimoMovimentoDestino[2]);
bool Afogamento(char tabuleiro[8][8], int JogadorDaVez, int ultimoMovimentoOrigem[2], int ultimoMovimentoDestino[2]);

#endif // JOGADASVALIDAS_H