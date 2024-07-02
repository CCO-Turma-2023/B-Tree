//
// Created by tiago on 29/06/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "Btree/btree.h"
#include "CriarIndice.h"

int getTamanhoNome (FILE *arq)
{
    int tamanhoNome = 0;
    char c;
    fscanf(arq, "%c", &c);
    while (c < 0x40 && c >= 0x30){
        fscanf(arq, "%c", &c);
    }
    fscanf(arq, "%c", &c);
    while (!(c < 0x40 && c >= 0x30)){
        fscanf(arq, "%c", &c);
        tamanhoNome++;
    }
    return tamanhoNome;
}

Btree *CriarIndice(char *nomeArq){
    int ordem, matricula, indice = 1, idade, periodo, tamanhoNome;
    char *nome, c;
    FILE *arq;
    arq = fopen(nomeArq, "r");
    tamanhoNome = getTamanhoNome(arq);
    nome = (char*)malloc(sizeof(char)*(tamanhoNome));
    Btree *arvore;
    chave key;
    if(!arq){
        printf("Arquivo nao existe\n");
        return NULL;
    }
    printf ("\nDigite a ordem da arvore(Obs. Somente numeros pares e maior ou igual a 6):");
    scanf ("%d", &ordem);
    if (ordem%2 || ordem < 5 || ordem > 300){
        printf ("Numero invalido\n");
        return NULL;
    }
    arvore = criarArvore(ordem);
    if(!arvore)
        return NULL;
    rewind(arq);
    while (!feof(arq)) {
        fscanf (arq, "%d ", &matricula);
        fgets(nome, tamanhoNome, arq);
        fscanf(arq, "%d %d", &idade, &periodo);
        key.valor = matricula;
        key.indice = indice;
        if (!insereChave(arvore, key)){
            printf("Não foi possivel inserir chave de valor %d\n",key.valor);
            return NULL;
        }
        indice++;
    }
    return arvore;
}