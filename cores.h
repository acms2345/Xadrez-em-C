#ifndef CORES_H
#define CORES_H

#include <stdio.h>
#include <stdarg.h>

#define RESET  "\x1b[0m"

//Background (cores de fundo)
#define PRETO_BACKGROUND  "\x1b[40m"
#define BRANCO_BACKGROUND  "\x1b[47m"
#define AMARELO_BACKGROUND   "\x1b[43m"
#define AZUL_BACKGROUND       "\x1b[44m"
#define MAGENTA_BACKGROUND    "\x1b[45m"


//Foreground (cores para textos)
#define PRETO_FOREGROUND   "\x1b[30m"
#define BRANCO_FOREGROUND    "\x1b[37m"
#define VERDE_FOREGROUND  "\x1b[32m"
#define VERMELHO_FOREGROUND  "\x1b[31m"
#define MAGENTA_FOREGROUND "\x1b[35m"
#define AMARELO_FOREGROUND    "\x1b[33m"
#define AZUL_FOREGROUND      "\x1b[34m"
#define CIANO_FOREGROUND     "\x1b[36m"
#define BRANCO_CLARO_FOREGROUND  "\x1b[97m"
#define PRETO_CLARO_FOREGROUND   "\x1b[90m"

#define COR_PECAS "\x1b[33m" //Amarelo/Yellow
#define DESTAQUE "\x1b[46m" //Ciano/Cyan

// Estilos/Styles
#define NEGRITO       "\x1b[1m"
#define SUBLINHADO    "\x1b[4m"

/**
 * Imprime texto colorido (com cor de foreground)
 * Uso: printfColor(VERMELHO_FOREGROUND, "Erro: %d", codigo_erro);
 */
static inline void printfColor(const char *cor, const char *fmt, ...) {
    printf("%s", cor);
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("%s", RESET);
}

/**
 * Imprime texto colorido com estilo (estilo + cor + mensagem)
 * Uso: printfSColor(NEGRITO, VERDE_FOREGROUND, "Sucesso: %s", mensagem);
 */
static inline void printfSColor(const char *estilo, const char *cor, const char *fmt, ...) {
    printf("%s%s", estilo, cor);
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("%s", RESET);
}

#endif // CORES_H