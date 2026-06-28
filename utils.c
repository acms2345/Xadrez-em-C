#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "cores.h"
#include "traducao.h"

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
        // Linux/Mac
        printf("\033[2J\033[H");
        fflush(stdout);
    #endif
}

void pausa() {
    printf("\n%s...", Msg(MSG_PAUSA));
    fflush(stdout);
    getchar();
}


/*Essa função conta a quantidade de caracteres.
Ela faz uma adaptação quanto a caracteres com acento,
pois a=1byte enquanto á=2bytes.
A lógica usada para esses casos é a seguinte:
- Todo caractere inicia com binário diferente de 10;
- Quando inicia com 10, isso é uma indicação que se trata
    do 2º byte de um caractere especial.
- Assim, considerando que o & em C faz comparação bits por bits,
    é usado o sistema de máscara de bits:
    - (string & 0xC0)= por causa do 0XC0 (11000000), todos os bits
        exceto os 2 primeiros serão zerados.
    - (string & 0xC0) != 0x80 = por causa do 0X80 (10000000),
        será verificado se os dois primeiros dígitos são 10 ou não.*/
int contarTamanhoString(const char *string){
    int tamanhoString = 0;
    
    while (*string != '\0')
    {
        if((*string & 0xC0) != 0x80){
            continue;
        } else{
            tamanhoString++;
        }
    }

    return tamanhoString;
    
}

void repetirChar(char *ch, int quantidade){
    for(int i = 0; i < quantidade; i++) fputs(ch, stdout);
}

void printfBox(const char **linhas, int quantidadeLinhas){
    #define MARGEM 2

    int tamanhoLinhaMax = 0;

    for (size_t i = 0; i < quantidadeLinhas; i++)
    {
        int tamanho = contarTamanhoString(linhas[i]);

        if(tamanho > tamanhoLinhaMax) tamanhoLinhaMax = tamanho;

    }
    
    int tamanhoInterno = MARGEM * 2 + tamanhoLinhaMax;

    //Para a parte superior
    fputs("╔", stdout); repetirChar("═", tamanhoInterno); fputs("╗", stdout);
    fputs("\n", stdout);

    for (size_t i = 0; i < quantidadeLinhas; i++)
    {
        fputs("║", stdout);
        
        int tamanhoTexto = contarTamanhoString(linhas[i]);
        
        repetirChar(" ", MARGEM);

        fputs(linhas[i], stdout);

        int tamanhoResto = tamanhoInterno -(tamanhoTexto + (MARGEM*2));
        
        repetirChar(" ", tamanhoResto);

        repetirChar(" ", MARGEM);

        fputs("║", stdout);

        fputs("\n", stdout);
    }
    
    //Para a parte inferior
    fputs("╚", stdout); repetirChar("═", tamanhoInterno); fputs("╝", stdout);


}