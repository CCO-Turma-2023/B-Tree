#include <stdio.h>
#include <stdlib.h>
#include "btree.h"



no * alocaNo(int ordem) {
    no *novo_no = (no*)malloc(sizeof(no));

    // Erro de alocar nó
    if(!novo_no) {
        printf ("Erro ao alocar o no.\n");
        return NULL;
    }

    // Alocando espaço para as chaves --> Ímpar = ordem, par = ordem -1
    novo_no->chaves = (chave*)malloc(sizeof(chave) * (ordem - 1));

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

no* split(Btree *arv, no *aux, chave chaveNova){
    // Alocando um novo nó para dividir o nó aux
    no *novoNo = alocaNo(arv->ordem), *pai;
    int indice;
    // Verifica se o nó foi alocado com sucesso
    if (!novoNo){
        return NULL;
    }

    for (int i = 1; i < arv->ordem/2; i++){
        novoNo->chaves[i-1].valor = aux->chaves[i+((arv->ordem/2) - 1)].valor;
        novoNo->chaves[i-1].indice = aux->chaves[i+((arv->ordem/2) - 1)].indice;
        novoNo->filhos[i-1] = aux->filhos[i+((arv->ordem/2) - 1)];
        if (novoNo->filhos[i-1]) {
            novoNo->filhos[i-1]->pai = novoNo;
        }
        novoNo->n++;
        aux->n--;
    }

    if (aux == arv->raiz){
        no *novaRaiz = alocaNo(arv->ordem);
        if (!novaRaiz){
            return NULL;
        }
        aux->n--;
        novaRaiz->chaves[0] = aux->chaves[aux->n];
        novaRaiz->n = 1;
        novaRaiz->filhos[0] = aux;
        novaRaiz->filhos[1] = novoNo;
        novaRaiz->folha = 0;
        aux->pai = novoNo->pai = novaRaiz;
        arv->raiz = novaRaiz;
    } else {
        if (aux->pai->n == arv->ordem - 1){
            chave chaveAux = aux->chaves[aux->n/2];
            pai = split(arv, aux->pai, aux->chaves[aux->n/2]);
            if (chaveAux.valor < chaveNova.valor) {
                pai = aux->pai;
            }
            indice = pai->n;
            while (indice != 0 && chaveNova.valor != pai->chaves[indice].valor) {;
                indice--;
            }
            novoNo->pai = pai;
            pai->filhos[indice + 1] = novoNo;
        } else {
            pai = aux->pai;
            indice = pai->n;
            while (indice != 0 && chaveNova.valor < pai->chaves[indice - 1].valor) {
                pai->chaves[indice].valor = pai->chaves[indice - 1].valor;
                indice--;
            }
            pai->chaves[indice] = aux->chaves[(arv->ordem-1)/2];
            novoNo->pai = aux->pai;
            pai->filhos[indice + 1] = novoNo;
            pai->n++;
            aux->n--;
        }
    }

    indice = novoNo->n;
    while (indice != 0 && chaveNova.valor < novoNo->chaves[indice - 1].valor) {
        novoNo->chaves[indice].valor = novoNo->chaves[indice - 1].valor;
        indice--;
    }
    novoNo->chaves[indice] = chaveNova;
    novoNo->n++;
    return novoNo;
}

int insereChave(Btree *arv, chave novaChave) {
    no *aux = arv->raiz;
    int indice;

    // Achando o nó folha onde será inserido o valor
    while (!aux->folha){
        indice = 0;
        while (novaChave.valor > aux->chaves[indice].valor && indice < aux->n) {
            indice++;
        }
        aux = aux->filhos[indice];
    }

    // Achando onde a chave será inserida no nó
    if (aux->n != arv->ordem - 1) {
        indice = aux->n;
        // Procurando da última posição ocupada para achar o local para inserir a chave
        while (indice != 0 && novaChave.valor < aux->chaves[indice - 1].valor) {
            aux->chaves[indice].valor = aux->chaves[indice-1].valor;
            indice--;
        }
        aux->n++;
        aux->chaves[indice] = novaChave;
    } else {
        split(arv, aux, novaChave);
    }
    return 1;
}

no* getRaiz (Btree *arv){
    return arv->raiz;
}

void imprimirArvore(no *aux){
    if (aux){
        for (int i = 0; i < aux->n; i++) {
            printf("%d ", aux->chaves[i].valor);
        }
        printf ("\n");
        for (int i = 0; i < aux->n + 1; i++){
            imprimirArvore(aux->filhos[i]);
        }
    }
    return;
}
