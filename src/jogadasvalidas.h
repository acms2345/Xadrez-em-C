#ifndef JOGADASVALIDAS_H
#define JOGADASVALIDAS_H
#include <stdbool.h>

const char* JogadaValida(char tabuleiro[8][8], int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int jogadorDaVez);

int iniciarJogo(int opcao);

#endif // JOGADASVALIDAS_H