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
    int nPontos = 0, i = 0, j = 0, q = 0;
    char *line = NULL;
    size_t size = 1000;
    // srand(time(NULL));

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
            //clock_t start_calc = clock();
            distanciaPontos[i][j] = calcDistancia(lista, i, j); //PRECISO TESTAR ALGO AQUI, 1 SEG
            // clock_t end_calc = clock();
            // double seconds_calc = ((double)end_calc - start_calc) / CLOCKS_PER_SEC;
            // printf("Tempo execusão calcDistanci: %lf \n", seconds_preorder);
            arvMST->vetorArestas[arvMST->nVetorArestas] = insereAresta(lista, i, j, distanciaPontos[i][j]);
            arvMST->nVetorArestas++;
            arvMST->vetorArestas = realloc(arvMST->vetorArestas, (arvMST->nVetorArestas + 1) * sizeof(Aresta *));
        }
        max++;
    }

    qsort(arvMST->vetorArestas, arvMST->nVetorArestas, sizeof(Aresta *), compDouble);

    geraVetorArestasMST(arvMST);
    removeArestas(arvMST);

    //for (i = 0; i < arvMST->nVetorArestas; i++)
    //printf("O lider de %s é: %s || O lider de %s é: %s\n", arvMST->vetorArestas[i]->origem->nome, arvMST->vetorArestas[i]->origem->pai->nome, arvMST->vetorArestas[i]->destino->nome, arvMST->vetorArestas[i]->destino->pai->nome);
    //  printf("%d. %s %s %lf\n", (i + 1), arvMST->vetorArestas[i]->origem->nome, arvMST->vetorArestas[i]->destino->nome, arvMST->vetorArestas[i]->distancia);

    // for (i = 0; i < arvMST->nArestasMST; i++)
    //     printf("Root de %s é: %s || Root de %s é: %s\n\n", arvMST->vetorArestas[i]->origem->nome, find(arvMST->vetorArestas[i]->origem)->nome, arvMST->vetorArestas[i]->destino->nome, find(arvMST->vetorArestas[i]->destino)->nome);
    //printf("%d. %s %s %lf\n", (i + 1), arvMST->vetorArestasMST[i]->origem->nome, arvMST->vetorArestasMST[i]->destino->nome, arvMST->vetorArestasMST[i]->distancia);

    Conjunto **conjuntos = malloc(k * sizeof(Conjunto));
    for (i = 0; i < k; i++)
        conjuntos[i] = criaConjunto();

    ArestasMST *aresta = arvMST->iniArestasMST;
    // while (aresta != NULL)
    //     printf("");
    // for (aresta = arvMST->iniArestasMST; aresta != NULL; aresta = aresta->prox)
    //     printf("%s %s %lf\n", aresta->aresta->origem->nome, aresta->aresta->destino->nome, aresta->aresta->distancia);

    for (i = k - 1; i >= 0; i--)
    {
        ArestasMST *ant = arvMST->iniArestasMST;
        aresta = arvMST->iniArestasMST;
        //printf("%d---\n", i);
        // for (aresta = arvMST->iniArestasMST; aresta != NULL; aresta = aresta->prox)
        //     printf("%s %s\n", aresta->aresta->origem->nome, aresta->aresta->destino->nome);
        printf("----------------------\n");

        while (aresta != NULL)
        {
            

            if (conjuntos[i]->root == NULL)
                conjuntos[i]->root = find(aresta->aresta->origem);

            if ((strcmp(conjuntos[i]->root->nome, find(aresta->aresta->origem)->nome) == 0))
            {
                if (!aresta->aresta->origem->agrupado)
                {
                    conjuntos[i]->pontos[conjuntos[i]->nPontos++] = aresta->aresta->origem;
                    conjuntos[i]->pontos = realloc(conjuntos[i]->pontos, (conjuntos[i]->nPontos + 1) * sizeof(Ponto *));
                    aresta->aresta->origem->agrupado = true;
                }

                if (!aresta->aresta->destino->agrupado)
                {
                    conjuntos[i]->pontos[conjuntos[i]->nPontos++] = aresta->aresta->destino;
                    conjuntos[i]->pontos = realloc(conjuntos[i]->pontos, (conjuntos[i]->nPontos + 1) * sizeof(Ponto *));
                    aresta->aresta->destino->agrupado = true;
                }
                printf("Aresta atual: %s - %s. Lider: %s\n", aresta->aresta->origem->nome, aresta->aresta->destino->nome, find(aresta->aresta->origem)->nome);

                if (arvMST->iniArestasMST->aresta->id == aresta->aresta->id)
                {
                    arvMST->iniArestasMST = aresta->prox;
                    aresta = arvMST->iniArestasMST;
                }

                else
                {
                    ant->prox = aresta->prox;
                }
            }
            else
            {
                ant = aresta;
                aresta = aresta->prox;
            }
            //libera aresta;
        }
    }

    // for (i = 0; i < k; i++)
    // {
    //     for (j = 0; j < conjuntos[i]->nPontos; j++)
    //     {
    //         if (j == conjuntos[i]->nPontos - 1)
    //             printf("%s", conjuntos[i]->pontos[j]->nome);
    //         else
    //             printf("%s,", conjuntos[i]->pontos[j]->nome);
    //     }
    //     printf("\n");
    // }

    liberaLista(lista);
    return 0;
}