#include <stdio.h>
#include "btree.h"

#define MAX_NOME 8

struct aluno{
    int matricula;
    char nome[100];
};

int main() {
    int ordem = 4;
    Btree *arvore = criarArvore(ordem);
    chave aux;
    int vetor[200];
    FILE *arq = fopen("entrada.txt", "r");
    struct aluno aluno;
    int indice = 1, indiceArq;
    while (!feof(arq)) {
        fscanf(arq, "%d %[^\n]", &aluno.matricula, aluno.nome);
        aux.valor = aluno.matricula % 10000;
        aux.indice = indice;
        vetor[indice-1] = aux.valor;
        insereChave(arvore, aux);
        indice++;
    }
    int fodase = 0;
    for (int j = 0; j < indice-1; j++) {
        indiceArq = busca(getRaiz(arvore), vetor[j]);
        if (indiceArq == 0) {
            printf("erradflp´sdp´kfpksdfpkdsfo");
        } else {
            fodase++;
            fseek(arq, 0, SEEK_SET);
            for (int i = 0; i < indiceArq - 1; i++)
                fscanf(arq, "%d  %[^\n]", &aluno.matricula, aluno.nome);
            fscanf(arq, "%d  %[^\n]", &aluno.matricula, aluno.nome);
            printf("%d - %s\n", aluno.matricula, aluno.nome);
        }
    }
    printf ("\n%d", fodase);
    return 0;
}