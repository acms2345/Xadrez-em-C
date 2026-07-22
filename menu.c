#include <stdio.h>
#include "jogo.h"
#include "replay.h"
#include "traducao.h"
#include "cores.h"
#include "utils.h"

/*Note: The source code is entirely written in Portuguese now.*/

// Ativa UTF-8 no Windows
#ifdef _WIN32
    #include <windows.h>
#endif

int main(){
    #ifdef _WIN32
        SetConsoleCP(65001);
        SetConsoleOutputCP(65001);
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut != INVALID_HANDLE_VALUE) {
            DWORD dwMode = 0;
            if (GetConsoleMode(hOut, &dwMode)) {
                dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                SetConsoleMode(hOut, dwMode);
            }
        }
    #endif
    
    int opcao;
    int opcao_lingua;
    while(1){
        printf("Escolha a língua/Choose the language (0 = Português, 1 = English): ");

        fflush(stdout);

        if(scanf("%d", &opcao_lingua) != 1 || opcao_lingua >= TOTAL_LINGUAS || opcao_lingua < 0){
            printf("Opcao inválida!/Invalid option!\n");

            int c;
            while((c = getchar()) != '\n' && c != EOF); // Limpa o buffer de entrada
            
            continue;
        }

        definirIdioma(opcao_lingua);
        break;
    }

    printf("%s%s", NEGRITO, AMARELO_FOREGROUND);
    printfBox((const char *[]){Msg(MSG_MENU_TITULO)}, 1);

    while (1){
        printf(Msg(MSG_MENU_OPCAO_NOVA_PARTIDA));
        printf(Msg(MSG_MENU_OPCAO_CARREGAR_PARTIDA));
        printf(Msg(MSG_MENU_OPCAO_AJUDA));
        printf(Msg(MSG_MENU_OPCAO_REPLAY));
        printf(Msg(MSG_MENU_OPCAO_SAIR));
        printf(Msg(MSG_MENU_OPCAO_ESCOLHA_OPCAO));

        fflush(stdout);

        if(scanf("%d", &opcao) != 1){
            printf(Msg(MSG_MENU_OPCAO_INVALIDA));
            
            int c;
            while((c = getchar()) != '\n' && c != EOF); // Limpa o buffer de entrada
            
            continue;
        }

        if(opcao < 1 || opcao > 5){
            printf(Msg(MSG_MENU_OPCAO_INVALIDA));
        } else if(opcao == 5){
            printf(Msg(MSG_MENU_FECHANDO_PROGRAMA));
            return 0;
        } else if (opcao == 3)
        {
            limparTela();
            printfBox((const char *[]){Msg(MSG_MENU_AJUDA_TITULO), 
                " ",
                Msg(MSG_MENU_AJUDA_LINHA1), 
                Msg(MSG_MENU_AJUDA_LINHA2),
                Msg(MSG_MENU_AJUDA_LINHA3),
                Msg(MSG_MENU_AJUDA_LINHA4),
                Msg(MSG_MENU_AJUDA_LINHA5),
                Msg(MSG_MENU_AJUDA_LINHA6),
                Msg(MSG_MENU_AJUDA_LINHA7)}, 9);
            pausa();
            limparTela();
        } else if (opcao == 4)
        {
            ExibirReplay();
        }
        else{
            iniciarJogo(opcao);
        }
    }

    return 0;
}