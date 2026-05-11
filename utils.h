#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <string.h>
int comparar_case_insensitive(const char *str1, const char *str2);
void trim(char *str);
const char* ObterSimboloPeca(char peca);
void limpezaBuffer();
#endif // UTILS_H