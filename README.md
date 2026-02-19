# Documentação do projeto de Xadrez em C

[Versão em português abaixo/ Portuguese version below](#versão-em-português)

---

# English version

This code implements a local two-player chess game, inspired by the official rules of chess.

> **Note**: This is an educational project. Some advanced rules are not yet implemented.

> **Developer's note**: Please be aware that the source code, including all variable names, function names, comments, is written in Portuguese. I'm making the translation of certain parts of UI, but it takes time.

### 🔗 Useful Links

- **Online Demo**: [Test on OnlineGDB (OUTDATED VERSION)](https://onlinegdb.com/mCVxTRf8M)
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

Instead of traditional black and white pieces, the code differentiates them using uppercase and lowercase characters:

-   **White pieces**: UPPERCASE letters (P, T, C, B, Q, K)
-   **Black pieces**: lowercase letters (p, t, c, b, q, k)

The code also includes a scoring system for each player based on the value of each piece.

## 📁 Project Structure

```
Xadrez-em-C/
├── menu.c             # Main menu and entry point
├── jogo.c           # Main code (interface, game loop)
├── jogo.h           # Header that links jogo.c to menu.c.
├── jogadasvalidas.c   # Move validation logic
├── jogadasvalidas.h   # Header with prototypes
├── traducao.c         # Message translation functions
├── traducao.h          # Header with prototypes
└── README.md          # This file
```

### Main Functions

-   `ExibirTabuleiro()`: Prints the current state of the board.
-   `SalvarJogo()`: Saves the game information to a file named `salvamento.dat`.
-   `CarregarJogo()`: Loads the information saved by the `SalvarJogo()` function.
-   `obterCoordenada()`: Reads and validates the user's algebraic notation input.
-   `JogadaValida()`: Checks if a move is valid.
    -   `CasaAtacada()`: Checks if the square the king is moving to is under attack.
-   `PromocaoPeao()`: Allows choosing a piece for pawn promotion.
-   `atualizarPontuacao()`: Checks if a piece was captured and assigns the piece score accordingly (explained in detail in the scoring section).

## 📊 Scoring System

| Piece      | Value   |
| ---------- | ------- |
| Pawn (P/p) | 1       |
| Knight (C/c) | 3       |
| Bishop (B/b) | 3       |
| Rook (T/t) | 5       |
| Queen (Q/q)  | 9       |
| King (K/k)   | Victory |

> This scoring system does not directly determine the winner. It only gives an idea of which player potentially performed better during the match.

## 🎮 How to Play

1.  The names of the two players are entered into the system.
2.  The board is an 8x8 grid (with the row order being the reverse of conventional chess).
3.  To make a move, the user must enter it in algebraic notation (e.g., e2e4):
    -   First letter: origin column (a-h);
    -   First number: origin row (1-8);
    -   Second letter: destination column (a-h);
    -   Second number: destination row (1-8);
    -   Type "salvar" to save the game.
    -   Type "desistir" to forfeit the game and give victory to your opponent.
4.  The game includes a draw system based on the 50-move rule (100 moves - or half moves - without a capture or pawn move).

- If you wish, in the game there is a Help option, in which there are some quick instructions about the game.

### Example of a Move

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

Player1, enter your move in algebraic notation (ex: e2e4): e2e4

  a b c d e f g h
8 t c b k q b c t
7 p p p p p p p p
6                
5                
4         P       
3                
2 P P P P   P P P
1 T C B K Q B C T

Player2, enter your move in algebraic notation (ex: e2e4): e7e5

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

### 💾 About Saving and Loading Games

During the game, when prompted to enter the next move, you can also type "salvar" to save the current game state to the `salvamento.dat` file.
To resume a saved game, you must choose the "Load Saved Game" option from the main menu.

> The `salvamento.dat` file is binary and should not be edited manually.

## ⚠️ Known Limitations

1.  **No castling**: This special move is not implemented.
3.  **No en passant**: This special pawn capture is not implemented.
4.  **No draw detection**: For stalemate or repetition.

## 📄 License

This project is under the MIT License. See the `LICENSE` file for more details.

---

# Versão em português
Tal código corresponde a um jogo de dois jogadores local, inspirado nas regras oficiais do xadrez.

> **Nota**: Este é um projeto educacional. Algumas regras avançadas ainda não estão implementadas.

> **Nota do Desenvolvedor**: O código-fonte, incluindo nomes de variáveis, funções e comentários, está escrito em português. Estou trabalhando na tradução de certas partes.

### 🔗 Links úteis

- **Demo Online**: [Testar no OnlineGDB (VERSÃO DESATUALIZADA)](https://onlinegdb.com/mCVxTRf8M)
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
Ao invés das pecas brancas e pretas, o código diferencia as peças por caracteres maiúsculos e minúsculos:
- **Peças brancas**: letras MAIÚSCULAS (P, T, C, B, Q, K)
- **Peças pretas**: letras minúsculas (p, t, c, b, q, k)

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
└── README.md          # Este arquivo
```

### Principais funções

- `ExibirTabuleiro()`: Imprime o estado atual do tabuleiro.
- `SalvarJogo()`: Salva as informações da partida para serem acessados depois em um arquivo chamado `salvamento.dat`.
- `CarregarJogo()`: Acessa as informações salvas pela função `SalvarJogo()`.
- `obterCoordenada()`: Lê e valida entrada de notação algébrica do usuário.
- `JogadaValida()`: Verifica se o movimento é válido.
  - `CasaAtacada()`: Verifica se a casa para que o rei está se movendo não está em xeque.
- `PromocaoPeao()`: Permite escolher peça na promoção.
- `atualizarPontuacao()`: Verifica se houve captura e, se teve, atribui a pontuação de peças (melhor explicada no tópico a seguir).

## 📊 Sistema de pontuação

| Peça | Valor |
|------|-------|
| Peão (P/p) | 1 |
| Cavalo (C/c) | 3 |
| Bispo (B/b) | 3 |
| Torre (T/t) | 5 |
| Rainha (Q/q) | 9 |
| Rei (K/k) | Vitória |

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
> O arquivo `salvamento.dat` é binário, e por isso não deve ser editado manualmente.

## ⚠️ Limitações conhecidas

1. **Sem roque**: Movimento especial não implementado
3. **Sem en passant**: Captura especial de peão não implementada
4. **Sem detecção de empate**: Por afogamento ou repetição.

## 📄 Licença

Este projeto está sob a licença MIT. Veja o arquivo `LICENSE` para mais detalhes.
