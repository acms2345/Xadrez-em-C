#include <stdio.h>
#include "traducao.h"

static Lingua linguaAtual = PORTUGUES;

static const char* tabela_traducoes [TOTAL_STRINGS][TOTAL_LINGUAS] = {
    //menu.c
    {
        "==============================================\n            XADREZ EM C\n==============================================",
        "==============================================\n            CHESS IN C\n=============================================="
    },
    {
        "\n1. Nova Partida\n",
        "\n1. New Game\n"
    },
    {
        "2. Carregar Partida Salva\n",
        "2. Load Saved Game\n"
    },
    {
        "3. Ajuda\n",
        "3. Help\n"
    },
    {
        "4. Sair\n\n",
        "4. Exit\n\n"
    },
    {
        "Escolha uma opção: ",
        "Choose an option: "
    },
    {
        "Opção inválida! Por favor, insira um número entre 1 e 4: ",
        "Invalid option! Please enter a number between 1 and 4: "
    },
    {
        "Fechando o programa...\n",
        "Closing the program...\n"
    },


    //menu.c - Ajuda
    {
        "\nAJUDA:\n",
        "\nHELP:\n"
    },
    {
        "Este é um jogo de xadrez para dois jogadores. Cada jogador controla um conjunto de pecas, uma em MAIÚSCULAS e a outra em minúsculas.\n",
        "This is a chess game for two players. Each player controls a set of pieces, one in UPPERCASE and the other in lowercase.\n"
    },
    {
        "O objetivo do jogo é capturar o rei do oponente. As peças se movem de acordo com as regras tradicionais do xadrez.\n",
        "The objective of the game is to capture the opponent's king. The pieces move according to traditional chess rules.\n"
    },
    {
        "Para fazer uma jogada, você precisará inserir as coordenadas de origem e destino no formato de notação algébrica (ex: e2e4, e2-e4).\n",
        "To make a move, you will need to enter the source and destination coordinates in algebraic notation (e.g., e2e4, e2-e4).\n"
    },
    {
        "Você também pode salvar o jogo a qualquer momento digitando 'salvar' quando solicitado a inserir uma jogada.\n",
        "You can also save the game at any time by typing 'save' when prompted to enter a move.\n"
    },
    {
        "Digite 'desistir' para abandonar o jogo atual e conceder a vitória ao oponente.\n",
        "Type 'resign' to abandon the current game and concede victory to the opponent.\n"
    },
    {
        "Boa sorte e divirta-se!\n\n",
        "Good luck and have fun!\n\n"
    },


    //jogo.c
    {
        "\n%s, digite a jogada em notação algébrica (ex: e2e4): ",
        "\n%s, enter your move in algebraic notation (e.g., e2e4): "
    },
    {
        "Jogo salvo com sucesso!\n",
        "Game saved successfully!\n"
    },
    {
        "Erro ao salvar o jogo.\n",
        "Error saving the game.\n"
    },
    {
        "%s desistiu do jogo. %s é o vencedor!\n",
        "%s resigned from the game. %s is the winner!\n"
    },
    {
        "ERRO: Coluna origem inválida. Use letras de a-h.\n",
        "ERROR: Invalid source column. Use letters a-h.\n"
    },
    {
        "ERRO: Linha origem inválida. Use números de 1-8.\n",
        "ERROR: Invalid source row. Use numbers 1-8.\n"
    },
    {
        "ERRO: Coluna destino inválida. Use letras de a-h.\n",
        "ERROR: Invalid destination column. Use letters a-h.\n"
    },
    {
        "ERRO: Linha destino inválida. Use números de 1-8.\n",
        "ERROR: Invalid destination row. Use numbers 1-8.\n"
    },
    {
        "ERRO: Dígito inválido. Para separar, use espaço ou hífen.\n",
        "ERROR: Invalid character. To separate, use space or hyphen.\n"
    },
    {
        "ERRO: Formato inválido. Use 4 caracteres (ex: e2e4) ou use 5 caracteres (ex: e2-e4)\n",
        "ERROR: Invalid format. Use 4 characters (e.g., e2e4) or use 5 characters (e.g., e2-e4)\n"
    },
    {
        "Seu peão chegou na última linha! Escolha a peça para promover (Q, C, B, T): ",
        "Your pawn has reached the last row! Choose the piece to promote to (Q, C, B, T): "
    },
    {
        "Escolha inválida. Por favor, escolha entre Q, C, B, T: ",
        "Invalid choice. Please choose between Q, C, B, T: "
    },

    {
        "Erro ao abrir o arquivo para salvar o jogo.\n",
        "Error opening file to save the game.\n"
    },
    {
        "Nenhum jogo salvo encontrado.\n",
        "No saved game found.\n"
    },

    {
        "Digite o nome do %d jogador: ",
        "Enter the name of player %d: "
    },
    {
        "E a vez de %s!\n (%s)",
        "It's %s's turn!\n (%s)"
    },
    {
        "MAIÚSCULAS",
        "UPPERCASE"
    },
    {
        "minúsculas",
        "lowercase"
    },
    {
        "Jogada inválida! Não há peça na posição de origem.\n",
        "Invalid move! There is no piece at the source position.\n"
    },

    {
        "\n=== XEQUE-MATE (REI CAPTURADO) ===\n",
        "\n=== CHECKMATE (KING CAPTURED) ===\n"
    },
    {
        "O jogador %s ganhou o jogo!\n",
        "Player %s wins the game!\n"
    },
    {
        "Placar: %s: %d pontos, %s: %d pontos\n",
        "Score: %s: %d points, %s: %d points\n"
    },
    {
        "Total de movimentos feitos: %d\n",
        "Total moves made: %d\n"
    },
    {
        "\n=== EMPATE (REGRA DOS 50 MOVIMENTOS SEM CAPTURA OU PEÃO) ===\n",
        "\n=== DRAW (50-MOVE RULE WITHOUT CAPTURE OR PAWN MOVE) ===\n"
    },
    {
        "\n=== XEQUE-MATE ===\n",
        "\n=== CHECKMATE ===\n"
    },

    {
        "=== AFOGAMENTO ===\n",
        "=== STALEMATE ===\n"
    },

    {
        "Houve um empate! Nenhum jogador tem movimentos válidos, mas o rei não está em xeque.\n",
        "It's a draw! Neither player has valid moves, but the king is not in check.\n"
    },

    {
        "Jogada inválida! %s.\n",
        "Invalid move! %s.\n"
    },


    //jogadasvalidas.c

    {
        "Movimento para a mesma posição",
        "Move to the same position"
    },
    {
        "Tentativa de capturar própria peça",
        "Attempt to capture own piece"
    },
    {
        "Tentativa de mover peça do oponente",
        "Attempt to move opponent's piece"
    },
    {
        "Movimento deixaria rei em xeque",
        "Move would leave king in check"
    },
    {
        "Movimento inválido para o peão",
        "Invalid move for the pawn"
    },
    {
        "Movimento inválido para a torre",
        "Invalid move for the rook"
    },
    {
        "Movimento inválido para o cavalo",
        "Invalid move for the knight"
    },
    {
        "Movimento inválido para o bispo",
        "Invalid move for the bishop"
    },
    {
        "Movimento inválido para a rainha",
        "Invalid move for the queen"
    },
    {
        "Casa de destino em xeque",
        "Destination square is in check"
    },
    {
        "Movimento inválido para o rei",
        "Invalid move for the king"
    },
    {
        "Peça inválida",
        "Invalid piece"
    }
};

void definirIdioma(Lingua novoIdioma){
    linguaAtual = novoIdioma;
}

const char* Msg(Texto ID_Texto){
    return tabela_traducoes[ID_Texto][linguaAtual];
}