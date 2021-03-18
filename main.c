#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include "mst.h"

static int compDouble(const void *item1, const void *item2)
{
    Aresta *a1 = *(Aresta **)item1;
    Aresta *a2 = *(Aresta **)item2;

    if (((a1->distancia) - (a2->distancia)) > 0)
        return 1;
    else if (((a1->distancia) - (a2->distancia)) < 0)
        return -1;
    else
        return 0;
}

int main(int argc, char *argv[])
{

    FILE *entrada = NULL;
    char caracterAtual, fimLinha = '\n';
    int nPontos = 0, i = 0, j = 0;
    char *line = NULL;
    size_t size = 1000;

    entrada = fopen(argv[1], "r");

    if (entrada == NULL)
    {
        printf("Um ou mais parâmetros não foram informados corretamente.\nAbortando programa...\n");
        return 1;
    }

    // Quantas linhas têm o arquivo? Isto é, quantos pontos?
    while (fread(&caracterAtual, sizeof(char), 1, entrada))
        if (caracterAtual == fimLinha)
            nPontos++;

    double **distanciaPontos = (double **)malloc(nPontos * sizeof(double *));
    for (i = 0; i < nPontos; i++)
        distanciaPontos[i] = (double *)malloc(nPontos * sizeof(double));

    rewind(entrada);

    line = (char *)malloc(size);
    char **arrayPontos = malloc(nPontos * size);

    // Lê as linhas do arquivo
    for (i = 0; getline(&line, &size, entrada) != -1; i++)
    {
        arrayPontos[i] = (char *)malloc(size);
        strcpy(arrayPontos[i], line);
        size = 1000;
    }

    fclose(entrada);
    free(line);

    ListaPontos *lista = criaListaPontos();

    for (i = 0; i < nPontos; i++)
    {
        inserePonto(iniciaPonto(arrayPontos[i], i), lista);
        free(arrayPontos[i]);
    }

    free(arrayPontos);

    int k = 3;
    ArvMST *arvMST = criaArvMST(k);

    int max = 0;

    for (i = 0; i < nPontos; i++)
    {
        for (j = 0; j < max; j++)
        {

            distanciaPontos[i][j] = calcDistancia(lista, i, j);
            arvMST->vetorArestas[arvMST->nVetorArestas] = insereAresta(lista, i, j, distanciaPontos[i][j]);
            arvMST->nVetorArestas++;
            arvMST->vetorArestas = realloc(arvMST->vetorArestas, (arvMST->nVetorArestas + 1) * sizeof(Aresta *));
        }
        max++;
    }

    qsort(arvMST->vetorArestas, arvMST->nVetorArestas, sizeof(Aresta *), compDouble);

    geraVetorArestasMST(arvMST);
    removeKArestas(arvMST);

    //for (i = 0; i < arvMST->nVetorArestas; i++)
    //printf("O lider de %s é: %s || O lider de %s é: %s\n", arvMST->vetorArestas[i]->origem->nome, arvMST->vetorArestas[i]->origem->pai->nome, arvMST->vetorArestas[i]->destino->nome, arvMST->vetorArestas[i]->destino->pai->nome);
    //  printf("%d. %s %s %lf\n", (i + 1), arvMST->vetorArestas[i]->origem->nome, arvMST->vetorArestas[i]->destino->nome, arvMST->vetorArestas[i]->distancia);

    for (i = 0; i < arvMST->nVetorArestasMST; i++)
        printf("%d. %s %s %lf\n", (i + 1), arvMST->vetorArestasMST[i]->origem->nome, arvMST->vetorArestasMST[i]->destino->nome, arvMST->vetorArestasMST[i]->distancia);
    
    

    //algoritmoMST(arvMST, sizeListaArestas);
    liberaLista(lista);
    return 0;
}