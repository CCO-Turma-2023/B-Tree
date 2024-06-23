#ifndef BTREE_BTREE_H
#define BTREE_BTREE_H

typedef struct no no;
typedef struct Btree Btree;

Btree* criarArvore(int ordem);
no* alocaNo(int ordem);
int insereChave(Btree *arv, int valor);
void split (Btree *arv, no* aux, int valor);
void imprimirArvore (no *node, int nivel);
no* getRaiz(Btree *arv);

#endif
