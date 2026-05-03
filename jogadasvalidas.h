#ifndef JOGADASVALIDAS_H
#define JOGADASVALIDAS_H
#include <stdbool.h>

#define TAMANHO_TABULEIRO 8

const char* JogadaValida(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int jogadorDaVez, int ultimoMovimentoOrigem[2], int ultimoMovimentoDestino[2], bool reiSeMoveu[2], bool torreEsquerdaSeMoveu[2], bool torreDireitaSeMoveu[2]);
bool XequeMate(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int JogadorDaVez, int ultimoMovimentoOrigem[2], int ultimoMovimentoDestino[2], bool reiSeMoveu[2], bool torreEsquerdaSeMoveu[2], bool torreDireitaSeMoveu[2]);
bool Afogamento(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int JogadorDaVez, int ultimoMovimentoOrigem[2], int ultimoMovimentoDestino[2], bool reiSeMoveu[2], bool torreEsquerdaSeMoveu[2], bool torreDireitaSeMoveu[2]);
bool materialInsuficiente(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

// Funções para gerenciar verificação de repetição de posição

typedef struct {
    char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    bool reiMoveu[2];
    bool torreEsquerdaMoveu[2];
    bool torreDireitaMoveu[2];
    int jogadorDaVez;
} EstadoPosicao;

EstadoPosicao* ObterHistoricoPositoes(void);
int ObterCountHistoricoPositoes(void);
void DefinirCountHistoricoPositoes(int count);
void AdicionarPosicaoAoHistorico(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int jogadorDaVez, 
                                 bool reiMoveu[2], bool torreEsquerdaMoveu[2], 
                                 bool torreDireitaMoveu[2]);

int VerificarRepetidaoPosicao(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int jogadorDaVez, 
                              bool reiMoveu[2], bool torreEsquerdaMoveu[2], 
                              bool torreDireitaMoveu[2]);

void ReiniciarHistoricoPosicoes(void);

#endif // JOGADASVALIDAS_H