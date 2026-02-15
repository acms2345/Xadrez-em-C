#ifndef JOGADASVALIDAS_H
#define JOGADASVALIDAS_H
#include <stdbool.h>

const char* JogadaValida(char tabuleiro[8][8], int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int jogadorDaVez);
bool XequeMate(char tabuleiro[8][8], int JogadorDaVez);

#endif // JOGADASVALIDAS_H