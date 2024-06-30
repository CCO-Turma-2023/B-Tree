//
// Created by tiago on 30/06/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BuscaDireta.h"

void BuscaDireta(char *nomeArq){
    int matricula,valor, qtd;
    char nome[15];
    double tempo;
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
    printf("Busca direta no arquivo:\n");
    for(int i = 0;i < qtd; i++){
        rewind(arq);
        valor = rand() % 10000;
        printf("%d - ",valor);
        inicio = clock();
        while (!feof(arq) && matricula % 10000 != valor)
            fscanf(arq, "%d %[^\n]", &matricula, nome);
        if (feof(arq))
            printf("Nao encontrado - ");
        else{
            printf("%d - %s - ", matricula, nome);
        }
        fim = clock();
        tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("Tempo gasto: %lf\n",tempo);
    }
    fclose(arq);
}
