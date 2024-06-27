#include <stdio.h>
#include "btree.h"

#define MAX_NOME 8

struct aluno{
    int matricula;
    char nome[100];
};

int main() {
    int ordem;
    printf ("Digite a ordem da arvore(Obs. Somente numeros pares e maior ou igual a 4):");
    scanf ("%d", &ordem);
    if (ordem%2 || ordem < 3){
        printf ("Numero invalido.");
        return 1;
    }
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
    for (int j = 0; j < indice-1; j++) {
        indiceArq = busca(getRaiz(arvore), vetor[j]);
        if (indiceArq == 0) {
            printf("Elemento nao encontrado\n");
        } else {
            fseek(arq, 0, SEEK_SET);
            for (int i = 0; i < indiceArq - 1; i++)
                fscanf(arq, "%d  %[^\n]", &aluno.matricula, aluno.nome);
            fscanf(arq, "%d  %[^\n]", &aluno.matricula, aluno.nome);
            printf("%d - %s\n", aluno.matricula, aluno.nome);
        }
    }
    return 0;
}