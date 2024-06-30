//
// Created by tiago on 29/06/2024.
//
#include <stdio.h>
#include "Btree/btree.h"
#include "Menu.h"
#include "CriarIndice/CriarIndice.h"
#include "ProcurarElementos/ProcurarElemento.h"
#include "Remover Elemento/RemoverElemento.h"

void menu(){
    int escolha;
    char nomeArq[30];
    Btree *arv;
    do{
        printf("Menu:\n1-Criar Indice\n2-Procurar elementos\n3-Remover elemento\n4-Sair\n");
        scanf("%d",&escolha);
        switch (escolha) {
            case 1:
                printf("Digite o nome do arquivo a partir do qual sera criado a B-Tree:");
                scanf("%s",nomeArq);
                arv = CriarIndice(nomeArq);
                if(arv)
                    printf("Arvore criada\n");
                break;
            case 2:
                ProcurarElementos(arv,nomeArq);
                break;
            case 3:
                RemoverRegistro(arv);
                break;
            case 4:
                break;
            default:
                printf("Invalido\n");
        }
    } while (escolha !=4);

}