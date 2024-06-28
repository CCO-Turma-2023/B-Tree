#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

#define MAX_NOME 8

struct aluno{
    int matricula;
    char nome[14];
};

int* gerarEntrada (int n){
    int *v = (int*)malloc(sizeof(int) * n), indiceV, indiceU, aux;
    if (!v)
    {
        return NULL;
    }

    FILE *arq = fopen("entrada2.txt", "w+");
    FILE *nomes = fopen("nome10000.txt", "r");
    char s[14];
    if (!arq)
    {
        return NULL;
    }


    for (int i = 0; i < n; i++)
    {
        v[i] = 2023000000 + i;
    }

    for (int i = 0; i < 1494912; i++)
    {
        indiceV = rand() % n;
        indiceU = rand() % n;
        aux = v[indiceV];
        v[indiceV] = v[indiceU];
        v[indiceU] = aux;
    }

    for (int i = 0; i < n; i++)
    {
        fscanf (nomes, "%[^\n]", s);
        fprintf (arq, "%d %s\n", v[i], s);
    }
    fclose(arq);
    return v;
}

int main() {
    int ordem;
    int *v = gerarEntrada(10000);
    if (!v)
        return 1;
    printf ("Digite a ordem da arvore(Obs. Somente numeros pares e maior ou igual a 4):");
    scanf ("%d", &ordem);
    if (ordem%2 || ordem < 3){
        printf ("Numero invalido.");
        return 1;
    }
    Btree *arvore = criarArvore(ordem);
    chave aux;
    int vetor[10000];
    FILE *arq = fopen("entrada2.txt", "r");
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
    int oi = 0;
    for (int j = 0; j < 100; j++) {
        indiceArq = busca(getRaiz(arvore), vetor[j]);
        if (indiceArq == 0) {
            printf("Elemento nao encontrado\n");
        } else {
            oi++;
            printf ("%d - %d ..... ", vetor[j], indiceArq);
            fseek(arq, (indiceArq-1) * 27, SEEK_SET);
            //for (int i = 0; i < indiceArq - 1; i++)
                //fscanf(arq, "%d  %[^\n]", &aluno.matricula, aluno.nome);
            fscanf(arq, "%d  %s", &aluno.matricula, aluno.nome);
            printf("%d - %s\n", aluno.matricula, aluno.nome);
        }
    }
    printf ("\n%d", oi);
    return 0;
}