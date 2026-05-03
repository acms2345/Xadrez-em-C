#ifndef JOGADASVALIDAS_H
#define JOGADASVALIDAS_H
#include <stdbool.h>

const char* JogadaValida(char tabuleiro[8][8], int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int jogadorDaVez, int ultimoMovimentoOrigem[2], int ultimoMovimentoDestino[2], bool reiSeMoveu[2], bool torreEsquerdaSeMoveu[2], bool torreDireitaSeMoveu[2]);
bool XequeMate(char tabuleiro[8][8], int JogadorDaVez, int ultimoMovimentoOrigem[2], int ultimoMovimentoDestino[2], bool reiSeMoveu[2], bool torreEsquerdaSeMoveu[2], bool torreDireitaSeMoveu[2]);
bool Afogamento(char tabuleiro[8][8], int JogadorDaVez, int ultimoMovimentoOrigem[2], int ultimoMovimentoDestino[2], bool reiSeMoveu[2], bool torreEsquerdaSeMoveu[2], bool torreDireitaSeMoveu[2]);
bool materialInsuficiente(char tabuleiro[8][8]);

// Funções para gerenciar verificação de repetição de posição

typedef struct {
    char tabuleiro[8][8];
    bool reiMoveu[2];
    bool torreEsquerdaMoveu[2];
    bool torreDireitaMoveu[2];
    int jogadorDaVez;
} EstadoPosicao;

EstadoPosicao* ObterHistoricoPositoes(void);
int ObterCountHistoricoPositoes(void);
void DefinirCountHistoricoPositoes(int count);
void AdicionarPosicaoAoHistorico(char tabuleiro[8][8], int jogadorDaVez, 
                                 bool reiMoveu[2], bool torreEsquerdaMoveu[2], 
                                 bool torreDireitaMoveu[2]);

int VerificarRepetidaoPosicao(char tabuleiro[8][8], int jogadorDaVez, 
                              bool reiMoveu[2], bool torreEsquerdaMoveu[2], 
                              bool torreDireitaMoveu[2]);

void ReiniciarHistoricoPosicoes(void);

#endif // JOGADASVALIDAS_H