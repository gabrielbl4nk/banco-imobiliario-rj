#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

int main() {
    int opcaoMenu;
    int continuarMenu;
    int opcaoJogo;
    int rodando;
    int jogadorAtual;
    int dado1, dado2, total;
    int linha, coluna, pos, r;
    int p;
    int posicaoAntiga;
    int landedPosicao;
    int bonusInicio;
    int novaPosicao;
    int opcaoCompra;
    int indoParaPrisao;
    int foiBonusInicio;
    int foiCasaPrisao;
    int foiTresDuplas;
    int faliu;
    int ativosRestantes;
    int vencedor;
    int valorAssalto;
    int perdaAssalto;
    int foiAssaltado;

    int posicao[4];
    int saldo[4];
    int ativo[4];
    int duplasConsecutivas;
    int tabuleiroPos[11][11];
    int nivelConstrucao[40];
    int dono[40];

    int precoCasas[40] = {
        0, 220, 290, 360, 430, 500, 570, 640, 710, 780,
        0, 850, 920, 990, 1060, 1130, 1200, 1270, 1340, 1410,
        0, 1480, 1550, 1620, 1690, 1760, 1830, 1900, 1970, 2040,
        0, 2110, 2180, 2250, 2320, 2390, 2460, 2530, 2600, 2670
    };

    int aluguelCasas[40] = {
        0, 30, 40, 50, 60, 80, 90, 100, 110, 120,
        0, 130, 140, 150, 160, 170, 180, 190, 200, 210,
        0, 220, 230, 240, 250, 260, 270, 280, 300, 310,
        0, 320, 330, 340, 350, 360, 370, 380, 390, 400
    };

    char nomeCasas[40][35] = {
        "INICIO",
        "Itaborai",
        "Centro - RO",
        "Copacabana",
        "Costazul",
        "Sao Goncalo",
        "Marica",
        "Ancora",
        "Cabo Frio",
        "Ipanema",
        "PRISAO / VISITANDO",
        "Jardim Leal",
        "Xerem",
        "Leblon",
        "Niteroi",
        "Campos Eliseos",
        "Barra da Tijuca",
        "Sarapui",
        "Botafogo",
        "25 de Agosto",
        "ESTACIONAMENTO",
        "Itaperuna",
        "Flamengo",
        "Vila Sao Luis",
        "Lapa",
        "Parque Lafaiete",
        "Maracana",
        "Gramacho",
        "Ilha do Governador",
        "Centro Caxias",
        "VA PARA A PRISAO",
        "Recreio",
        "Jacarepagua",
        "Tijuca",
        "Meier",
        "Penha",
        "Madureira",
        "Duque de Caxias",
        "Unamar",
        "Macuco"
    };

    setlocale(LC_ALL, "Portuguese");
    srand((unsigned int) time(NULL));

    for (linha = 0; linha <= 10; linha++) {
        for (coluna = 0; coluna <= 10; coluna++) {
            if (linha == 10) {
                tabuleiroPos[linha][coluna] = 10 - coluna;
            } else if (coluna == 0) {
                tabuleiroPos[linha][coluna] = 20 - linha;
            } else if (linha == 0) {
                tabuleiroPos[linha][coluna] = 20 + coluna;
            } else if (coluna == 10) {
                tabuleiroPos[linha][coluna] = 30 + linha;
            } else {
                tabuleiroPos[linha][coluna] = -1;
            }
        }
    }

    bonusInicio = 200;
    valorAssalto = 150;
    continuarMenu = 1;

    while (continuarMenu == 1) {
        system("cls");

        printf("===================================================\n");
        printf("      BANCO IMOBILIÁRIO RJ - MONITORIA PROG 1\n");
        printf("===================================================\n");
        printf("\n");
        printf("   Compre bairros, cobre aluguel e arruíne\n");
        printf("   seus amigos. Qualquer semelhança com o\n");
        printf("   Banco Imobiliário é mera coincidência.\n");
        printf("\n");
        printf("---------------------------------------------------\n");
        printf("   1 - Jogar\n");
        printf("   2 - Como jogar\n");
        printf("   3 - Sobre o jogo\n");
        printf("   4 - Sair\n");
        printf("---------------------------------------------------\n");
        printf("\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcaoMenu);
        getchar();

        if (opcaoMenu == 1) {
            for (p = 0; p < 4; p++) {
                posicao[p] = 0;
                saldo[p] = 4000;
                ativo[p] = 1;
            }
            for (p = 0; p < 40; p++) {
                nivelConstrucao[p] = 0;
                dono[p] = -1;
            }
            jogadorAtual = 0;
            duplasConsecutivas = 0;
            rodando = 1;

            while (rodando == 1) {
                system("cls");

                printf("===================================================\n");
                printf("      BANCO IMOBILIÁRIO RJ - MONITORIA PROG 1\n");
                printf("===================================================\n");
                printf("Peça 1 = \033[1;31mVermelho\033[0m   Peça 2 = \033[1;34mAzul\033[0m   Peça 3 = \033[1;32mVerde\033[0m   Peça 4 = \033[1;33mAmarelo\033[0m\n");
                printf("Nível de construção: N0 (vazio) até N5 (hotel)\n");
                printf("\n");

                for (linha = 0; linha <= 10; linha++) {
                    for (r = 0; r < 4; r++) {
                        for (coluna = 0; coluna <= 10; coluna++) {
                            pos = tabuleiroPos[linha][coluna];

                            if (pos == -1) {
                                printf("         ");
                            } else if (r == 0 || r == 3) {
                                printf("+-------+");
                            } else if (r == 1) {
                                printf("|%2d  ", pos);
                                if (dono[pos] == -1) {
                                    printf("N%d", nivelConstrucao[pos]);
                                } else if (dono[pos] == 0) {
                                    printf("\033[1;31mN%d\033[0m", nivelConstrucao[pos]);
                                } else if (dono[pos] == 1) {
                                    printf("\033[1;34mN%d\033[0m", nivelConstrucao[pos]);
                                } else if (dono[pos] == 2) {
                                    printf("\033[1;32mN%d\033[0m", nivelConstrucao[pos]);
                                } else {
                                    printf("\033[1;33mN%d\033[0m", nivelConstrucao[pos]);
                                }
                                printf(" |");
                            } else {
                                printf("|");
                                for (p = 0; p < 4; p++) {
                                    if (p > 0) {
                                        printf(" ");
                                    }
                                    if (posicao[p] == pos) {
                                        if (p == 0) {
                                            printf("\033[1;31m%d\033[0m", p + 1);
                                        } else if (p == 1) {
                                            printf("\033[1;34m%d\033[0m", p + 1);
                                        } else if (p == 2) {
                                            printf("\033[1;32m%d\033[0m", p + 1);
                                        } else {
                                            printf("\033[1;33m%d\033[0m", p + 1);
                                        }
                                    } else {
                                        printf(".");
                                    }
                                }
                                printf("|");
                            }
                        }
                        printf("\n");
                    }
                }

                printf("\n");
                printf("---------------------------------------------------\n");

                for (p = 0; p < 4; p++) {
                    if (p == 0) {
                        printf("\033[1;31m");
                    } else if (p == 1) {
                        printf("\033[1;34m");
                    } else if (p == 2) {
                        printf("\033[1;32m");
                    } else {
                        printf("\033[1;33m");
                    }
                    if (ativo[p] == 1) {
                        printf("Jogador %d (peça %d) - %s - Saldo: R$ %d\033[0m\n", p + 1, p + 1, nomeCasas[posicao[p]], saldo[p]);
                    } else {
                        printf("Jogador %d (peça %d) - FALIDO\033[0m\n", p + 1, p + 1);
                    }
                }

                printf("---------------------------------------------------\n");
                printf("Vez do Jogador %d\n", jogadorAtual + 1);
                printf("\n");
                printf("1 - Jogar os dados\n");
                printf("2 - Fechar o jogo e voltar ao menu principal\n");
                printf("\n");
                printf("Escolha uma opção: ");
                scanf("%d", &opcaoJogo);
                getchar();

                if (opcaoJogo == 1) {
                    dado1 = rand() % 6 + 1;
                    dado2 = rand() % 6 + 1;
                    total = dado1 + dado2;
                    indoParaPrisao = 0;
                    faliu = 0;
                    foiAssaltado = 0;
                    foiBonusInicio = 0;
                    foiCasaPrisao = 0;
                    foiTresDuplas = 0;

                    if (dado1 == dado2) {
                        duplasConsecutivas = duplasConsecutivas + 1;
                    }

                    if (duplasConsecutivas == 3) {
                        foiTresDuplas = 1;
                        posicao[jogadorAtual] = 10;
                        novaPosicao = 10;
                        indoParaPrisao = 1;
                    } else {
                        posicaoAntiga = posicao[jogadorAtual];
                        landedPosicao = (posicaoAntiga + total) % 40;
                        posicao[jogadorAtual] = landedPosicao;
                        novaPosicao = landedPosicao;

                        if (posicaoAntiga + total >= 40) {
                            saldo[jogadorAtual] = saldo[jogadorAtual] + bonusInicio;
                            foiBonusInicio = 1;
                        }

                        if (landedPosicao == 35 && saldo[jogadorAtual] > 0 && rand() % 100 < 10) {
                            foiAssaltado = 1;
                            if (saldo[jogadorAtual] >= valorAssalto) {
                                perdaAssalto = valorAssalto;
                            } else {
                                perdaAssalto = saldo[jogadorAtual];
                            }
                            saldo[jogadorAtual] = saldo[jogadorAtual] - perdaAssalto;
                        }

                        if (landedPosicao == 30) {
                            foiCasaPrisao = 1;
                            posicao[jogadorAtual] = 10;
                            novaPosicao = 10;
                            indoParaPrisao = 1;
                        }
                    }

                    system("cls");

                    printf("===================================================\n");
                    printf("      BANCO IMOBILIÁRIO RJ - MONITORIA PROG 1\n");
                    printf("===================================================\n");
                    printf("Peça 1 = \033[1;31mVermelho\033[0m   Peça 2 = \033[1;34mAzul\033[0m   Peça 3 = \033[1;32mVerde\033[0m   Peça 4 = \033[1;33mAmarelo\033[0m\n");
                    printf("Nível de construção: N0 (vazio) até N5 (hotel)\n");
                    printf("\n");

                    for (linha = 0; linha <= 10; linha++) {
                        for (r = 0; r < 4; r++) {
                            for (coluna = 0; coluna <= 10; coluna++) {
                                pos = tabuleiroPos[linha][coluna];

                                if (pos == -1) {
                                    printf("         ");
                                } else if (r == 0 || r == 3) {
                                    printf("+-------+");
                                } else if (r == 1) {
                                    printf("|%2d  ", pos);
                                    if (dono[pos] == -1) {
                                        printf("N%d", nivelConstrucao[pos]);
                                    } else if (dono[pos] == 0) {
                                        printf("\033[1;31mN%d\033[0m", nivelConstrucao[pos]);
                                    } else if (dono[pos] == 1) {
                                        printf("\033[1;34mN%d\033[0m", nivelConstrucao[pos]);
                                    } else if (dono[pos] == 2) {
                                        printf("\033[1;32mN%d\033[0m", nivelConstrucao[pos]);
                                    } else {
                                        printf("\033[1;33mN%d\033[0m", nivelConstrucao[pos]);
                                    }
                                    printf(" |");
                                } else {
                                    printf("|");
                                    for (p = 0; p < 4; p++) {
                                        if (p > 0) {
                                            printf(" ");
                                        }
                                        if (posicao[p] == pos) {
                                            if (p == 0) {
                                                printf("\033[1;31m%d\033[0m", p + 1);
                                            } else if (p == 1) {
                                                printf("\033[1;34m%d\033[0m", p + 1);
                                            } else if (p == 2) {
                                                printf("\033[1;32m%d\033[0m", p + 1);
                                            } else {
                                                printf("\033[1;33m%d\033[0m", p + 1);
                                            }
                                        } else {
                                            printf(".");
                                        }
                                    }
                                    printf("|");
                                }
                            }
                            printf("\n");
                        }
                    }

                    printf("\n");
                    printf("---------------------------------------------------\n");

                    for (p = 0; p < 4; p++) {
                        if (p == 0) {
                            printf("\033[1;31m");
                        } else if (p == 1) {
                            printf("\033[1;34m");
                        } else if (p == 2) {
                            printf("\033[1;32m");
                        } else {
                            printf("\033[1;33m");
                        }
                        if (ativo[p] == 1) {
                            printf("Jogador %d (peça %d) - %s - Saldo: R$ %d\033[0m\n", p + 1, p + 1, nomeCasas[posicao[p]], saldo[p]);
                        } else {
                            printf("Jogador %d (peça %d) - FALIDO\033[0m\n", p + 1, p + 1);
                        }
                    }

                    printf("---------------------------------------------------\n");
                    printf("\n");
                    printf("Jogador %d tirou %d e %d (total %d)\n", jogadorAtual + 1, dado1, dado2, total);

                    if (foiTresDuplas == 1) {
                        printf("Três duplas seguidas! Foi direto para a prisão.\n");
                    } else {
                        printf("Nova posição: %s\n", nomeCasas[landedPosicao]);

                        if (foiAssaltado == 1) {
                            printf("Você parou na Penha e foi assaltado na favela do Quitungo! Perdeu R$ %d.\n", perdaAssalto);
                        }

                        if (foiBonusInicio == 1) {
                            printf("Passou pelo INÍCIO! Ganhou R$ %d\n", bonusInicio);
                        }

                        if (foiCasaPrisao == 1) {
                            printf("Caiu em VÁ PARA A PRISÃO! Foi enviado para a prisão.\n");
                        } else if (precoCasas[novaPosicao] > 0) {
                            if (dono[novaPosicao] == -1) {
                                printf("\n");
                                printf("Propriedade livre! Preço: R$ %d - Aluguel: R$ %d\n", precoCasas[novaPosicao], aluguelCasas[novaPosicao]);

                                if (saldo[jogadorAtual] >= precoCasas[novaPosicao]) {
                                    printf("1 - Comprar\n");
                                    printf("2 - Não comprar\n");
                                    printf("Escolha uma opção: ");
                                    scanf("%d", &opcaoCompra);
                                    getchar();

                                    if (opcaoCompra == 1) {
                                        saldo[jogadorAtual] = saldo[jogadorAtual] - precoCasas[novaPosicao];
                                        dono[novaPosicao] = jogadorAtual;
                                        printf("Jogador %d comprou %s!\n", jogadorAtual + 1, nomeCasas[novaPosicao]);
                                    }
                                } else {
                                    printf("Saldo insuficiente para comprar esta propriedade.\n");
                                }
                            } else if (dono[novaPosicao] != jogadorAtual) {
                                printf("\n");
                                printf("Propriedade do Jogador %d! Aluguel: R$ %d\n", dono[novaPosicao] + 1, aluguelCasas[novaPosicao]);

                                if (saldo[jogadorAtual] >= aluguelCasas[novaPosicao]) {
                                    saldo[jogadorAtual] = saldo[jogadorAtual] - aluguelCasas[novaPosicao];
                                    saldo[dono[novaPosicao]] = saldo[dono[novaPosicao]] + aluguelCasas[novaPosicao];
                                    printf("Você pagou R$ %d de aluguel.\n", aluguelCasas[novaPosicao]);
                                } else {
                                    saldo[dono[novaPosicao]] = saldo[dono[novaPosicao]] + saldo[jogadorAtual];
                                    saldo[jogadorAtual] = 0;
                                    printf("Você não tem dinheiro para pagar o aluguel e faliu!\n");
                                    printf("O que restava do seu saldo foi para o Jogador %d.\n", dono[novaPosicao] + 1);

                                    faliu = 1;
                                    ativo[jogadorAtual] = 0;
                                    posicao[jogadorAtual] = -1;
                                    for (p = 0; p < 40; p++) {
                                        if (dono[p] == jogadorAtual) {
                                            dono[p] = -1;
                                            nivelConstrucao[p] = 0;
                                        }
                                    }
                                    printf("Suas propriedades voltaram para o banco.\n");
                                }
                            } else {
                                printf("\n");
                                printf("Você já é dono desta propriedade.\n");
                            }
                        }
                    }

                    if (faliu == 0 && indoParaPrisao == 0 && dado1 == dado2) {
                        printf("\n");
                        printf("Tirou dupla! Jogue novamente.\n");
                    }

                    printf("\n");
                    printf("Pressione ENTER para continuar...");
                    getchar();

                    ativosRestantes = 0;
                    for (p = 0; p < 4; p++) {
                        if (ativo[p] == 1) {
                            ativosRestantes = ativosRestantes + 1;
                            vencedor = p;
                        }
                    }

                    if (ativosRestantes == 1) {
                        system("cls");
                        printf("===================================================\n");
                        printf("                   FIM DE JOGO\n");
                        printf("===================================================\n");
                        printf("\n");
                        if (vencedor == 0) {
                            printf("\033[1;31m");
                        } else if (vencedor == 1) {
                            printf("\033[1;34m");
                        } else if (vencedor == 2) {
                            printf("\033[1;32m");
                        } else {
                            printf("\033[1;33m");
                        }
                        printf("   O Jogador %d (peça %d) venceu a partida!\033[0m\n", vencedor + 1, vencedor + 1);
                        printf("   Saldo final: R$ %d\n", saldo[vencedor]);
                        printf("\n");
                        printf("   Todos os outros jogadores faliram.\n");
                        printf("\n");
                        printf("Pressione ENTER para voltar ao menu...");
                        getchar();
                        rodando = 0;
                    } else if (faliu == 1 || indoParaPrisao == 1 || dado1 != dado2) {
                        jogadorAtual = (jogadorAtual + 1) % 4;
                        while (ativo[jogadorAtual] == 0) {
                            jogadorAtual = (jogadorAtual + 1) % 4;
                        }
                        duplasConsecutivas = 0;
                    }
                } else if (opcaoJogo == 2) {
                    rodando = 0;
                } else {
                    printf("\n");
                    printf("Opção inválida! Pressione ENTER para tentar de novo...");
                    getchar();
                }
            }
        } else if (opcaoMenu == 2) {
            system("cls");
            printf("===================================================\n");
            printf("   COMO JOGAR\n");
            printf("===================================================\n");
            printf("\n");
            printf("O tabuleiro tem 40 casas numeradas, no mesmo formato\n");
            printf("do Monopoly, passando por Rio das Ostras, Itaboraí,\n");
            printf("Itaperuna, Duque de Caxias e outros lugares do Rio.\n");
            printf("\n");
            printf("São 4 jogadores (peças 1, 2, 3 e 4), cada um com\n");
            printf("uma cor: vermelho, azul, verde e amarelo. Cada um\n");
            printf("começa com R$ 4000 e na casa INÍCIO. Na sua vez, o\n");
            printf("jogador joga dois dados e avança pelo tabuleiro de\n");
            printf("acordo com a soma tirada.\n");
            printf("\n");
            printf("Toda vez que um jogador passa ou cai no INÍCIO,\n");
            printf("recebe um bônus em dinheiro. Cada casa também mostra\n");
            printf("seu nível de construção (N0 a N5).\n");
            printf("\n");
            printf("Casas mais próximas do fim do tabuleiro custam mais\n");
            printf("caro e têm aluguéis mais altos, assim como no jogo\n");
            printf("original. Ao cair numa propriedade livre, o jogador\n");
            printf("pode comprá-la. Ao cair numa propriedade de outro\n");
            printf("jogador, paga aluguel a ele automaticamente.\n");
            printf("\n");
            printf("Se tirar dupla nos dados, o jogador joga de novo.\n");
            printf("Mas cuidado: três duplas seguidas mandam ele direto\n");
            printf("para a prisão. Cair na casa \"VÁ PARA A PRISÃO\"\n");
            printf("também manda para lá na hora, sem passar pelo\n");
            printf("INÍCIO (ou seja, sem ganhar o bônus).\n");
            printf("\n");
            printf("Quem não tiver dinheiro para pagar um aluguel vai à\n");
            printf("falência: sai da partida e suas propriedades voltam\n");
            printf("para o banco. Vence o último jogador que restar.\n");
            printf("\n");
            printf("A qualquer momento é possível fechar a partida e\n");
            printf("voltar ao menu principal.\n");
            printf("\n");
            printf("Pressione ENTER para voltar ao menu...");
            getchar();
        } else if (opcaoMenu == 3) {
            system("cls");
            printf("===================================================\n");
            printf("   SOBRE O JOGO\n");
            printf("===================================================\n");
            printf("\n");
            printf("Jogo desenvolvido para a matéria de Programação 1\n");
            printf("do curso de Ciência da Computação, com tema baseado\n");
            printf("em locais do Rio de Janeiro.\n");
            printf("\n");
            printf("Pressione ENTER para voltar ao menu...");
            getchar();
        } else if (opcaoMenu == 4) {
            system("cls");
            printf("Obrigado por jogar! Até a próxima.\n");
            continuarMenu = 0;
        } else {
            printf("\n");
            printf("Opção inválida! Pressione ENTER para tentar de novo...");
            getchar();
        }
    }

    return 0;
}
