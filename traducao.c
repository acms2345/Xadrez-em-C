#include <stdio.h>
#include "traducao.h"

static Lingua linguaAtual = PORTUGUES;

static const char* tabela_traducoes [TOTAL_STRINGS][TOTAL_LINGUAS] = {
    [STR_SEPARACAO] = {
        "-----------------------------------------------\n\n",
        "-----------------------------------------------\n\n"
    },
    [MSG_PAUSA] = {
        "Pressione ENTER para continuar",
        "Press ENTER to continue"
    },
    
    //menu.c
    [MSG_MENU_TITULO] = {
        "XADREZ EM C",
        "CHESS IN C"
    },
    [MSG_MENU_OPCAO_NOVA_PARTIDA] = {
        "\n1. Nova Partida\n",
        "\n1. New Game\n"
    },
    [MSG_MENU_OPCAO_CARREGAR_PARTIDA] = {
        "2. Carregar Partida Salva\n",
        "2. Load Saved Game\n"
    },
    [MSG_MENU_OPCAO_AJUDA] = {
        "3. Ajuda\n",
        "3. Help\n"
    },
    [MSG_MENU_OPCAO_REPLAY] = {
        "4. Replay\n",
        "4. Replay\n"
    },
    [MSG_MENU_OPCAO_SAIR] = {
        "5. Sair\n\n",
        "5. Exit\n\n"
    },
    [MSG_MENU_OPCAO_ESCOLHA_OPCAO] = {
        "Escolha uma opção: ",
        "Choose an option: "
    },
    [MSG_MENU_OPCAO_INVALIDA] = {
        "Opção inválida! Por favor, insira um número entre 1 e 5: ",
        "Invalid option! Please enter a number between 1 and 5: "
    },
    [MSG_MENU_FECHANDO_PROGRAMA] = {
        "Fechando o programa...\n",
        "Closing the program...\n"
    },
    
    [MSG_MENU_AJUDA_TITULO] = {
        "AJUDA:",
        "HELP:"
    },
    [MSG_MENU_AJUDA_LINHA1] = {
        "Este é um jogo de xadrez para dois jogadores. Cada um controla um conjunto de peças: um em brancas (MAIÚSCULAS) e outro em pretas (minúsculas).",
        "This is a chess game for two players. Each controls a set of pieces: one with white (UPPERCASE) and the other with black (lowercase)."
    },
    [MSG_MENU_AJUDA_LINHA2] = {
        "O objetivo: dar xeque-mate ao rei do oponente. As peças se movem de acordo com as regras tradicionais do xadrez.",
        "The goal: to checkmate the opponent's king. The pieces move according to traditional chess rules."
    },
    [MSG_MENU_AJUDA_LINHA3] = {
        "Para fazer uma jogada, você precisará inserir as coordenadas de origem e destino no formato de notação algébrica (ex: e2e4, e2-e4).",
        "To make a move, you will need to enter the source and destination coordinates in algebraic notation (e.g., e2e4, e2-e4)."
    },
    [MSG_MENU_AJUDA_LINHA4] = {
        "Você também pode salvar o jogo a qualquer momento digitando 'salvar' quando solicitado a inserir uma jogada.",
        "You can also save the game at any time by typing 'save' when prompted to enter a move."
    },
    [MSG_MENU_AJUDA_LINHA5] = {
        "Digite 'desistir' para abandonar o jogo atual e conceder a vitória ao oponente.",
        "Type 'resign' to abandon the current game and concede victory to the opponent."
    },
    [MSG_MENU_AJUDA_LINHA6] = {
        "Digite 'empatar' para sugerir um empate ao seu oponente. Ele responderá sim (S) ou não (N).",
        "Type 'draw' to sugest a draw to your oponent. He will answer yes (Y) or no (N)."
    },
    [MSG_MENU_AJUDA_LINHA7] = {
        "Ao ocorrer uma promoção de peão, será solicitada a letra correspondente à peça de troca (Q, C, B, ou T)",
        "When a pawn promotion occurs, the letter corresponding to the replacement piece (Q, C, B, or T) will be requested"
    },
    [MSG_MENU_AJUDA_LINHA8] = {
        "Boa sorte e divirta-se! :)",
        "Good luck and have fun! :)"
    },


    //jogo.c
    [MSG_JOGO_RAINHA] = {
        "Rainha",
        "Queen"
    },
    [MSG_JOGO_CAVALO] = {
        "Cavalo",
        "Horse"
    },
    [MSG_JOGO_BISPO] = {
        "Bispo",
        "Bishop"
    },
    [MSG_JOGO_TORRE] = {
        "Torre",
        "Rook"
    },

    [MSG_JOGO_DIGITE_JOGADA] = {
        "\n%s, digite a jogada em notação algébrica (ex: e2e4): ",
        "\n%s, enter your move in algebraic notation (e.g., e2e4): "
    },
    [MSG_JOGO_ENCERRAMENTO_EOF] = {
        "Fim do arquivo (EOF) detectado. Encerrando a partida...\n",
        "End of file (EOF) detected. Ending the game...\n"
    },
    [MSG_JOGO_SALVAR_SUCESSO] = {
        "Jogo salvo com sucesso!\n",
        "Game saved successfully!\n"
    },
    [MSG_JOGO_SALVAR_ERRO] = {
        "Erro ao salvar o jogo.\n",
        "Error saving the game.\n"
    },
    [MSG_JOGO_DESISTENCIA] = {
        "%s desistiu do jogo. %s é o vencedor!",
        "%s resigned from the game. %s is the winner!"
    },
    [MSG_JOGO_EMPATE_SUGESTAO] = {
       "%s deseja um empate. %s aceita? (s/n): ",
        "%s offers a draw. Does %s accept? (y/n): "
    },
    [MSG_JOGO_EMPATE_ACEITO] = {
        "%s aceitou o empate. O jogo termina empatado!",
        "%s accepted the draw. The game ends in a draw!"
    }, 
    [MSG_JOGO_COLUNA_ORIGEM_INVALIDA] = {
        "ERRO: Coluna origem inválida. Use letras de a-h.\n",
        "ERROR: Invalid source column. Use letters a-h.\n"
    },
    [MSG_JOGO_LINHA_ORIGEM_INVALIDA] = {
        "ERRO: Linha origem inválida. Use números de 1-8.\n",
        "ERROR: Invalid source row. Use numbers 1-8.\n"
    },
    [MSG_JOGO_COLUNA_DESTINO_INVALIDA] = {
        "ERRO: Coluna destino inválida. Use letras de a-h.\n",
        "ERROR: Invalid destination column. Use letters a-h.\n"
    },
    [MSG_JOGO_LINHA_DESTINO_INVALIDA] = {
        "ERRO: Linha destino inválida. Use números de 1-8.\n",
        "ERROR: Invalid destination row. Use numbers 1-8.\n"
    },
    [MSG_JOGO_SEPARADOR_COORDENADAS_INVALIDO] = {
        "ERRO: Dígito inválido. Para separar, use espaço ou hífen.\n",
        "ERROR: Invalid character. To separate, use space or hyphen.\n"
    },
    [MSG_JOGO_FORMATO_COORDENADAS_INVALIDO] = {
        "ERRO: Formato inválido. Use 4 caracteres (ex: e2e4) ou use 5 caracteres (ex: e2-e4)\n",
        "ERROR: Invalid format. Use 4 characters (e.g., e2e4) or use 5 characters (e.g., e2-e4)\n"
    },

    [MSG_JOGO_PROMOCAO_PEAO_ESCOLHA_PECA] = {
        "Escolha a peça para promover seu peão (Q=Rainha, C=Cavalo, B=Bispo, T=Torre): ",
        "Choose the piece to promote your pawn (Q=Queen, C=Horse, B=Bishop, T=Tower): "
    },
    [MSG_JOGO_PROMOCAO_PEAO_PECA_INVALIDA] = {
        "Escolha inválida. Por favor, escolha entre Q, C, B, T: ",
        "Invalid choice. Please choose between Q, C, B, T: "
    },

    [MSG_JOGO_SALVAR_ERRO_ABERTURA_ARQUIVO] = {
        "Erro ao abrir o arquivo para salvar o jogo.\n",
        "Error opening file to save the game.\n"
    },
    [MSG_JOGO_CARREGAR_ERRO] = {
        "ERRO: Nenhum jogo salvo encontrado.\n",
        "ERROR: No saved game found.\n"
    },
    [MSG_JOGO_VERSAO_INCOMPATIVEL] = {
        "ERRO: Versão do salvamento incompatível com a do jogo.\n",
        "ERROR: Save version incompatible with the game version.\n"
    },

    [MSG_JOGO_DIGITE_JOGADOR] = {
        "Digite o nome do %d jogador (máximo de 20 caracteres): ",
        "Enter the name of player %d (maximum 20 characters): "
    },
    [MSG_JOGO_VEZ_JOGADOR] = {
        "E a vez de %s!\n (%s)",
        "It's %s's turn!\n (%s)"
    },
    [MSG_JOGO_MAIUSCULAS] = {
        "MAIÚSCULAS - Brancas ♙",
        "UPPERCASE - Whites ♙"
    },
    [MSG_JOGO_MINUSCULAS] = {
        "minúsculas - Pretas ♟",
        "lowercase - Blacks ♟"
    },
    [MSG_JOGO_POSICAO_ORIGEM_VAZIA] = {
        "Jogada inválida! Não há peça na posição de origem.\n",
        "Invalid move! There is no piece at the source position.\n"
    },

    [MSG_JOGO_PROMOCAO_TITULO] = {
        "PROMOÇÃO DE PEÃO",
        "PAWN PROMOTION"
    },

    [MSG_JOGO_REIEMXEQUE] = {
        "\nAtenção: seu rei está em xeque!",
        "\nAttention: your king os on check!"
    },

    [MSG_JOGO_XEQUEMATE_REI_CAPTURADO_TITULO] = {
        "\n=== XEQUE-MATE (REI CAPTURADO) ===\n",
        "\n=== CHECKMATE (KING CAPTURED) ===\n"
    },
    [MSG_JOGO_XEQUEMATE_VENCEDOR] = {
        "O jogador %s ganhou o jogo!\n",
        "Player %s wins the game!\n"
    },
    [MSG_JOGO_XEQUEMATE_PLACAR] = {
        "Placar: %s: %d pontos, %s: %d pontos\n",
        "Score: %s: %d points, %s: %d points\n"
    },
    [MSG_JOGO_XEQUEMATE_TOTAL_MOVIMENTOS] = {
        "Total de movimentos feitos: %d\n",
        "Total moves made: %d\n"
    },
    [MSG_JOGO_EMPATE_50MOVIMENTOS_TITULO] = {
        "\n=== EMPATE (REGRA DOS 50 MOVIMENTOS SEM CAPTURA OU PEÃO) ===\n",
        "\n=== DRAW (50-MOVE RULE WITHOUT CAPTURE OR PAWN MOVE) ===\n"
    },
    [MSG_JOGO_XEQUEMATE_TITULO] = {
        "\n=== XEQUE-MATE ===\n",
        "\n=== CHECKMATE ===\n"
    },
    [MSG_JOGO_AFOGAMENTO_TITULO] = {
        "=== AFOGAMENTO ===\n",
        "=== STALEMATE ===\n"
    },
    [MSG_JOGO_EMPATE_TEXTO_AFOGAMENTO] = {
        "Houve um empate! Nenhum jogador tem movimentos válidos, mas o rei não está em xeque.",
        "It's a draw! Neither player has valid moves, but the king is not in check."
    },
    [MSG_JOGO_EMPATE_TEXTO_50MOVIMENTOS] = {
        "Houve um empate! Não houve movimento de peão ou captura de peças por 50 lances.",
        "It's a draw! There was not pawn moves or piece captures for 50 moves."
    },
    [MSG_JOGO_EMPATE_TEXTO_MATERIALINSUFICIENTE] = {
        "Houve um empate! Não há material suficiente para fazer xeque-mate.",
        "It's a draw! There is not enough material to deliver checkmate"
    },
    [MSG_JOGO_EMPATE_TEXTO_MOVIMENTOSREPETIDOS] = {
        "Houve um empate! O mesmo movimento foi repetido três vezes.",
        "It's a draw! The same move was repeated three times."
    },
    [MSG_JOGO_REPETICAO_TITULO] = {
        "\n=== EMPATE POR REPETIÇÃO DE POSIÇÃO ===\n",
        "\n=== DRAW BY POSITION REPETITION ===\n"
    },
    [MSG_JOGO_MATERIAL_INSUFICIENTE_TITULO] = {
        "\n=== EMPATE POR MATERIAL INSUFICIENTE ===\n",
        "\n=== DRAW BY INSUFFICIENT MATERIAL ===\n"
    },

    [MSG_JOGO_JOGADA_INVALIDA] = {
        "Jogada inválida! %s.\n",
        "Invalid move! %s.\n"
    },


    //jogadasvalidas.c
    [MSG_JOGADA_VALIDA] = {
        "Movimento válido.",
        "Valid move."
    },
    [MSG_JOGADA_VALIDA_EN_PASSANT] = {
        "Movimento válido (en passant).",
        "Valid move (en passant)."
    },
    [MSG_JOGADA_VALIDA_ROQUE] = {
        "Movimento válido (roque).",
        "Valid move (castling)."
    },
    [MSG_JOGADAS_MOVIMENTO_MESMA_POSICAO] = {
        "Movimento para a mesma posição",
        "Move to the same position"
    },
    [MSG_JOGADAS_PECA_MESMO_JOGADOR] = {
        "Tentativa de capturar própria peça",
        "Attempt to capture own piece"
    },
    [MSG_JOGADAS_MOVER_PECA_OPONENTE] = {
        "Tentativa de mover peça do oponente",
        "Attempt to move opponent's piece"
    },
    [MSG_JOGADAS_DEIXA_REI_XEQUE] = {
        "Movimento deixaria rei em xeque",
        "Move would leave king in check"
    },
    [MSG_JOGADAS_MOVIMENTO_INVALIDO_PEAO] = {
        "Movimento inválido para o peão",
        "Invalid move for the pawn"
    },
    [MSG_JOGADAS_MOVIMENTO_INVALIDO_TORRE] = {
        "Movimento inválido para a torre",
        "Invalid move for the rook"
    },
    [MSG_JOGADAS_MOVIMENTO_INVALIDO_CAVALO] = {
        "Movimento inválido para o cavalo",
        "Invalid move for the knight"
    },
    [MSG_JOGADAS_MOVIMENTO_INVALIDO_BISPO] = {
        "Movimento inválido para o bispo",
        "Invalid move for the bishop"
    },
    [MSG_JOGADAS_MOVIMENTO_INVALIDO_RAINHA] = {
        "Movimento inválido para a rainha",
        "Invalid move for the queen"
    },
    [MSG_JOGADAS_CASA_DESTINO_XEQUE] = {
        "Casa de destino em xeque",
        "Destination square is in check"
    },
    [MSG_JOGADAS_MOVIMENTO_INVALIDO_REI] = {
        "Movimento inválido para o rei",
        "Invalid move for the king"
    },
    [MSG_JOGADAS_PECA_INVALIDA] = {
        "Peça inválida",
        "Invalid piece"
    },

    
    //replay.c

    [MSG_REPLAY_SEM_HISTORICO] = {
        "Nenhum histórico de movimentos encontrado para replay.",
        "No move history found for replay."
    },
    [MSG_REPLAY_MOVIMENTO_NUM] = {
        "Movimento %d: ",
        "%d move:"
    },
    [MSG_REPLAY_POSICAO_INICIAL] = {
        "Posição Inicial\n\n",
        "Initial position\n\n"
    },
    [MSG_REPLAY_OPCOES] = {
        "  [P] Anterior   [N] Próximo   [I] Ir para   [S] Sair\n",
        "  [P] Previous   [N] Next   [I] Go to   [S] Leave\n"
    }
    
};

void definirIdioma(Lingua novoIdioma){
    linguaAtual = novoIdioma;
}

const char* Msg(Texto ID_Texto){
    return tabela_traducoes[ID_Texto][linguaAtual];
}