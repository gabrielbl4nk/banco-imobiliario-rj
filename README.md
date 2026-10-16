# Banco Imobiliário RJ - Monitoria Prog 1

Jogo estilo Banco Imobiliário feito em C para rodar no terminal. As casas do tabuleiro são bairros e cidades do Rio de Janeiro, como Rio das Ostras, Niterói, Unamar e Duque de Caxias. Dá pra jogar com 4 pessoas no mesmo computador.

Trabalho da monitoria de Programação 1 do curso de Ciência da Computação, feito por Gabriel, Jorge e Luan.

## Como rodar

Precisa só de um compilador de C, como o gcc. O jogo não usa nenhuma biblioteca externa, só as que já vêm com o próprio C (stdio.h, stdlib.h, locale.h e time.h). No Windows dá pra instalar o gcc pelo MinGW, ou usar uma IDE que já vem com ele, como o Code::Blocks.

Para compilar e rodar:

```
gcc menu.c -o jogo
./jogo
```

O jogo foi feito para o Windows (usa system("cls")). Se as cores não aparecerem, tente no Windows Terminal. Deixa o terminal em tela cheia porque o tabuleiro é grande.

## Como jogar

- São 4 jogadores, cada um com uma cor: 1 vermelho, 2 azul, 3 verde e 4 amarelo.
- Todo mundo começa no INÍCIO com R$ 4000.
- Na sua vez você joga dois dados e anda a soma deles. Quem passa pelo INÍCIO ganha um dinheiro extra.
- Se cair numa propriedade sem dono, pode comprar. Se cair na de outro jogador, paga aluguel pra ele.
- Quanto mais perto do fim do tabuleiro, mais cara a propriedade e maior o aluguel.
- Se tirar dupla nos dados, joga de novo. Três duplas seguidas mandam direto pra prisão.
- Cair em "VÁ PARA A PRISÃO" também manda pra prisão, sem passar pelo INÍCIO.
- Dá pra fechar a partida e voltar pro menu a qualquer momento.

## Como ganha e como perde

Quem não tiver dinheiro pra pagar um aluguel vai à falência: sai do jogo e as propriedades dele voltam pro banco. Ganha o último jogador que sobrar.

## O que ainda falta

- Construir casas e hotéis nas propriedades (o nível já aparece no tabuleiro, mas ainda não dá pra aumentar)
- Vender propriedades pra conseguir pagar as dívidas e continuar no jogo (por enquanto quem não paga o aluguel já quebra)
- Regras da prisão (por enquanto o jogador só é movido pra lá)
- Eventos durante a partida
- Casas especiais, tipo sorte/revés e impostos
- Balancear os preços e os aluguéis
- Separar o código em funções (hoje está tudo dentro da main)
