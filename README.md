# Documentação do projeto de Xadrez em C
Tal código corresponde a um jogo de dois jogadores local, inspirado nas regras oficiais do xadrez.

## Sobre o funcionamento do código
Ao invés das pecas brancas e pretas, o código diferencia as peças por caracteres maiúsculos e minúsculos. 
### Organização dos arquivos
Para não colocar VÁRIAS linhas de código em um único arquivo, resolvi separar em dois arquivos:
- **xadrez.c**: é o código principal, com a exibição para o usuário.
- **jogadasvalidas.c**: faz a verificação principal das jogadas válidas (ou inválidas), por meio de uma função booleana.