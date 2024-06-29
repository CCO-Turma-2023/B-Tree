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

void liberaNo (no *noRemovido){
    free(noRemovido->filhos);
    free(noRemovido->chaves);
    free(noRemovido);
    return;
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

void addChave(no *aux, chave novaChave) {
    int indice = aux->n;
    // Procurando o local certo para inserir a chave
    while (indice != 0 && novaChave.valor < aux->chaves[indice - 1].valor) {
        aux->chaves[indice] = aux->chaves[indice-1]; // Dá um shift para a direita na chave
        aux->filhos[indice+1] = aux->filhos[indice]; // Dá um shift para a direita no filho
        indice--;
    }
    aux->n++; // Aumenta o número de chaves
    aux->chaves[indice] = novaChave; // Insere a chave
}

no* split(Btree *arv, no *aux, chave chaveNova){
    // Alocando um novo nó para dividir o nó aux
    no *novoNo = alocaNo(arv->ordem); // Aloca espaço para um novo nó
    no *pai; // Prepara variável do pai
    int indice, i, tamanho = aux->n;
    chave meio;

    // Verifica se o nó foi alocado com sucesso
    if (!novoNo){
        return NULL;
    }

    novoNo->folha = aux->folha; // Define a mesma propriedade de folha no nó irmão
    indice = 0;
    for (i = (aux->n/2) +1; i < tamanho; i++){ // Copia a segunda metade do nó aux para o novo nó
        novoNo->chaves[indice] = aux->chaves[i]; // Copia a chave para o novo nó
        novoNo->filhos[indice] = aux->filhos[i]; // Copia o filho à esquerda da chave antiga pro novo nó
        novoNo->filhos[indice + 1] = aux->filhos[i + 1]; // Copia o filho à direita da chave antiga pro novo nó
        if (novoNo->filhos[indice]) { // Caso os filhos da chave que foi transferida exista
            novoNo->filhos[indice]->pai = novoNo; // Seta o pai do filho para o novo nó criado
            novoNo->filhos[indice + 1]->pai = novoNo; // Seta o pai do filho para o novo nó criado
        }
        novoNo->n++; // Aumenta o número de chaves no novo nó
        aux->n--; // Diminui o número de chaves no nó antigo
        indice ++; // Incrementa o índice
    }

    meio = aux->chaves[aux->n - 1];
    if (aux == arv->raiz){ // Se o nó que foi dividido é a raiz
        no *novaRaiz = alocaNo(arv->ordem); // Aloca uma nova raiz
        if (!novaRaiz){
            return NULL;
        }
        aux->n--; // Diminui o número de chaves no nó antigo
        novaRaiz->chaves[0] = meio; // A raiz recebe a chave do meio
        novaRaiz->n = 1; // Aumenta o número de chaves na nova raiz
        novaRaiz->filhos[0] = aux; // O filho da esquerda da nova raiz é o nó antigo
        novaRaiz->filhos[1] = novoNo; // O filho da direita da nova raiz é o novo nó
        novaRaiz->folha = 0; // A nova raiz não é folha
        aux->pai = novoNo->pai = novaRaiz; // Seta o pai dos nós
        arv->raiz = novaRaiz; // A nova raiz da árvore é a nova raiz criada
    } else {
        if (aux->pai->n == arv->ordem - 1){ // Se o pai do nó estiver cheio !!!!!!!!!!!!!
            pai = split(arv, aux->pai, meio); // Split  no pai
            if (meio.valor < pai->chaves[0].valor) { // Se a chave do meio for menor que a primeira chave do pai
                pai = aux->pai; // O pai passa a ser o pai do nó antigo
            }
            aux->n--; // Diminui o número de chaves no nó antigo
            indice = pai->n - 1; // Índice recebe o número de chaves do pai
            while (indice != 0 && meio.valor != pai->chaves[indice].valor) { // Encontra a posição correta para inserir a chave
                indice--; // Decrementa o índice
            }
            novoNo->pai = pai; // O pai do novo nó é o pai do nó antigo
            pai->filhos[indice + 1] = novoNo;
        } else { // Se o pai do nó não estiver cheio
            pai = aux->pai;
            indice = pai->n;
            while (indice != 0 && chaveNova.valor < pai->chaves[indice - 1].valor) { // Encontra a posição correta para inserir a chave
                pai->chaves[indice] = pai->chaves[indice - 1]; // Dá um shift para a direita na chave
                pai->filhos[indice + 1] = pai->filhos[indice]; // Dá um shift para a direita no filho
                indice--; // Decrementa o índice
            }
            pai->chaves[indice] = meio; // Insere o elemento do meio do aux no pai
            novoNo->pai = aux->pai; // O pai do novo nó é o pai do nó antigo
            pai->filhos[indice + 1] = novoNo; // O filho à direita da chave antiga é o novo nó
            pai->n++; // Aumenta o número de chaves no pai
            aux->n--; // Diminui o número de chaves no nó antigo
        }
    }

    if (meio.valor < chaveNova.valor){ // Se o valor inserido for maior que o meio do nó antigo
        aux = novoNo;  // Seta o aux para o novo nó
    }

    addChave(aux, chaveNova);
    return novoNo;
}



int insereChave(Btree *arv, chave novaChave) {
    no *aux = arv->raiz;
    int indice;

    // Achando o nó folha onde será inserido o valor
    while (!aux->folha) { // Enquanto não for folha
        indice = 0;
        while (indice < aux->n && novaChave.valor > aux->chaves[indice].valor) { // Encontra nó folha para inserir
            indice++;
        }
        aux = aux->filhos[indice];
    }

    // Verifica se o nó está cheio
    if (aux->n != arv->ordem - 1) { // Se não estiver cheio, chama a função addChave
        addChave(aux, novaChave);
    } else { // Se estiver cheio, chama a função split
        aux = split(arv, aux, novaChave);
    }
    if (!aux) {
        return 0;
    } else {
        return 1;
    }
}

int removeChave(Btree *arv, chave chaveRemover){
    no *aux = arv->raiz;
    no *predecessor;
    int indice = 0;

    // Achando o nó onde está o valor a ser removido
    while (aux && aux->chaves[indice].valor != chaveRemover.valor){ // Enquanto for diferente do valor a remover
        // Procura o elemento no nó ou o filho que terá que ir depois
        while (indice < aux->n && chaveRemover.valor > aux->chaves[indice].valor) {
            indice++;
        }
        // Verifica se o elemento não foi encontrado ou se chegou no final do nó
        if (indice == aux->n || aux->chaves[indice].valor != chaveRemover.valor) {
            aux = aux->filhos[indice];
            indice = 0;
        }
    }
    // Elemento não encontrado
    if (!aux){
        printf ("O elemento não está na árvore.\n");
        return 0;
    }
    // Se o elemento for folha
    if(aux->folha){
        // realiza um shift à esquerda das chaves a direita da chave a ser removida
        while (indice < aux->n - 1){
            aux->chaves[indice] = aux->chaves[indice + 1];
            indice++;
        }
        aux->n--;
    } else {
        // procura a chave predecessora
        predecessor = aux->filhos[indice];
        while (!predecessor->folha){
            predecessor = predecessor->filhos[predecessor->n];
        }
        //troca a chave predecessora com a chave a ser removida
        aux->chaves[indice] = predecessor->chaves[predecessor->n - 1];
        predecessor->n--;
        aux = predecessor;
    }
    if (aux->n < arv->ordem/2 - 1){
        balanceamento(arv, aux);
    }
    return 1;
}

void rotacao (Btree *arv, no *noDesbal, int indiceNoDesbal){
    no *pai = noDesbal->pai, *irmao;
    int indice = 0;
    if (indiceNoDesbal - 1 >= 0 && pai->filhos[indiceNoDesbal-1]->n - 1 >= arv->ordem/2 - 1){
        irmao = pai->filhos[indiceNoDesbal-1]; // Pegando o irmão à esquerda
        addChave(noDesbal, pai->chaves[indiceNoDesbal-1]); // Adicionando a chave do pai no nó desbalanceado
        // Substituindo a chave do pai pela chave mais à direita do irmão à esquerda
        pai->chaves[indiceNoDesbal-1] = irmao->chaves[--irmao->n];
        // Colocando o filho mais à direita no irmão no filho mais a esquerda do nó Desbalanceado
        noDesbal->filhos[0] = irmao->filhos[irmao->n+1];
        if (irmao->filhos[irmao->n+1]) {
            irmao->filhos[irmao->n + 1]->pai = noDesbal->filhos[0];
        }
    } else {
        irmao = pai->filhos[indiceNoDesbal+1]; // Pegando o irmão à direita
        addChave(noDesbal, pai->chaves[indiceNoDesbal]); // Adicionando a chave do pai no nó desbalanceado
        pai->chaves[indiceNoDesbal] = irmao->chaves[0]; // Substituindo a primeira chave do irmão com a do pai
        // Colocando o filho mais à esquerda no irmão no filho mais à direita do nó Desbalanceado
        noDesbal->filhos[noDesbal->n] = irmao->filhos[0];
        if (irmao->filhos[0]) {
            irmao->filhos[0]->pai = noDesbal;
        }
        // Dando shift uma casa para esquerda em todas as chaves e filhos do irmão
        while (indice < irmao->n - 1){
            irmao->chaves[indice] = irmao->chaves[indice+1];
            irmao->filhos[indice] = irmao->filhos[indice+1];
            indice++;
        }
        irmao->filhos[indice] = irmao->filhos[indice+1];
        irmao->n--; // Decrementando a chave removida
    }
    
    return;
}

void merge(Btree *arv, no* noDesbal,int indiceNoDesbal){
    no *pai = noDesbal->pai, *irmao;
    int indiceIrmao = 0;

    if (indiceNoDesbal < pai->n){
        irmao = pai->filhos[indiceNoDesbal+1];
    } else {
        irmao = noDesbal;
        noDesbal = pai->filhos[indiceNoDesbal-1];
    }

    //Descendo o pai para o no desbalanceado
    noDesbal->chaves[noDesbal->n++] = pai->chaves[indiceNoDesbal];

    //Passar os elementos do irmão para o no desbalanceado (merge)
    while (indiceIrmao < irmao->n){
        noDesbal->chaves[noDesbal->n] = irmao->chaves[indiceIrmao];//Passando a chaves do irmao para o no desbalanceado
        noDesbal->filhos[noDesbal->n] = irmao->filhos[indiceIrmao];//Passando o filho esquerdo da chave para o no desbalanceado
        noDesbal->filhos[noDesbal->n+1] = irmao->filhos[indiceIrmao+1];//Passando o filho direito da chave para o no desbalanceado
        if (irmao->filhos[indiceIrmao]){
            irmao->filhos[indiceIrmao]->pai = noDesbal;
            irmao->filhos[indiceIrmao+1]->pai = noDesbal;
        }
        noDesbal->n++;
        indiceIrmao++;
    }

    // Realizando shift à esquerda nos elementos do pai
    while (indiceNoDesbal < pai->n - 1 && indiceNoDesbal != arv->raiz){
        pai->chaves[indiceNoDesbal] = pai->chaves[indiceNoDesbal+1];
        pai->filhos[indiceNoDesbal+1] = pai->filhos[indiceNoDesbal+2];
    }
    pai->n--;
    if (pai == arv->raiz && pai->n == 0){
        arv->raiz = noDesbal;
    }
    liberaNo (irmao);
    return;
}



void balanceamento (Btree *arv, no *noDesbal){
    no* pai = noDesbal->pai;
    int indiceNoDesbal = 0;

    while (pai->filhos[indiceNoDesbal] != noDesbal){
        indiceNoDesbal++;
    }

    // Verificando se há irmão à esquerda e se remover uma chave dele não fará com que ele fique desbalanceado OU
    // se há irmão à direita e se remover uma chave dele não fará com que ele fique desbalanceado
    if ((indiceNoDesbal - 1 >= 0 && pai->filhos[indiceNoDesbal-1]->n - 1 >= arv->ordem/2 - 1) ||
        (indiceNoDesbal < pai->n && pai->filhos[indiceNoDesbal+1]->n - 1 >= arv->ordem/2 - 1)){

        rotacao(arv, noDesbal, indiceNoDesbal); // Realizando a rotação

    } else {
        merge(arv, noDesbal, indiceNoDesbal);
        if (pai != arv->raiz && pai->n < arv->ordem/2 - 1){
            balanceamento(arv, pai);
        }
    }

    return;
}

no* getRaiz (Btree *arv) {
    return arv->raiz;
}

void imprimirArvore(no *aux) {
    if (aux) {
        for (int i = 0; i < aux->n; i++) {
            printf("%d ", aux->chaves[i].valor);
        }
        printf ("- pai: ");
        if (aux->pai)
            for (int i = 0; i < aux->pai->n; i++) {
                printf("%d ", aux->pai->chaves[i].valor);
            }

        printf("\n");
        if (aux->filhos[0])
            printf ("filhos: ");
        for (int i = 0; i < aux->n + 1; i++){
            imprimirArvore(aux->filhos[i]);
        }
    }
    return;
}

int busca(no *aux, int nroMatricula) {
    int i = 0;
    // Encontre a primeira chave maior ou igual a k
    while (i < aux->n && nroMatricula > aux->chaves[i].valor) {
        i++;
    }

    // Se a chave for encontrada, retorne o nó
    if (aux->chaves[i].valor == nroMatricula) {
        return aux->chaves[i].indice;
    }

    // Se o nó é folha, não há mais aonde procurar
    if (aux->folha == 1) {
        return 0;
    }

    // Vá para o filho apropriado
    return busca(aux->filhos[i], nroMatricula);
}