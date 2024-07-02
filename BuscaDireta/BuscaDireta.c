//
// Created by tiago on 30/06/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CriarIndice/CriarIndice.h"
#include "BuscaDireta.h"
#include "BuscaBtree/BuscaBtree.h"

void BuscaDireta(char *nomeArq){
    int matricula,valor, qtd, tamanhoNome, idade, periodo;
    char *nome;
    double tempo, tempoTotal = 0;
    clock_t inicio, fim;
    srand(time(NULL));
    FILE *arq;
    arq = fopen(nomeArq, "r");
    if (!arq){
        printf("Arquivo nao existe\n");
        return;
    }
    tamanhoNome = getTamanhoNome(arq);
    printf("Digite a quantidade de buscas:");
    scanf("%d", &qtd);
    printf("Busca direta no arquivo:\n");
    for(int i = 0;i < qtd; i++){
        rewind(arq);
        valor = 2023000000 + rand() % 15000;
        printf("%d - ",valor);
        inicio = clock();
        while (!feof(arq) && matricula != valor) {
            fscanf (arq, "%d ", &matricula);
            fgets(nome, tamanhoNome, arq);
            fscanf(arq, "%d %d", &idade, &periodo);
        }
        if (feof(arq))
            printf("Nao encontrado - ");
        else{
            printf("%d - %s - %d - %d ", matricula, nome, idade, periodo);
        }
        fim = clock();
        tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("Tempo gasto: %lf\n",tempo);
        tempoTotal += tempo;
    }
    printf ("Tempo médio gasto foi: %lf\n", tempoTotal/qtd);
    fclose(arq);
}
