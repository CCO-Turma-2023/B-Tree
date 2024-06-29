#ifndef BTREE_BTREE_H
#define BTREE_BTREE_H

typedef struct{
    int valor;
    int indice;
}chave;

struct no {
    chave *chaves; // Array de chaves
    struct no **filhos;
    int n; // Número atual de chaves
    int folha; // 1 = nó é folha. 0 caso contrário.
    struct no *pai; // Pai do nó
};

struct Btree {
    struct no *raiz;
    int ordem;
};

typedef struct no no;
typedef struct Btree Btree;

Btree* criarArvore(int ordem);
no* alocaNo(int ordem);
int insereChave(Btree *arv, chave valor);
no* split (Btree *arv, no* aux, chave valor);
int removeChave(Btree *arv, chave valor);
void imprimirArvore (no *node);
no* getRaiz(Btree *arv);
int busca (no *aux, int nroMatricula);
void balanceamento (Btree *arv, no *noDesbal);
void rotacao (Btree *arv, no *noDesbal, int indiceIrmao);
no* merge(Btree *arv, no* noDesbal,int indiceNoDesbal);
void liberaNo (no *noRemovido);


#endif
