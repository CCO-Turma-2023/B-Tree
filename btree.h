#ifndef BTREE_BTREE_H
#define BTREE_BTREE_H

typedef struct no no;
typedef struct Btree Btree;

Btree* criarArvore(int ordem);
no* alocaNo(int ordem);
int insereChave(Btree *arv, int valor);

#endif
