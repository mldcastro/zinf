# zinf

Este repositório guarda o código do jogo `zinf`, o trabalho final da cadeira de Algoritmos e Programação.

Para rodar o código é necessário ter a linguagem C instalada.

O formatador de código usado é o formatador [`clang-format`](https://clang.llvm.org/docs/ClangFormat.html) (versão 12).

## Compilação e execução em Linux

Para compilar o código em um sistema Linux, basta rodar o comando `make main` no diretório raíz do repositório.
Este comando irá gerar um binário chamado `main` que poderá ser executado através da linha de comando `./main`.

## Jogo

Ao executar o binário, você irá ver uma tela de menu. Para iniciar um novo jogo basta pressionar `Enter`. Para
ver a tabela de pontuações basta pressionar `S` e para sair basta pressionar `X` ou a tecla `Esc`.

A movimentação do personagem é feita através das teclas:

- `W`: mover para cima;
- `A`: mover para a esquerda;
- `S`: mover para baixo;
- `D`: mover para a direita;

Para atacar, pressione a tecla `J`.

Ganhando ou perdendo o jogo, a tela final irá pedir o seu nome para salvar a sua pontuação caso ela esteja entre
as 5 maiores. Após digitar o seu nome, pressione `Enter` para enviar o nome e em seguida ser redirecionado ao menu
de entrada.
