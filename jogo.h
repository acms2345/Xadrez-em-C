#ifndef JOGO_H
#define JOGO_H

#define MAX_HISTORICO 500

int iniciarJogo(int opcao);

typedef struct
{
    int linhaOrigem, colunaOrigem;
    int linhaDestino, colunaDestino;
} Movimento;

void obterHistoricoMovimentos(Movimento* historico, int* count);

#endif // JOGO_H