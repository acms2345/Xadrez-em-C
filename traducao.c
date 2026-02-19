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
        "Escolha uma opcao: ",
        "Choose an option: "
    },
    {
        "Opcao invalida! Por favor, insira um numero entre 1 e 4: ",
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
        "Este e um jogo de xadrez para dois jogadores. Cada jogador controla um conjunto de pecas, uma em MAIUSCULAS e a outra em minusculas.\n",
        "This is a chess game for two players. Each player controls a set of pieces, one in UPPERCASE and the other in lowercase.\n"
    },
    {
        "O objetivo do jogo e capturar o rei do oponente. As pecas se movem de acordo com as regras tradicionais do xadrez.\n",
        "The objective of the game is to capture the opponent's king. The pieces move according to traditional chess rules.\n"
    },
    {
        "Para fazer uma jogada, voce precisara inserir as coordenadas de origem e destino no formato de notacao algebrica (ex: e2e4, e2-e4).\n",
        "To make a move, you will need to enter the source and destination coordinates in algebraic notation (e.g., e2e4, e2-e4).\n"
    },
    {
        "Voce tambem pode salvar o jogo a qualquer momento digitando 'salvar' quando solicitado a inserir uma jogada.\n",
        "You can also save the game at any time by typing 'save' when prompted to enter a move.\n"
    },
    {
        "Digite 'desistir' para abandonar o jogo atual e conceder a vitoria ao oponente.\n",
        "Type 'resign' to abandon the current game and concede victory to the opponent.\n"
    },
    {
        "Boa sorte e divirta-se!\n\n",
        "Good luck and have fun!\n\n"
    },


    //jogo.c
    {
        "\n%s, digite a jogada em notacao algebrica (ex: e2e4): ",
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
        "%s desistiu do jogo. %s e o vencedor!\n",
        "%s resigned from the game. %s is the winner!\n"
    },
    {
        "ERRO: Coluna origem invalida. Use letras de a-h.\n",
        "ERROR: Invalid source column. Use letters a-h.\n"
    },
    {
        "ERRO: Linha origem invalida. Use numeros de 1-8.\n",
        "ERROR: Invalid source row. Use numbers 1-8.\n"
    },
    {
        "ERRO: Coluna destino invalida. Use letras de a-h.\n",
        "ERROR: Invalid destination column. Use letters a-h.\n"
    },
    {
        "ERRO: Linha destino invalida. Use numeros de 1-8.\n",
        "ERROR: Invalid destination row. Use numbers 1-8.\n"
    },
    {
        "ERRO: Digito invalido. Para separar, use espaco ou hifen.\n",
        "ERROR: Invalid character. To separate, use space or hyphen.\n"
    },
    {
        "ERRO: Formato invalido. Use 4 caracteres (ex: e2e4) ou use 5 caracteres (ex: e2-e4)\n",
        "ERROR: Invalid format. Use 4 characters (e.g., e2e4) or use 5 characters (e.g., e2-e4)\n"
    },
    {
        "Seu peao chegou na ultima linha! Escolha a peca para promover (Q, C, B, T): ",
        "Your pawn has reached the last row! Choose the piece to promote to (Q, C, B, T): "
    },
    {
        "Escolha invalida. Por favor, escolha entre Q, C, B, T: ",
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
        "MAIUSCULAS",
        "UPPERCASE"
    },
    {
        "minusculas",
        "lowercase"
    },
    {
        "Jogada invalida! Nao ha peca na posicao de origem.\n",
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
        "\n=== EMPATE (REGRA DOS 50 MOVIMENTOS SEM CAPTURA OU PEAO) ===\n",
        "\n=== DRAW (50-MOVE RULE WITHOUT CAPTURE OR PAWN MOVE) ===\n"
    },
    {
        "\n=== XEQUE-MATE ===\n",
        "\n=== CHECKMATE ===\n"
    },

    {
        "Jogada invalida! %s.\n",
        "Invalid move! %s.\n"
    },


    //jogadasvalidas.c

    {
        "Movimento para a mesma posicao",
        "Move to the same position"
    },
    {
        "Tentativa de capturar propria peca",
        "Attempt to capture own piece"
    },
    {
        "Tentativa de mover peca do oponente",
        "Attempt to move opponent's piece"
    },
    {
        "Movimento deixaria rei em xeque",
        "Move would leave king in check"
    },
    {
        "Movimento invalido para o peao",
        "Invalid move for the pawn"
    },
    {
        "Movimento invalido para a torre",
        "Invalid move for the rook"
    },
    {
        "Movimento invalido para o cavalo",
        "Invalid move for the knight"
    },
    {
        "Movimento invalido para o bispo",
        "Invalid move for the bishop"
    },
    {
        "Movimento invalido para a rainha",
        "Invalid move for the queen"
    },
    {
        "Casa de destino em xeque",
        "Destination square is in check"
    },
    {
        "Movimento invalido para o rei",
        "Invalid move for the king"
    },
    {
        "Peça invalida",
        "Invalid piece"
    }
};

void definirIdioma(Lingua novoIdioma){
    linguaAtual = novoIdioma;
}

const char* Msg(Texto ID_Texto){
    return tabela_traducoes[ID_Texto][linguaAtual];
}