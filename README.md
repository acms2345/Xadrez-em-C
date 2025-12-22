# Documentação do projeto de Xadrez em C
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
├── xadrez.c           # Código principal (interface, loop do jogo)
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
1. O nome dos dois jogadores são informados ao sistema.
2. O tabuleiro funciona com uma tabela de 8 linhas e 8 colunas (com a ordem de linhas sendo o contrário ao convencional do xadrez).
3. Para o usuário mover, é necessário inserir a jogada em notação algébrica (ex: e2e4):
  - Primeira letra: coluna de origem (a-h);
  - Primeiro número: linha de origem (1-8);
  - Segunda letra: coluna de destino (a-h);
  - Segundo número: linha de destino (1-8);
  - Digite "salvar" para salvar o jogo.

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

## ⚠️ Limitações conhecidas

1. **Não detecta xeque-mate**: Jogo termina apenas com captura do rei
2. **Sem roque**: Movimento especial não implementado
3. **Sem en passant**: Captura especial de peão não implementada
4. **Entrada estendida apenas**: Não aceita notação algébrica completa (e4, Nf3), apenas formato estendido (e2e4)
5. **Sem detecção de empate**: Por afogamento ou repetição.

## 📄 Licença

Este projeto está sob a licença MIT. Veja o arquivo `LICENSE` para mais detalhes.
