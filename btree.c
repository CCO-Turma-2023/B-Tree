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
    int indice, i;
    chave meio;
    if (chaveNova.valor == 44)
        printf ("oi");
    // Verifica se o nó foi alocado com sucesso
    if (!novoNo){
        return NULL;
    }
    novoNo->folha = aux->folha;
    for (i = 1; i < arv->ordem/2; i++){
        novoNo->chaves[i-1] = aux->chaves[i+((arv->ordem/2) - 1)];
        novoNo->filhos[i-1] = aux->filhos[i+((arv->ordem/2) - 1)];
        novoNo->filhos[i] = aux->filhos[(i + 1)+((arv->ordem/2) - 1)];
        if (novoNo->filhos[i-1]) {
            novoNo->filhos[i-1]->pai = novoNo;
            novoNo->filhos[i]->pai = novoNo;
        }
        novoNo->n++;
        aux->n--;
    }
    meio = aux->chaves[aux->n - 1];
    if (aux == arv->raiz){
        no *novaRaiz = alocaNo(arv->ordem);
        if (!novaRaiz){
            return NULL;
        }
        aux->n--;
        novaRaiz->chaves[0] = meio;
        novaRaiz->n = 1;
        novaRaiz->filhos[0] = aux;
        novaRaiz->filhos[1] = novoNo;
        novaRaiz->folha = 0;
        aux->pai = novoNo->pai = novaRaiz;
        arv->raiz = novaRaiz;
    } else {
        if (aux->pai->n == arv->ordem - 1){
            pai = split(arv, aux->pai, meio);
            if (meio.valor < pai->chaves[0].valor) {
                pai = aux->pai;
            }
            aux->n--;
            indice = pai->n;
            while (indice != 0 && meio.valor != pai->chaves[indice].valor) {
                indice--;
            }
            novoNo->pai = pai;
            pai->filhos[indice + 1] = novoNo;
        } else {
            pai = aux->pai;
            indice = pai->n;
            while (indice != 0 && chaveNova.valor < pai->chaves[indice - 1].valor) {
                pai->chaves[indice] = pai->chaves[indice - 1];
                pai->filhos[indice + 1] = pai->filhos[indice];
                indice--;
            }
            pai->chaves[indice] = meio;
            novoNo->pai = aux->pai;
            pai->filhos[indice + 1] = novoNo;
            pai->n++;
            aux->n--;
        }
    }

    if (meio.valor < chaveNova.valor){
        aux = novoNo;
    }
    indice = aux->n;
    while (indice != 0 && chaveNova.valor < aux->chaves[indice - 1].valor) {
        aux->chaves[indice] = aux->chaves[indice-1];
        aux->filhos[indice+1] = aux->filhos[indice];
        indice--;
    }
    aux->chaves[indice] = chaveNova;
    aux->n++;
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
            aux->chaves[indice] = aux->chaves[indice-1];
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
        printf ("- pai: ");
        if (aux->pai)
        for (int i = 0; i < aux->pai->n; i++) {
            printf("%d ", aux->pai->chaves[i].valor);
        }
        printf ("\n");
        if (aux->filhos[0])
            printf ("filhos: ");
            for (int i = 0; i < aux->n + 1; i++){
                imprimirArvore(aux->filhos[i]);
        }
    }
    return;
}

int busca (no *aux, int nroMatricula){
    int i = 0;
    // Encontre a primeira chave maior ou igual a k
    while (i < aux->n && nroMatricula > aux->chaves[i].valor)
        i++;
    // Se a chave for encontrada, retorne o nó
    if (aux->chaves[i].valor == nroMatricula)
        return aux->chaves[i].indice;

    // Se a chave não for encontrada aqui e este é um nó folha
    if (aux->folha == 1)
        return 0;

    // Vá para o filho apropriado
    return busca(aux->filhos[i], nroMatricula);
}