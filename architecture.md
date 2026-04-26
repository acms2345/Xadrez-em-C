# Project Architecture/Arquitetura do Projeto

# English version

## Main Functions

#### In `jogo.c`:
-   `iniciarJogo(int opcao)`: Initializes a new game or loads a saved one based on the option.
-   `ExibirTabuleiro()`: Prints the current state of the board with Unicode chess piece symbols.
-   `SalvarJogo()`: Saves the complete game state to a binary file named `salvamento.dat`.
-   `CarregarJogo()`: Loads the game state from `salvamento.dat`.
-   `obterCoordenada()`: Reads and validates algebraic notation input (supports `e2e4` or `e2-e4` format).
    - Handles special commands: `"salvar"`/`"save"` (save game), `"desistir"`/`"resign"` (resign), `"empatar"`/`"draw"` (propose draw)
-   `PromocaoPeao()`: Prompts player to choose a piece for pawn promotion (Q, C, B, T).
-   `atualizarPontuacao()`: Updates player score when a piece is captured.
-   **Helper functions**:
    - `limpezaBuffer()`: Clears input buffer to prevent issues with multiple inputs.
    - `trim()`: Removes leading/trailing whitespace and newline characters.

#### In `jogadasvalidas.c`:
-   `JogadaValida()`: Main validation function that checks all move rules and returns error messages if invalid.
-   `CasaAtacada()`: Checks if a given square is under attack by opponent pieces (used for king safety validation).
    - Validates attacks from: pawns, knights, bishops, rooks, queens, and kings.
-   `movimentoDeixaReiemXeque()`: Simulates a move and checks if it would leave the player's king in check (prevents illegal moves).
-   `movimentoDeixaReiemXequeEnPassant()`: Almost similar to the above function, but specifically for en passant captures.
-   `ReiEmXeque()`: Checks if the current player's king is in check.
-   `XequeMate()`: Detects checkmate (king in check with no legal moves).
-   `Afogamento()`: Detects stalemate (no legal moves but king not in check).
- `Roque()`: Validates castling moves based on piece movement history and current board state.


#### Save File Structure

The save file stores a binary `Salvamento` struct containing:
- `tabuleiro[8][8]`: The current board state
- `jogadorDaVez`: Which player's turn it is (0 or 1)
- `movimentosFeitos`: Total moves made
- `movimentosSemCapturaouPiao`: Move counter for the 50-move rule
- `jogadores[2]`: Player names and scores

## 🔧 Technical Architecture

### System Features

#### 1. **Internationalization (i18n) System**
The game supports two languages: Portuguese and English. The translation system is implemented in `traducao.c`:
- `definirIdioma()`: Sets the active language
- `Msg()`: Retrieves translated message strings
- All UI messages are centralized in a translation table for easy maintenance

#### 2. **Terminal Color System**
The `cores.h` header provides ANSI color codes for:
- Background colors: Black, white, blue, magenta
- Foreground colors: Black, white, green, red, yellow
- Text styles: Bold, underlined
- Macros for easy colored output: `printfColor()`, `printfSColor()`

#### 3. **Move Validation Engine**
The move validation follows this logic:
1. Check if source square has a piece
2. Check if piece belongs to the current player
3. Validate the specific movement rules for the piece type
4. Simulate the move and verify the king isn't left in check
5. Return error message if invalid, or confirm if valid

#### 4. **Game State Detection**
The game automatically detects:
- **Check**: King is under attack but has legal moves
- **Checkmate**: King is under attack with no legal moves (game ends)
- **Stalemate**: No legal moves and king is not under attack (draw)
- **50-Move Rule**: No captures or pawn moves for 100 half-moves (draw)

### Data Structures

**Player struct:**
```c
typedef struct {
    char nome[20];
    int pontos;
} Jogador;
```

**Save file struct:**
```c
struct Salvamento
{
    float versao; //For future compatibility checks
    char tabuleiro[8][8];
    int jogadorDaVez;
    int movimentosFeitos;
    int movimentosSemCapturaouPiao;
    int ultimoMovimentoOrigem[2];
    int ultimoMovimentoDestino[2];
    Jogador jogadores[2];
    // Castling flags
    bool reiMoveu[2]; 
    bool torreEsquerdaMoveu[2]; //left = column a
    bool torreDireitaMoveu[2];

    Movimento historico[MAX_HISTORICO];
    int countHistorico;
};
```

**Move History struct:**
```c
typedef struct {
    int origem[2];      // [row, col]
    int destino[2];     // [row, col]
    EstadoRoque estadoRoque;  // Castling state after move
} Movimento;
```


#Versão em português

### Principais funções

#### Em `jogo.c`:
- `iniciarJogo(int opcao)`: Inicia um novo jogo ou carrega um salvo baseado na opção.
- `ExibirTabuleiro()`: Imprime o estado atual do tabuleiro com símbolos Unicode.
- `SalvarJogo()`: Salva as informações completas da partida em arquivo binário `salvamento.dat`.
- `CarregarJogo()`: Carrega as informações salvas de `salvamento.dat`.
- `obterCoordenada()`: Lê e valida entrada de notação algébrica (aceita `e2e4` ou `e2-e4`).
  - Trata comandos especiais: `"salvar"`/`"save"` (salvar jogo), `"desistir"`/`"resign"` (desistir), `"empatar"`/`"draw"` (propor empate)
- `PromocaoPeao()`: Permite escolher peça na promoção de peão (Q, C, B, T).
- `atualizarPontuacao()`: Verifica se houve captura e atualiza a pontuação do jogador.
- **Funções auxiliares**:
  - `limpezaBuffer()`: Limpa o buffer de entrada para evitar problemas com múltiplas entradas.
  - `trim()`: Remove espaços em branco iniciais/finais e quebras de linha.

#### Em `jogadasvalidas.c`:
- `JogadaValida()`: Função principal de validação que verifica todas as regras de movimento.
- `CasaAtacada()`: Verifica se uma casa está sob ataque de peças do oponente.
  - Valida ataques de: peões, cavalos, bispos, torres, rainhas e reis.
- `movimentoDeixaReiemXeque()`: Simula um movimento e verifica se o rei ficaria em xeque.
- `movimentoDeixaReiemXequeEnPassant()`: Similar à função acima, mas especificamente para capturas en passant.
- `ReiEmXeque()`: Verifica se o rei do jogador atual está em xeque.
- `XequeMate()`: Detecta xeque-mate (rei em xeque sem movimentos legais).
- `Afogamento()`: Detecta afogamento (nenhum movimento legal mas rei não em xeque).
- `Roque()`: Valida movimentos de roque com base no histórico de movimentos das peças e estado atual do tabuleiro.

#### Estrutura do arquivo de salvamento

O arquivo de salvamento armazena uma estrutura `Salvamento` contendo:
- `tabuleiro[8][8]`: O estado atual do tabuleiro
- `jogadorDaVez`: De quem é a vez (0 ou 1)
- `movimentosFeitos`: Total de movimentos realizados
- `movimentosSemCapturaouPiao`: Contador de movimentos para a regra dos 50 lances
- `jogadores[2]`: Nomes e pontuação dos jogadores

## 🔧 Arquitetura Técnica

### Funcionalidades do Sistema

#### 1. **Sistema de Internacionalização (i18n)**
O jogo suporta dois idiomas: Português e English. O sistema de tradução é implementado em `traducao.c`:
- `definirIdioma()`: Define o idioma ativo
- `Msg()`: Recupera strings de mensagens traduzidas
- Todas as mensagens da interface estão centralizadas em uma tabela de tradução para fácil manutenção

#### 2. **Sistema de Cores de Terminal**
O header `cores.h` fornece códigos de cor ANSI para:
- Cores de fundo: Preto, branco, azul, magenta
- Cores de texto: Preto, branco, verde, vermelho, amarelo
- Estilos de texto: Negrito, sublinhado
- Macros para saída colorida facilitada: `printfColor()`, `printfSColor()`

#### 3. **Motor de Validação de Movimentos**
A validação de movimento segue esta lógica:
1. Verifica se há uma peça na casa de origem
2. Verifica se a peça pertence ao jogador atual
3. Valida as regras de movimento específicas do tipo de peça
4. Simula o movimento e verifica se o rei não ficaria em xeque
5. Retorna mensagem de erro se inválido, ou confirma se válido

#### 4. **Detecção de Estados do Jogo**
O jogo detecta automaticamente:
- **Xeque**: Rei está sob ataque mas tem movimentos legais
- **Xeque-mate**: Rei está sob ataque sem movimentos legais (jogo termina)
- **Afogamento**: Nenhum movimento legal e rei não está sob ataque (empate)
- **Regra dos 50 lances**: Nenhuma captura ou movimento de peão por 100 meias-jogadas (empate)

### Estruturas de Dados

**Estrutura do Jogador:**
```c
typedef struct {
    char nome[20];
    int pontos;
} Jogador;
```

**Estrutura do arquivo de salvamento:**
```c
struct Salvamento
{
    float versao; //Para controle de versão do salvamento, caso haja mudanças futuras na estrutura
    char tabuleiro[8][8];
    int jogadorDaVez;
    int movimentosFeitos;
    int movimentosSemCapturaouPiao;
    int ultimoMovimentoOrigem[2];
    int ultimoMovimentoDestino[2];
    Jogador jogadores[2];
    //Informações de roque
    bool reiMoveu[2]; 
    bool torreEsquerdaMoveu[2]; //esquerda = coluna a
    bool torreDireitaMoveu[2];

    Movimento historico[MAX_HISTORICO];
    int countHistorico;
};
```

**Estrutura do histórico de movimentos:*
```c
typedef struct {
    int origem[2];      // [linha, coluna]
    int destino[2];     // [linha, coluna]
    EstadoRoque estadoRoque;  // Estado do roque após o movimento
} Movimento;
```
