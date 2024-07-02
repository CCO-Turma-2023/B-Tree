//
// Created by tiago on 30/06/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "BuscaBtree.h"
#include "CriarIndice/CriarIndice.h"

void BuscaBtree(Btree *arv,char *nomeArq) {
    int valor = 1, indiceArq, matricula, qtd, n, idade, periodo, tamanhoNome, tamanhoRegistro, cod;
    char *nome, linha[200];
    double tempo, tempoTotal = 0;
    clock_t inicio, fim;
    srand(time(NULL));
    FILE *arq;
    arq = fopen(nomeArq, "r");
    if (!arq) {
        printf("Arquivo nao existe\n");
        return;
    }
    fgets(linha, sizeof(linha), arq);
    tamanhoRegistro = strlen(linha) + 1;
    rewind(arq);
    tamanhoNome = getTamanhoNome(arq);
    nome = (char *) malloc(sizeof(char) * (tamanhoNome));
    printf("Selecione o modo de busca.\n1 - Aleatorio\n2 - Escolher o registro.\n");
    scanf("%d", &cod);
    switch (cod) {
        case 1:
            printf("Digite a quantidade de buscas:");
            scanf("%d", &qtd);
            printf("Busca pela Btree:\n");
            n = getNumElementos(arv);
            rewind(arq);
            for (int i = 0; i < qtd; i++) {
                valor = 2023000000 + rand() % n;
                printf("%d - ", valor);
                inicio = clock();
                indiceArq = busca(getRaiz(arv), valor);
                if (indiceArq) {
                    fseek(arq, (indiceArq - 1) * (tamanhoRegistro), SEEK_SET);
                    fscanf(arq, "%d ", &matricula);
                    fgets(nome, tamanhoNome, arq);
                    fscanf(arq, "%d %d", &idade, &periodo);
                    printf("%d - %s - %d - %d ", matricula, nome, idade, periodo);
                } else {
                    printf("Nao encontrado - ");
                }
                fim = clock();
                tempo = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
                printf("Tempo gasto: %lf\n", tempo);
                tempoTotal += tempo;
            }
            printf("Tempo médio gasto foi: %lf\n", tempoTotal / qtd);
            break;
        case 2:
            printf ("Digite o valor que deseja procurar ou 0 para sair: ");
            scanf ("%d", &valor);
            while (valor != 0) {
                printf("Busca pela Btree:\n");
                n = getNumElementos(arv);
                rewind(arq);
                printf("%d - ", valor);
                inicio = clock();
                indiceArq = busca(getRaiz(arv), valor);
                if (indiceArq) {
                    fseek(arq, (indiceArq - 1) * (tamanhoRegistro), SEEK_SET);
                    fscanf(arq, "%d ", &matricula);
                    fgets(nome, tamanhoNome, arq);
                    fscanf(arq, "%d %d", &idade, &periodo);
                    printf("%d - %s - %d - %d ", matricula, nome, idade, periodo);
                } else {
                    printf("Nao encontrado - ");
                }
                fim = clock();
                tempo = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
                printf("Tempo gasto: %lf\n", tempo);
                tempoTotal += tempo;
                printf ("Digite o valor que deseja procurar ou 0 para sair: ");
                scanf ("%d", &valor);
            }
            break;
        default:
            printf ("Numero invalido.\n");
            break;
    }
    fclose(arq);
}