//
// Created by tiago on 29/06/2024.
//
#include <stdio.h>
#include "Btree/btree.h"
#include "CriarIndice.h"

Btree *CriarIndice(char *nomeArq){
    int ordem, matricula, indice = 1;
    char nome[15];
    Btree *arvore;
    chave key;
    FILE *arq;
    arq = fopen(nomeArq, "r");
    if(!arq){
        printf("Arquivo nao existe\n");
        return NULL;
    }
    printf ("\nDigite a ordem da arvore(Obs. Somente numeros pares e maior ou igual a 6):");
    scanf ("%d", &ordem);
    if (ordem%2 || ordem < 5){
        printf ("Numero invalido\n");
        return NULL;
    }
    arvore = criarArvore(ordem);
    if(!arvore)
        return NULL;
    while (!feof(arq)) {
        fscanf(arq, "%d %[^\n]", &matricula, nome);
        key.valor = matricula % 10000;
        key.indice = indice;
        if (!insereChave(arvore, key)){
            printf("Não foi possivel inserir chave de valor %d\n",key.valor);
            return NULL;
        }
        indice++;
    }
    return arvore;
}