#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <string.h>

/*Esse código é colocado para resolver
o problema de trechos em que 0 e 1 correspondem
a brancas e pretas, como JogadorDaVez em jogo.c e vários outros.*/
#define PECAS_BRANCAS 0
#define PECAS_PRETAS 1

int comparar_case_insensitive(const char *str1, const char *str2);
void trim(char *str);
const char* ObterSimboloPeca(char peca);
void limpezaBuffer();
void limparTela();
void pausa();
void printfBox(const char **linhas, int quantidadeLinhas);
void printfBoxFmt(int tamanhoMaximo, const char *fmt, ...);
#endif // UTILS_H