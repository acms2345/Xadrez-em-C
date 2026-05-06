# Documentação do projeto de Xadrez em C

[Versão em português abaixo/ Portuguese version below](#versão-em-português)

---

# English version

This code implements a local two-player chess game, inspired by the official rules of chess.

> **Note**: This is an educational project. Some advanced rules are not yet implemented.

> **Developer's note**: Please be aware that the source code, including all variable names, function names, comments, is written in Portuguese. I'm making the translation of certain parts of UI, but it takes time.

### 🔗 Useful Links

- **Online Demo**: [Test on OnlineGDB (2.1 VERSION)](https://onlinegdb.com/RQbpxn_Xr)
- **Repository**: [GitHub - Xadrez-em-C](https://github.com/acms2345/Xadrez-em-C)
- **Pre-compiled Executable**: [releases page](https://github.com/acms2345/Xadrez-em-C/releases)
- **Project architecture**: [architecture.md](https://github.com/acms2345/Xadrez-em-C/blob/main/architecture.md)

## 📋 System Requirements

- **C Compiler**: GCC, Clang, or any standard C compiler
- **Operating System**: Windows, Linux, or macOS
- **Disk Space**: Less than 1 MB

## 🚀 Quick start
The easiest way to get started:
1. Download the latest release from [GitHub Releases](https://github.com/acms2345/Xadrez-em-C/releases)
2. Extract the executable for your OS (Windows/Linux/macOS)
3. Run it directly - no compilation needed!

## How to Install and Use the Source Code

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

```bash
make clean
make
```

### 3. Run the code
Just find the `xadrez.exe` file generated after compilation (it should be in the same folder as the other files). Or you can run:

On Windows:
```bash
.\xadrez
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
├── jogadasvalidas.h   # Header with prototypes and data structures
├── traducao.c         # Message translation functions (i18n system)
├── traducao.h         # Header with prototypes
├── cores.h            # Terminal color definitions (ANSI codes)
├── Makefile           # Build rules
├── LICENSE            # MIT License file
└── README.md          # This file
```

> **Note**: `salvamento.dat` is generated at runtime when a game is saved; it is not part of the source tree.



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
    -   Type "draw" to propose a draw to your opponent (the opponent can accept with `y`/`s` or decline with `n`).
4.  The game includes a draw system based on the 50-move rule (100 moves - or half moves - without a capture or pawn move).
5.  The game also detects draws by **threefold repetition** (same position occurring 3 times) and **insufficient mating material** (e.g., King vs King).

- If you wish, in the game there is a Help option, in which there are some quick instructions about the game.

### Example of a Move

```
  ╔═════════════════╗
  ║ a b c d e f g h ║
  ╠═════════════════╣
8 ║ ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜ ║
7 ║ ♟ ♟ ♟ ♟ ♟ ♟ ♟ ♟ ║
6 ║                 ║
5 ║                 ║
4 ║                 ║
3 ║                 ║
2 ║ ♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙ ║
1 ║ ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖ ║
  ╚═════════════════╝

Player1, enter your move in algebraic notation (ex: e2e4): e2e4

  ╔═════════════════╗
  ║ a b c d e f g h ║
  ╠═════════════════╣
8 ║ ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜ ║
7 ║ ♟ ♟ ♟ ♟ ♟ ♟ ♟ ♟ ║
6 ║                 ║
5 ║                 ║
4 ║         ♙       ║
3 ║                 ║
2 ║ ♙ ♙ ♙ ♙   ♙ ♙ ♙ ║
1 ║ ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖ ║
  ╚═════════════════╝

Player2, enter your move in algebraic notation (ex: e2e4): e7e5

  ╔═════════════════╗
  ║ a b c d e f g h ║
  ╠═════════════════╣
8 ║ ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜ ║
7 ║ ♟ ♟ ♟ ♟   ♟ ♟ ♟ ║
6 ║                 ║
5 ║         ♟       ║
4 ║         ♙       ║
3 ║                 ║
2 ║ ♙ ♙ ♙ ♙   ♙ ♙ ♙ ║
1 ║ ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖ ║
  ╚═════════════════╝

...
```

### 💾 About Saving and Loading Games

During the game, when prompted to enter the next move, you can also type "salvar"/"save" to save the current game state to the `salvamento.dat` file.
To resume a saved game, you must choose the "Load Saved Game" option from the main menu.

> The `salvamento.dat` file is binary and should not be edited manually. Only one game can be saved at a time — saving overwrites the previous file.


## ⚠️ Known Limitations

1.  **No moves replay**: The game tracks individual moves, but doesn't allow replaying them.
2.  **Single save slot**: Only one game can be saved at a time (`salvamento.dat` is overwritten on each save).
3.  **No network play**: Local two-player only; no AI or online opponent.

## 📄 License

This project is under the MIT License. See the `LICENSE` file for more details.

---

# Versão em português
Tal código corresponde a um jogo de dois jogadores local, inspirado nas regras oficiais do xadrez.

> **Nota**: Este é um projeto educacional. Algumas regras avançadas ainda não estão implementadas.

> **Nota do Desenvolvedor**: O código-fonte, incluindo nomes de variáveis, funções e comentários, está escrito em português. Estou trabalhando na tradução de certas partes.

### 🔗 Links úteis

- **Demo Online**: [Testar no OnlineGDB (VERSÃO 2.1)](https://onlinegdb.com/RQbpxn_Xr)
- **Repositório**: [GitHub - Xadrez-em-C](https://github.com/acms2345/Xadrez-em-C)
- **Executável pré-compilado**: [página de releases](https://github.com/acms2345/Xadrez-em-C/releases)
- **Arquitetura do projeto**: [architecture.md](https://github.com/acms2345/Xadrez-em-C/blob/main/architecture.md)

## 📋 Requisitos do Sistema

- **Compilador C**: GCC, Clang ou qualquer compilador C padrão
- **Sistema Operacional**: Windows, Linux ou macOS
- **Espaço em disco**: Menos de 1 MB

## 🚀 Instalação rápida
A maneira mais fácil de começar:
1. Baixe a última versão em [GitHub Releases](https://github.com/acms2345/Xadrez-em-C/releases)
2. Extraia o executável para seu sistema operacional (Windows/Linux/macOS)
3. Execute-o diretamente - não é necessário compilar!

## Como Instalar e Usar o Código-Fonte

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

```bash
make clean
make
```

### 3. Executar o código
- Apenas é necessário encontrar o arquivo `xadrez.exe` gerado após a compilação (ele deve estar na mesma pasta dos outros arquivos). Ou, você pode abrir o arquivo:
No Windows:
```bash
.\xadrez
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
├── jogadasvalidas.h   # Header com protótipos e estruturas de dados
├── traducao.c         # Funções de tradução de mensagens
├── traducao.h          # Header com protótipos
├── cores.h            # Definição de cores para o terminal
├── Makefile           # Regras de compilação
├── LICENSE             # Licença do projeto
└── README.md          # Este arquivo
```

> **Nota**: `salvamento.dat` é gerado em tempo de execução quando uma partida é salva; não faz parte do código-fonte.




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
  - Digite "empatar" para propor empate ao oponente (o oponente pode aceitar com `y`/`s` ou recusar com `n`).

4. O jogo possui o sistema de empate por 50 lances (100 movimentos - ou seja, meias-jogadas - sem captura ou movimento de peão).
5. O jogo também detecta empate por **repetição tripla** (mesma posição ocorrendo 3 vezes) e por **material insuficiente** (ex: Rei vs Rei).

- Caso você queira, no jogo há a opção de Ajuda, na qual há algumas instruções rápidas sobre o jogo.

### Exemplo de jogada

```
  ╔═════════════════╗
  ║ a b c d e f g h ║
  ╠═════════════════╣
8 ║ ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜ ║
7 ║ ♟ ♟ ♟ ♟ ♟ ♟ ♟ ♟ ║
6 ║                 ║
5 ║                 ║
4 ║                 ║
3 ║                 ║
2 ║ ♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙ ║
1 ║ ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖ ║
  ╚═════════════════╝

Jogador1, digite a jogada em notação algébrica (ex: e2e4): e2e4

  ╔═════════════════╗
  ║ a b c d e f g h ║
  ╠═════════════════╣
8 ║ ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜ ║
7 ║ ♟ ♟ ♟ ♟ ♟ ♟ ♟ ♟ ║
6 ║                 ║
5 ║                 ║
4 ║         ♙       ║
3 ║                 ║
2 ║ ♙ ♙ ♙ ♙   ♙ ♙ ♙ ║
1 ║ ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖ ║
  ╚═════════════════╝

Jogador2, digite a jogada em notação algébrica (ex: e2e4): e7e5

  ╔═════════════════╗
  ║ a b c d e f g h ║
  ╠═════════════════╣
8 ║ ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜ ║
7 ║ ♟ ♟ ♟ ♟   ♟ ♟ ♟ ║
6 ║                 ║
5 ║         ♟       ║
4 ║         ♙       ║
3 ║                 ║
2 ║ ♙ ♙ ♙ ♙   ♙ ♙ ♙ ║
1 ║ ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖ ║
  ╚═════════════════╝

...
```

### 💾 Sobre o salvamento e carregamento de partidas

Durante o jogo, quando solicitado para digitar o próximo movimento da peça, você também pode digitar "salvar"/"save" para salvar a partida atual no arquivo `salvamento.dat`.
Para retomar a partida salva, você deve escolher a opção de "Carregar Partida Salva" presente no menu. 
> O arquivo `salvamento.dat` é binário e não deve ser editado manualmente. Apenas uma partida pode ser salva por vez — salvar sobrescreve o arquivo anterior.



## ⚠️ Limitações conhecidas

1. **Sem replay de movimentos**: O jogo rastreia movimentos individuais, mas não permite reproduzi-los.
2. **Apenas um slot de salvamento**: Somente uma partida pode ser salva por vez (`salvamento.dat` é sobrescrito a cada salvamento).
3. **Sem jogo em rede**: Apenas dois jogadores locais; sem IA ou oponente online.

## 📄 Licença

Este projeto está sob a licença MIT. Veja o arquivo `LICENSE` para mais detalhes.
