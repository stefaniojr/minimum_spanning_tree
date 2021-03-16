#include "mst.h"

ListaArestas *criaListaArestas()
{
    ListaArestas *lista = (ListaArestas *)malloc(sizeof(ListaArestas));

    lista->ini = NULL;
    lista->fim = NULL;

    return lista;
}

Aresta *iniciaAresta(ListaPontos *lista, int id1, int id2, double distancia)
{
    Aresta *aresta = (Aresta *)malloc(sizeof(Aresta));

    //*********************************************************///
    celulaPonto *pontoCelula;
    Ponto *p1 = NULL, *p2 = NULL;

    for (pontoCelula = lista->ini; pontoCelula != NULL; pontoCelula = pontoCelula->prox)
    {
        if (pontoCelula->ponto->id == id1)
        {
            p1 = (Ponto *)malloc(sizeof(Ponto));
            p1 = pontoCelula->ponto;
        }

        if (pontoCelula->ponto->id == id2)
        {
            p2 = (Ponto *)malloc(sizeof(Ponto));
            p2 = pontoCelula->ponto;
        }

        // Se encontrou os dois pontos:
        if ((p1 != NULL) && (p2 != NULL))
            break;
    }

    if ((p1 == NULL) && (p2 == NULL))
        return NULL;

    //*********************************************************///

    aresta->destino = p1;
    aresta->origem = p2;
    aresta->distancia = distancia;

    return aresta;
}

void insereAresta(Aresta *aresta, ListaArestas *lista)
{
    celulaAresta *novaAresta = (celulaAresta *)malloc(sizeof(celulaAresta));

    novaAresta->prox = lista->ini;
    novaAresta->aresta = aresta;
    lista->ini = novaAresta;

    if (lista->fim == NULL)
        lista->fim = novaAresta;
}

void imprimeArestas(ListaArestas *lista)
{
    celulaAresta *arestaCelula;
    int i = 1;
    for (arestaCelula = lista->ini; arestaCelula != NULL; arestaCelula = arestaCelula->prox)
    {
        printf("%s %s %lf\n", arestaCelula->aresta->origem->nome, arestaCelula->aresta->destino->nome, arestaCelula->aresta->distancia);
        i++;
    }
}

void mergeSortListaArestas(ListaArestas **lista)
{
    celulaAresta *arestaCelula = (*lista)->ini;
    ListaArestas *a1 = (ListaArestas *)malloc(sizeof(ListaArestas));
    ListaArestas *a2 = (ListaArestas *)malloc(sizeof(ListaArestas));

    if ((arestaCelula == NULL) || (arestaCelula->prox == NULL))
        return;

    divisorDeListas(arestaCelula, &a1->ini, &a2->ini);

    mergeSortListaArestas(&a1);
    mergeSortListaArestas(&a2);

    (*lista)->ini = mergeListasArestas(a1->ini, a2->ini);
}

void divisorDeListas(celulaAresta *inicio, celulaAresta **frente, celulaAresta **atras)
{
    celulaAresta *umAUm;
    celulaAresta *doisADois;

    umAUm = inicio;
    doisADois = inicio->prox;

    while (doisADois != NULL)
    {
        doisADois = doisADois->prox;
        if (doisADois != NULL)
        {
            umAUm = umAUm->prox;
            doisADois = doisADois->prox;
        }
    }

    *frente = inicio;
    *atras = umAUm->prox;
    //doisADois->prox = NULL;
}

celulaAresta *mergeListasArestas(celulaAresta *a1, celulaAresta *a2)
{
    celulaAresta *aresta = NULL;

    if (a1 == NULL)
        return a2;
    else if (a2 == NULL)
        return a1;

    if (a1->aresta->distancia <= a2->aresta->distancia)
    {
        aresta = a1;
        aresta->prox = mergeListasArestas(a1->prox, a2);
    }
    else
    {
        aresta = a2;
        aresta->prox = mergeListasArestas(a1, a2->prox);
    }

    return aresta;
}
