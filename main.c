#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include "mst.h"

static int cmpfunc(const void *a, const void *b)
{

    Aresta *p1 = (Aresta *)malloc(sizeof(Aresta));
    Aresta *p2 = (Aresta *)malloc(sizeof(Aresta));
    p1 = *(Aresta **)a;
    p2 = *(Aresta **)b;

    return (1);
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

    double distanciaPontos[nPontos][nPontos];

    // Preenche matriz de distância entre pontos com 0's.
    for (i = 0; i < nPontos; i++)
        for (j = 0; j < nPontos; j++)
            distanciaPontos[i][j] = 0;

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

    ListaArestas *listaArestas = criaListaArestas();
    int max = 0;
    int nItensListaAresta = 0;
    for (i = 0; i < nPontos; i++)
    {
        for (j = 0; j < max; j++)
        {
            distanciaPontos[i][j] = calcDistancia(lista, i, j);
            insereAresta(iniciaAresta(lista, i, j, distanciaPontos[i][j]), listaArestas);
            nItensListaAresta++;
        }
        max++;
    }

    // for (i = 0; i < nPontos; i++)
    // {
    //     for (j = 0; j < nPontos; j++)
    //         printf("%.2lf ", distanciaPontos[i][j]);
    //     printf("\n");
    // }

    mergeSortListaArestas(&listaArestas);
    imprimeArestas(listaArestas);
    liberaLista(lista);
    return 0;
}