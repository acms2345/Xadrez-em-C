# Documentação do projeto de Xadrez em C

# English version

This code implements a local two-player chess game, inspired by the official rules of chess.

> **Note**: This is an educational project. Some advanced rules are not yet implemented.

> **Developer's note**: Please be aware that the source code, including all variable names, function names, and comments, is written in Portuguese. I'm trying to make the translation of certain parts, but it takes time.

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
├── jogadasvalidas.c   # Move validation logic
├── jogadasvalidas.h   # Header with prototypes
└── README.md          # This file
```

### Main Functions

-   `ExibirTabuleiro()`: Prints the current state of the board.
-   `SalvarJogo()`: Saves the game information to a file named `salvamento.dat`.
-   `CarregarJogo()`: Accesses the information saved by the `SalvarJogo()` function.
-   `obterCoordenada()`: Reads and validates the user's algebraic notation input.
-   `JogadaValida()`: Checks if a move is valid.
    -   `CasaAtacada()`: Checks if the square the king is moving to is under attack.
-   `PromocaoPeao()`: Allows choosing a piece for pawn promotion.

## 📊 Scoring System

| Piece      | Value   |
| ---------- | ------- |
| Pawn (P/p) | 1       |
| Knight (C/c) | 3       |
| Bishop (B/b) | 3       |
| Rook (T/t) | 5       |
| Queen (Q/q)  | 9       |
| King (K/k)   | Victory |

## 🎮 How to Play

-   You can test a demo of the project at [this link](https://onlinegdb.com/dUODuECUZ).

-   If you download the project, you can compile it using a C compiler like GCC. With it, you can run the following command:

```bash
gcc menu.c jogo.c jogadasvalidas.c -o xadrez
```

1.  The names of the two players are entered into the system.
2.  The board is an 8x8 grid (with the row order being the reverse of conventional chess).
3.  To make a move, the user must enter it in algebraic notation (e.g., e2e4):
    -   First letter: origin column (a-h);
    -   First number: origin row (1-8);
    -   Second letter: destination column (a-h);
    -   Second number: destination row (1-8);
    -   Type "salvar" to save the game.
4.  The game includes a draw system based on the 50-move rule (100 moves without a capture or pawn move).

### Example of a Move

```
  a b c d e f g h
1 t c b k q b c t
2 p p p p p p p p
3
4
5
6
7 P P P P P P P P
8 T C B K Q B C T

Player1, enter your move in algebraic notation (e.g., e2e4): e7e5
```

### 💾 About Saving and Loading Games

During the game, when prompted to enter the next move, you can also type "salvar" to save the current game state to the `salvamento.dat` file.
To resume a saved game, you must choose the "Load Saved Game" option from the main menu.

> The `salvamento.dat` file is binary and should not be edited manually.

## ⚠️ Known Limitations

1.  **No checkmate detection**: The game only ends when the king is captured.
2.  **No castling**: This special move is not implemented.
3.  **No en passant**: This special pawn capture is not implemented.
4.  **Extended notation only**: Does not accept standard algebraic notation (e.g., e4, Nf3), only the extended format (e.g., e2e4).
5.  **No draw detection**: For stalemate or repetition.

## 📄 License

This project is under the MIT License. See the `LICENSE` file for more details.

# Versão em português
Tal código corresponde a um jogo de dois jogadores local, inspirado nas regras oficiais do xadrez.

> **Nota**: Este é um projeto educacional. Algumas regras avançadas ainda não estão implementadas.

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
├── jogadasvalidas.c   # Lógica de validação de movimentos
├── jogadasvalidas.h   # Header com protótipos
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

## 📊 Sistema de pontuação

| Peça | Valor |
|------|-------|
| Peão (P/p) | 1 |
| Cavalo (C/c) | 3 |
| Bispo (B/b) | 3 |
| Torre (T/t) | 5 |
| Rainha (Q/q) | 9 |
| Rei (K/k) | Vitória |

## 🎮 Como jogar 
- O link para testar a demo do projeto é [esse aqui](https://onlinegdb.com/dUODuECUZ).

- Caso você baixe o projeto, o processo de compilação deve ocorrer por meio de um compilador como o GCC. Com ele, você pode executar o seguinte comando:
```bash
gcc menu.c jogo.c jogadasvalidas.c -o xadrez
```

1. O nome dos dois jogadores são informados ao sistema.
2. O tabuleiro funciona com uma tabela de 8 linhas e 8 colunas (com a ordem de linhas sendo o contrário ao convencional do xadrez).
3. Para o usuário mover, é necessário inserir a jogada em notação algébrica (ex: e2e4):
  - Primeira letra: coluna de origem (a-h);
  - Primeiro número: linha de origem (1-8);
  - Segunda letra: coluna de destino (a-h);
  - Segundo número: linha de destino (1-8);
  - Digite "salvar" para salvar o jogo.

4. O jogo possui o sistema de empate por 50 lances (100 movimentos sem captura ou movimento de peão).

### Exemplo de jogada

```
  a b c d e f g h
1 t c b k q b c t
2 p p p p p p p p
3                
4                
5                
6                
7 P P P P P P P P
8 T C B K Q B C T

Jogador1, digite a jogada em notacao algebrica (ex: e2e4):  e7e5
```

### 💾 Sobre o salvamento e carregamento de partidas

Durante o jogo, quando solicitado para digitar o próximo movimento da peça, você também pode digitar "salvar" para salvar a partida atual no arquivo `salvamento.dat`.
Para retomar a partida salva, você deve escolher a opção de "Carregar Partida Salva" presente no menu. 
> O arquivo `salvamento.dat` é binário, e por isso não deve ser editado manualmente.

## ⚠️ Limitações conhecidas

1. **Não detecta xeque-mate**: Jogo termina apenas com captura do rei
2. **Sem roque**: Movimento especial não implementado
3. **Sem en passant**: Captura especial de peão não implementada
4. **Entrada estendida apenas**: Não aceita notação algébrica completa (e4, Nf3), apenas formato estendido (e2e4)
5. **Sem detecção de empate**: Por afogamento ou repetição.

## 📄 Licença

Este projeto está sob a licença MIT. Veja o arquivo `LICENSE` para mais detalhes.
