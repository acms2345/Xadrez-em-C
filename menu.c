#include <stdio.h>
#include "jogadasvalidas.h"

int main(){
    int opcao;
    
    printf("==============================================\n");
    printf("            XADREZ EM C\n");
    printf("==============================================\n\n");
    printf("1. Nova Partida\n");
    printf("2. Carregar Partida Salva\n");
    printf("3. Ajuda\n");
    printf("4. Sair\n\n");
    printf("Escolha uma opcao: ");

    while (0 != 1){
        scanf("%d", &opcao);

        if(opcao < 1 || opcao > 4){
            printf("Opcao invalida!\n");
        } else if(opcao == 4){
            printf("Fechando o programa...\n");
            return 0;
        } else if (opcao == 3)
        {
            printf("\nAJUDA:\n");
            printf("Este e um jogo de xadrez para dois jogadores. Cada jogador controla um conjunto de pecas, uma em MAIUSCULAS e a outra em minusculas.\n");
            printf("O objetivo do jogo e capturar o rei do oponente. As pecas se movem de acordo com as regras tradicionais do xadrez.\n");
            printf("Para fazer uma jogada, voce precisara inserir as coordenadas de origem e destino no formato de notacao algebrica (ex: e2e4).\n");
            printf("Voce tambem pode salvar o jogo a qualquer momento digitando 'salvar' quando solicitado a inserir uma jogada.\n");
            printf("Boa sorte e divirta-se!\n\n");
        } else{
            iniciarJogo(opcao);
        }
    }
}