#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "cores.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <strings.h>
#endif

#include "utils.h"

int comparar_case_insensitive(const char *str1, const char *str2) {
    #ifdef _WIN32
        return _stricmp(str1, str2);
    #else    
    
    return strcasecmp(str1, str2);
    #endif
}
void trim(char *str){
    str[strcspn(str, "\n\r")] = '\0'; //Tira o newline

    int contagemInicio = 0;
    while(str[contagemInicio] == ' ' || str[contagemInicio] == '\t') contagemInicio++;
    /*O while acima conta onde realmente começa o texto da string.
    Por exemplo, na string " desistir", haverá uma contagem até onde realmente começa o texto
    (que é o caractere 'd').
    OBS: '\t' = caractere Tab.*/

    int contagemFinal = (int)strlen(str) - 1;
    while(contagemFinal >= contagemInicio && (str[contagemFinal] == ' ' || str[contagemFinal] == '\t')) contagemFinal--;

    if (contagemInicio <= contagemFinal){ //Ou seja, se houver algum texto (não-espaço) na string:
        memmove(str, &str[contagemInicio], contagemFinal - contagemInicio + 1);
        str[contagemFinal - contagemInicio + 1] = '\0';
    } else{
        str[0] = '\0'; //String vazia.
    }
}

//Esse é um sistema de conversão do formato de letras para os ícones do ANSI.
const char* ObterSimboloPeca(char peca) {
    static const char* simbolos[] = {
        ['P'] = "♙",
        ['T'] = "♖",
        ['C'] = "♘",
        ['B'] = "♗",
        ['Q'] = "♕",
        ['K'] = "♔",

        ['p'] = "♟",
        ['t'] = "♜",
        ['c'] = "♞",
        ['b'] = "♝",
        ['q'] = "♛",
        ['k'] = "♚",

        [' '] = " "
    };

    int ConversorIndice = (int)peca;
    if(ConversorIndice < sizeof(simbolos) / sizeof(simbolos[0]) && simbolos[ConversorIndice] != NULL){
        return simbolos[ConversorIndice];
    }
    return " "; // Caso de segurança
}

void limpezaBuffer(){
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}



void limparTela() {
    printf("%s", RESET); // Reseta as cores antes de limpar a tela
    fflush(stdout); // Garante que tudo seja impresso antes de limpar
    
    #ifdef _WIN32
        // Windows: usa API nativa
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hConsole != INVALID_HANDLE_VALUE) {
            COORD coord = {0, 0};
            DWORD written;
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            
            GetConsoleScreenBufferInfo(hConsole, &csbi);
            FillConsoleOutputCharacter(hConsole, ' ', 
                csbi.dwSize.X * csbi.dwSize.Y, coord, &written);
            SetConsoleCursorPosition(hConsole, coord);
        }
    #else
        // Linux/Mac: ANSI funciona normalmente
        printf("\033[2J\033[H");
        fflush(stdout);
    #endif
}

void pausa() {
    printf("\nPressione ENTER para continuar...");
    fflush(stdout);
    getchar();
}