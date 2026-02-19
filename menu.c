#include <stdio.h>
#include "jogo.h"
#include "traducao.h"

/*Note: The source code is entirely written in Portuguese now.*/

// ✅ Ativa UTF-8 automaticamente no Windows
#ifdef _WIN32
    #include <windows.h>
#endif

int main(){
    #ifdef _WIN32
        SetConsoleCP(65001);
        SetConsoleOutputCP(65001);
    #endif
    
    int opcao;
    Lingua opcao_lingua;
    while(1){
        printf("Escolha a língua/Choose the language (0 = Português, 1 = English): ");
        if(scanf("%d", &opcao_lingua) != 1){
            printf("Opcao inválida!/Invalid option!\n");

            int c;
            while((c = getchar()) != '\n' && c != EOF); // Limpa o buffer de entrada
            
            continue;
        }

        definirIdioma(opcao_lingua);
        break;
    }
    printf(Msg(MSG_MENU_TITULO));

    while (1){
        printf(Msg(MSG_MENU_OPCAO_NOVA_PARTIDA));
        printf(Msg(MSG_MENU_OPCAO_CARREGAR_PARTIDA));
        printf(Msg(MSG_MENU_OPCAO_AJUDA));
        printf(Msg(MSG_MENU_OPCAO_SAIR));
        printf(Msg(MSG_MENU_OPCAO_ESCOLHA_OPCAO));

        if(scanf("%d", &opcao) != 1){
            printf(Msg(MSG_MENU_OPCAO_INVALIDA));
            
            int c;
            while((c = getchar()) != '\n' && c != EOF); // Limpa o buffer de entrada
            
            continue;
        }

        if(opcao < 1 || opcao > 4){
            printf(Msg(MSG_MENU_OPCAO_INVALIDA));
        } else if(opcao == 4){
            printf(Msg(MSG_MENU_FECHANDO_PROGRAMA));
            return 0;
        } else if (opcao == 3)
        {
            printf(Msg(MSG_MENU_AJUDA_TITULO));
            printf(Msg(MSG_MENU_AJUDA_LINHA1));
            printf(Msg(MSG_MENU_AJUDA_LINHA2));
            printf(Msg(MSG_MENU_AJUDA_LINHA3));
            printf(Msg(MSG_MENU_AJUDA_LINHA4));
            printf(Msg(MSG_MENU_AJUDA_LINHA5));
            printf(Msg(MSG_MENU_AJUDA_LINHA6));
        } else{
            iniciarJogo(opcao);
        }
    }

    return 0;
}