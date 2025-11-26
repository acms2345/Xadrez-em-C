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
├── xadrez.c           # Código principal (interface, loop do jogo)
├── jogadasvalidas.c   # Lógica de validação de movimentos
├── jogadasvalidas.h   # Header com protótipos
└── README.md          # Este arquivo
```

### Principais funções

- `ExibirTabuleiro()`: Imprime o estado atual do tabuleiro
- `ObterCoordenada()`: Lê e valida entrada do usuário
- `JogadaValida()`: Verifica se o movimento é válido
- `PromocaoPeao()`: Permite escolher peça na promoção

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
2. O tabuleiro funciona com uma tabela de 8 linhas e 8 colunas.
3. Para o usuário mover, é necessário:
  - Inserir a linha de origem;
  - Inserir a coluna de origem;
  - Inserir a linha do destino;
  - E inserir a coluna do destino.

### Exemplo de jogada

```
  1 2 3 4 5 6 7 8
1 t c b k q b c t
2 p p p p p p p p
3                
4                
5                
6                
7 P P P P P P P P
8 T C B K Q B C T

Jogador1, digite a coordenada da linha de origem (1-8): 7
Jogador1, digite a coordenada da coluna de origem (1-8): 1
Jogador1, digite a coordenada da linha de destino (1-8): 6
Jogador1, digite a coordenada da coluna de destino (1-8): 1
```

## ⚠️ Limitações conhecidas

1. **Não verifica xeque**: O rei pode se mover para casa atacada
2. **Não detecta xeque-mate**: Jogo termina apenas com captura do rei
3. **Sem roque**: Movimento especial não implementado
4. **Sem en passant**: Captura especial de peão não implementada
5. **Entrada numérica apenas**: Não aceita notação algébrica (e4, Nf3)
6. **Sem detecção de empate**: Por afogamento, repetição ou 50 movimentos

## 📄 Licença

Este projeto está sob a licença MIT. Veja o arquivo `LICENSE` para mais detalhes.
