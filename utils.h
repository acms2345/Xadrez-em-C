#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <string.h>
int comparar_case_insensitive(const char *str1, const char *str2);
void trim(char *str);
const char* ObterSimboloPeca(char peca);
void limpezaBuffer();
void limparTela();
void pausa();
void printfBox(const char **linhas, int quantidadeLinhas);
void printfBoxFmt(int tamanhoMaximo, const char *fmt, ...);
#endif // UTILS_H