#include <stdio.h>
#include "btree.h"

int main() {
    int ordem = 4;
    Btree *arvore = criarArvore(ordem);
    chave aux;

    for (int i = 0; i < 10; i++) {
        aux.valor = i;
        aux.indice = 9998765;
        insereChave(arvore, aux);
    }
    imprimirArvore(getRaiz(arvore));
    return 0;
}