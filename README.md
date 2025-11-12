# Documentação do projeto de Xadrez em C
Tal código corresponde a um jogo de dois jogadores local, inspirado nas regras oficiais do xadrez.

## Sobre o funcionamento do código
Ao invés das pecas brancas e pretas, o código diferencia as peças por caracteres maiúsculos e minúsculos. 

Por enquanto, o código também conta com um sistema de pontuação para cada jogadorcom base no valor de cada peça.
### Organização dos arquivos
Para não colocar VÁRIAS linhas de código em um único arquivo, resolvi separar em dois arquivos:
- `xadrez.c`: é o código principal, com a exibição para o usuário.
- `jogadasvalidas.c`: faz a verificação principal das jogadas válidas (ou inválidas), por meio de uma função booleana.
Para conseguir usar a função booleana no xadrez.c, precisei usar o cabeçalho `jogadasvalidas.h` para ter as definições da função e conseguir interligar os dois arquivos.
Por isso, _o sistema de compilação dos codigos é um pouco diferente do convencional_. Mas a compilação depende do sistema operacional que você usa. Recomendo uma pesquisa sobre _"compilação com mais de um arquivo em C"_.
### Como jogar
- O nome dos dois jogadores são informados ao sistema.
- O tabuleiro funciona com uma tabela de 8 linhas e 8 colunas.
- Para o usuário mover, é necessário:
 - Inserir a linha de origem;
 - Inserir a coluna de origem;
 - Inserir a linha do destino;
 - E inserir a coluna do destino.
