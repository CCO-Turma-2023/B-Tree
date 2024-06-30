//
// Created by tiago on 30/06/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BuscaBtree.h"

void BuscaBtree(Btree *arv,char *nomeArq){
    int valor,indiceArq, matricula, qtd, n;
    char nome[15];
    double tempo, tempoTotal = 0;
    clock_t inicio, fim;
    srand(time(NULL));
    FILE *arq;
    arq = fopen(nomeArq, "r");
    if (!arq){
        printf("Arquivo nao existe\n");
        return;
    }
    printf("Digite a quantidade de buscas:");
    scanf("%d", &qtd);
    printf("Busca pela Btree:\n");
    n = getNumElementos(arv);
    for (int i =0; i<qtd;i++){
        valor = rand() % n;
        printf("%d - ",valor);
        inicio = clock();
        indiceArq = busca(getRaiz(arv),valor);
        if(indiceArq){
            fseek(arq, (indiceArq-1) *27, SEEK_SET);
            fscanf(arq, "%d %[^\n]", &matricula, nome);
            printf("%d - %s - ", matricula, nome);
        }else{
            printf("Nao encontrado - ");
        }
        fim = clock();
        tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("Tempo gasto: %lf\n",tempo);
        tempoTotal += tempo;
    }
    printf ("Tempo médio gasto foi: %lf\n", tempoTotal/qtd);
    fclose(arq);
}