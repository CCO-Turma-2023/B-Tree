//
// Created by tiago on 29/06/2024.
//
#include <stdio.h>
#include "Btree/btree.h"
#include "ProcurarElemento.h"
#include "BuscaBtree/BuscaBtree.h"
#include "BuscaDireta/BuscaDireta.h"

void ProcurarElementos(Btree *arv,char *nomeArq){
    int escolha;
    if(arv){
        printf("Menu:\n1-Busca B-Tree\n2-Busca Direta\n");
        scanf("%d", &escolha);
        switch(escolha){
            case 1:
                BuscaBtree(arv,nomeArq);
                break;
            case 2:
                BuscaDireta(nomeArq);
                break;
            default:
                printf("Invalido\n");
        }
    }else{
        printf("Arvore Invalida\n");
    }
}