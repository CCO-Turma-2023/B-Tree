//
// Created by tiago on 30/06/2024.
//
#include <stdio.h>
#include "Btree/btree.h"
#include "RemoverElemento.h"

void RemoverRegistro(Btree *arv){
    int qtd, elem, escolha;
    FILE *arq;
    char nomeArq[30];
    if(arv) {
        printf("Menu:\n1-Digitar\n2-Arquivo\n");
        scanf("%d", &escolha);
        switch (escolha) {
            case 1:
                printf("Digite a quantidade de valores a serem removidos:");
                scanf("%d", &qtd);
                for (int i = 0; i < qtd; i++) {
                    printf("Digite o elemento:");
                    scanf("%d", &elem);
                    if (removeChave(arv, elem))
                        printf("Removido\n");
                }
                break;
            case 2:
                printf("Digite o nome do arquivo que contem os valores de remocao:");
                scanf("%s", nomeArq);
                arq = fopen(nomeArq, "r");
                if (!arq) {
                    printf("Arquivo nao existe\n");
                    return;
                }
                while (!feof(arq)) {
                    fscanf(arq, "%d", &elem);
                    if (removeChave(arv, elem))
                        printf("Removido\n");
                }
                break;
            default:
                printf("Invalido\n");
            }
    }else{
        printf("Arvore invalida\n");
    }
}