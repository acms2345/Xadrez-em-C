# Documentação do projeto de Xadrez em C
Tal código corresponde a um jogo de dois jogadores local, inspirado nas regras oficiais do xadrez.

## Sobre o funcionamento do código
Ao invés das pecas brancas e pretas, o código diferencia as peças por caracteres maiúsculos e minúsculos. 
### Organização dos arquivos
Para não colocar VÁRIAS linhas de código em um único arquivo, resolvi separar em dois arquivos:
- **xadrez.c**: é o código principal, com a exibição para o usuário.
- **jogadasvalidas.c**: faz a verificação principal das jogadas válidas (ou inválidas), por meio de uma função booleana.
Para conseguir usar a função booleana no xadrez.c, precisei usar o cabeçalho **jogadasvalidas.h** para ter as definições da função e conseguir interligar os dois arquivos.
Por isso, _o sistema de compilação dos codigos é um pouco diferente do convencional_. Mas a compilação depende do sistema operacional que você usa. Recomendo uma pesquisa sobre "compilação com mais de um arquivo em C".