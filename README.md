# Documentação do projeto de Xadrez em C

[Versão em português abaixo/ Portuguese version below](#versão-em-português)

---

# English version

This code implements a local two-player chess game, inspired by the official rules of chess.

> **Note**: This is an educational project. Some advanced rules are not yet implemented.

> **Developer's note**: Please be aware that the source code, including all variable names, function names, comments, is written in Portuguese. I'm making the translation of certain parts of UI, but it takes time.

### 🔗 Useful Links

- **Online Demo**: [Test on OnlineGDB (1.5 VERSION)](https://onlinegdb.com/JubxiCZUy)
- **Repository**: [GitHub - Xadrez-em-C](https://github.com/acms2345/Xadrez-em-C)
- **Pre-compiled Executable**: [releases page](https://github.com/acms2345/Xadrez-em-C/releases)

## 📋 System Requirements

- **C Compiler**: GCC, Clang, or any standard C compiler
- **Operating System**: Windows, Linux, or macOS
- **Disk Space**: Less than 1 MB

## 🚀 How to Install and Run

### 1. **Download the Project**

#### Option A: Clone from GitHub
```bash
git clone https://github.com/acms2345/Xadrez-em-C.git
cd Xadrez-em-C
```

#### Option B: Direct download

Access the GitHub repository and click "Code" → "Download ZIP". Then extract the file.

### 2. Compile the project

Open terminal/command prompt in the project folder and run:

If using GCC:
```bash
gcc menu.c jogo.c jogadasvalidas.c traducao.c -o xadrez
```
If using Clang:
```bash
clang menu.c jogo.c jogadasvalidas.c traducao.c -o xadrez
```
Or if using MinGW (Windows):
```bash
mingw32-gcc menu.c jogo.c jogadasvalidas.c traducao.c -o xadrez
```

### 3. Run the code
Just find the `xadrez.exe` file generated after compilation (it should be in the same folder as the other files). Or you can run:

On Windows:
```bash
xadrez.exe
```
On Linux or macOS:
```bash
./xadrez
```

## How the Code Works


-   **White pieces**: ♙ ♖ ♘ ♗ ♕ ♔ (P, T, C, B, Q, K)
-   **Black pieces**: ♟ ♜ ♞ ♝ ♛ ♚ (p, t, c, b, q, k)

Inside the code, instead of white and black pieces, they are differentiated by uppercase and lowercase characters.

The code also includes a scoring system for each player based on the value of each piece.

## 📁 Project Structure

```
Xadrez-em-C/
├── menu.c             # Main menu and entry point
├── jogo.c             # Main code (interface, game loop)
├── jogo.h             # Header that links jogo.c to menu.c
├── jogadasvalidas.c   # Move validation logic
├── jogadasvalidas.h   # Header with prototypes
├── traducao.c         # Message translation functions (i18n system)
├── traducao.h         # Header with prototypes
├── cores.h            # Terminal color definitions (ANSI codes)
├── LICENSE            # MIT License file
└── README.md          # This file
```

### Main Functions

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
-   `ReiEmXeque()`: Checks if the current player's king is in check.
-   `XequeMate()`: Detects checkmate (king in check with no legal moves).
-   `Afogamento()`: Detects stalemate (no legal moves but king not in check).

## 📊 Scoring System

| Piece      |Symbol   |Value   |
| ---------- |---------|------- |
| Pawn (P/p) |♙ ♟  |1       |
| Knight (C/c) |♘ ♞  |3       |
| Bishop (B/b) |♗ ♝  |3       |
| Rook (T/t) |♖ ♜  |5       |
| Queen (Q/q)  |♕ ♛  |9       |
| King (K/k)   |♔ ♚  |Victory |

> This scoring system does not directly determine the winner. It only gives an idea of which player potentially performed better during the match.

## 🎮 How to Play

1.  The names of the two players are entered into the system.
2.  The board is an 8x8 grid (with the row order being the reverse of conventional chess).
3.  To make a move, the user must enter it in algebraic notation (e.g., e2e4):
    -   First letter: origin column (a-h);
    -   First number: origin row (1-8);
    -   Second letter: destination column (a-h);
    -   Second number: destination row (1-8);
    -   Type "save" to save the game.
    -   Type "resign" to forfeit the game and give victory to your opponent.
4.  The game includes a draw system based on the 50-move rule (100 moves - or half moves - without a capture or pawn move).

- If you wish, in the game there is a Help option, in which there are some quick instructions about the game.

### Example of a Move

```
  a b c d e f g h
8 ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜
7 ♟ ♟ ♟ ♟ ♟ ♟ ♟ ♟
6                
5                
4                
3                
2 ♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙
1 ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖

Player1, enter your move in algebraic notation (ex: e2e4): e2e4

  a b c d e f g h
8 ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜
7 ♟ ♟ ♟ ♟ ♟ ♟ ♟ ♟
6                
5                
4            ♙       
3                
2 ♙ ♙ ♙ ♙   ♙ ♙ ♙
1 ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖

Player2, enter your move in algebraic notation (ex: e2e4): e7e5

  a b c d e f g h
8 ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜
7 ♟ ♟ ♟ ♟   ♟ ♟ ♟
6                
5            ♟      
4            ♙             
3                
2 ♙ ♙ ♙ ♙   ♙ ♙ ♙
1 ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖

...
```

### 💾 About Saving and Loading Games

During the game, when prompted to enter the next move, you can also type "salvar" to save the current game state to the `salvamento.dat` file.
To resume a saved game, you must choose the "Load Saved Game" option from the main menu.

> The `salvamento.dat` file is binary and should not be edited manually.

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
struct Salvamento {
    char tabuleiro[8][8];
    int jogadorDaVez;
    int movimentosFeitos;
    int movimentosSemCapturaouPiao;
    Jogador jogadores[2];
};
```

## ⚠️ Known Limitations

1.  **No castling**: This special move is not implemented.
2.  **No en passant**: This special pawn capture is not implemented.
3.  **No repetition detection**: Draw by repetition is not implemented (but stalemate and 50-move rule are).
4.  **No move history**: The game doesn't track individual moves, only move counters.

## 📄 License

This project is under the MIT License. See the `LICENSE` file for more details.

---

# Versão em português
Tal código corresponde a um jogo de dois jogadores local, inspirado nas regras oficiais do xadrez.

> **Nota**: Este é um projeto educacional. Algumas regras avançadas ainda não estão implementadas.

> **Nota do Desenvolvedor**: O código-fonte, incluindo nomes de variáveis, funções e comentários, está escrito em português. Estou trabalhando na tradução de certas partes.

### 🔗 Links úteis

- **Demo Online**: [Testar no OnlineGDB (VERSÃO 1.5)](https://onlinegdb.com/JubxiCZUy)
- **Repositório**: [GitHub - Xadrez-em-C](https://github.com/acms2345/Xadrez-em-C)
- **Executável pré-compilado**: [página de releases](https://github.com/acms2345/Xadrez-em-C/releases)

## 📋 Requisitos do Sistema

- **Compilador C**: GCC, Clang ou qualquer compilador C padrão
- **Sistema Operacional**: Windows, Linux ou macOS
- **Espaço em disco**: Menos de 1 MB

## 🚀 Como Instalar e Executar

### 1. **Baixar o Projeto**

#### Opção A: Clonar do GitHub
```bash
git clone https://github.com/acms2345/Xadrez-em-C.git
cd Xadrez-em-C
```
#### Opção B: Download direto
Acesse o repositório no GitHub e clique em "Code" → "Download ZIP". Depois, extraia o arquivo.

### 2. **Compilar o projeto**

Abra o terminal/prompt de comando na pasta do projeto e execute:

Caso use o GCC:
```bash
gcc menu.c jogo.c jogadasvalidas.c traducao.c -o xadrez
```
Caso use o Clang:
```bash
clang menu.c jogo.c jogadasvalidas.c traducao.c -o xadrez
```
Ou caso use o MinGW (Windows):
```bash
mingw32-gcc menu.c jogo.c jogadasvalidas.c traducao.c -o xadrez
```

### 3. Executar o código
- Apenas é necessário encontrar o arquivo `xadrez.exe` gerado após a compilação (ele deve estar na mesma pasta dos outros arquivos). Ou, você pode abrir o arquivo:
No Windows:
```bash
xadrez.exe
```
No Linux ou MacOS:
```bash
./xadrez
```
## Sobre o funcionamento do código

- **Peças brancas**: ♙ ♖ ♘ ♗ ♕ ♔ (P, T, C, B, Q, K)
- **Peças pretas**: ♟ ♜ ♞ ♝ ♛ ♚ (p, t, c, b, q, k)

Dentro do código, ao invés de peças brancas e pretas, elas são diferenciadas por caracteres maiúsculos e minúsculos.

Por enquanto, o código também conta com um sistema de pontuação para cada jogador com base no valor de cada peça.

## 📁 Estrutura do projeto

```
Xadrez-em-C/
├── menu.c             # Menu principal e ponto de entrada
├── jogo.c           # Código principal (interface, loop do jogo)
├── jogo.h             # Header que interliga jogo.c a menu.c
├── jogadasvalidas.c   # Lógica de validação de movimentos
├── jogadasvalidas.h   # Header com protótipos
├── traducao.c         # Funções de tradução de mensagens
├── traducao.h          # Header com protótipos
├── cores.h            # Definição de cores para o terminal
├── salvamento.dat      # Arquivo binário para salvar o estado do jogo
├── LICENSE             # Licença do projeto
└── README.md          # Este arquivo
```

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
- `ReiEmXeque()`: Verifica se o rei do jogador atual está em xeque.
- `XequeMate()`: Detecta xeque-mate (rei em xeque sem movimentos legais).
- `Afogamento()`: Detecta afogamento (nenhum movimento legal mas rei não em xeque).


## 📊 Sistema de pontuação

| Peça |Símbolos |Valor |
|------|---------|-------|
| Peão (P/p) | ♙ ♟  | 1 |
| Cavalo (C/c) | ♘ ♞  | 3 |
| Bispo (B/b) | ♗ ♝  | 3 |
| Torre (T/t) | ♖ ♜  | 5 |
| Rainha (Q/q) | ♕ ♛  | 9 |
| Rei (K/k) |♔ ♚  | Vitória |

> Esse sistema não influencia diretamente em quem ganha. Eles só dão uma ideia de qual jogador possivelmente se saiu melhor na partida.

## 🎮 Como jogar 

1. O nome dos dois jogadores são informados ao sistema.
2. O tabuleiro funciona com uma tabela de 8 linhas e 8 colunas (com a ordem de linhas sendo o contrário ao convencional do xadrez).
3. Para o usuário mover, é necessário inserir a jogada em notação algébrica (ex: e2e4):
  - Primeira letra: coluna de origem (a-h);
  - Primeiro número: linha de origem (1-8);
  - Segunda letra: coluna de destino (a-h);
  - Segundo número: linha de destino (1-8);
  - Digite "salvar" para salvar o jogo.
  - Digite "desistir" para desistir do jogo e dar a vitória a seu oponente.

4. O jogo possui o sistema de empate por 50 lances (100 movimentos - ou seja, meias-jogadas - sem captura ou movimento de peão).

- Caso você queira, no jogo há a opção de Ajuda, na qual há algumas instruções rápidas sobre o jogo.

### Exemplo de jogada

```
  a b c d e f g h
8 t c b k q b c t
7 p p p p p p p p
6                
5                
4                
3                
2 P P P P P P P P
1 T C B K Q B C T

Jogador1, digite a jogada em notacao algebrica (ex: e2e4):  e2e4

  a b c d e f g h
8 t c b k q b c t
7 p p p p p p p p
6                
5                
4         P       
3                
2 P P P P   P P P
1 T C B K Q B C T

Jogador2, digite a jogada em notacao algebrica (ex: e2e4):  e7e5

  a b c d e f g h
8 t c b k q b c t
7 p p p p   p p p
6                
5         p      
4         P       
3                
2 P P P P   P P P
1 T C B K Q B C T

...
```

### 💾 Sobre o salvamento e carregamento de partidas

Durante o jogo, quando solicitado para digitar o próximo movimento da peça, você também pode digitar "salvar" para salvar a partida atual no arquivo `salvamento.dat`.
Para retomar a partida salva, você deve escolher a opção de "Carregar Partida Salva" presente no menu. 
> O arquivo `salvamento.dat` é binário e não deve ser editado manualmente.

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
struct Salvamento {
    char tabuleiro[8][8];
    int jogadorDaVez;
    int movimentosFeitos;
    int movimentosSemCapturaouPiao;
    Jogador jogadores[2];
};
```

## ⚠️ Limitações conhecidas

1. **Sem roque**: Movimento especial não implementado
2. **Sem en passant**: Captura especial de peão não implementada
3. **Sem detecção de repetição**: O empate por repetição não é detectado (mas afogamento e regra dos 50 lances são).
4. **Sem histórico de movimentos**: O jogo não rastreia movimentos individuais, apenas contadores de movimentos.

## 📄 Licença

Este projeto está sob a licença MIT. Veja o arquivo `LICENSE` para mais detalhes.
