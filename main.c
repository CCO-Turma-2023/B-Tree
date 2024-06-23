#include <stdio.h>
#include "btree.h"

int main() {
    int ordem = 4;
    Btree *arvore = criarArvore(ordem);

    for (int i = 0; i < 15; i++) {
        insereChave(arvore, i);
    }

    imprimirArvore(getRaiz(arvore), 0);
    //  **          **                          ********
    //    **      **                                    *
    //      **  **           ***********                *
    //        **                                        *
    //      **  **           ***********                *
    //    **      **                                    *
    //  **          **                          **
    return 0;
}