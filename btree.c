#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

struct no {
    int *chaves; // Array de chaves
    struct no **filhos;
    int n; // Número atual de chaves
    int folha; // 1 = nó é folha. 0 caso contrário.
    struct no *pai; // Pai do nó
};

struct Btree {
    struct no *raiz;
    int ordem;
};


no* alocaNo(int ordem) {
    no *novo_no = (no*)malloc(sizeof(no));

    // Erro de alocar nó
    if(!novo_no) {
        printf ("Erro ao alocar o no.\n");
        return NULL;
    }

    // Alocando espaço para as chaves --> Ímpar = ordem, par = ordem -1
    if(ordem % 2) {
        novo_no->chaves = (int *) malloc(sizeof(int) * ordem);
    } else {
        novo_no->chaves = (int *) malloc(sizeof(int) * ordem - 1);
    }

    // Erro de alocar chaves
    if(!novo_no->chaves) {
            printf("Erro ao alocar o vetor de chaves.\n");
            free(novo_no);
            return NULL;
    }

    // Alocando espaço para os filhos
    novo_no->filhos = (no**) malloc(sizeof(no*) * ordem);
    if(!novo_no->filhos) {
        printf ("Erro ao alocar os filhos do nó.\n");
        free(novo_no);
        return NULL;
    }

    // Inicializando nós filhos
    for(int i = 0; i < ordem; i++) {
        novo_no->filhos[i] = NULL;
    }

    novo_no->folha = 1;
    novo_no->n = 0;
    novo_no->pai = NULL;

    return novo_no;
}

Btree* criarArvore(int ordem) {
    Btree *arv = (Btree*)malloc(sizeof(Btree));

    if (!arv) {
        printf ("Erro ao alocar a árvore.\n");
        return NULL;
    }

    arv->ordem = ordem;
    arv->raiz = alocaNo(ordem);

    return arv;
}

void split (Btree *arv, no* aux, int valor){
    return;
}

int insereChave(Btree *arv, int valor) {
    no *aux = arv->raiz;
    int indice;

    // Achando o no onde será inserido o valor
    while (!aux->folha){
        indice = 0;
        while (valor > aux->chaves[indice] && indice < aux->n){
            indice++;
        }
        aux = aux->filhos[indice];
    }

    // Achando onde a chave será inserida no nó
    if (aux->n != arv->ordem - 1){
        indice = aux->n;
        // Procurando da última posição ocupada para achar o local para inserir a chave
        while (indice > 0 && valor < aux->chaves[indice]){
            indice--;
            aux->chaves[indice] = aux->chaves[indice-1];
        }
        aux->chaves[indice] = valor;
    } else {
        split(arv, aux, valor);
    }
    return 1;
}

