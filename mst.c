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
        printf("%d. %s %s %lf\n", i, arestaCelula->aresta->origem->nome, arestaCelula->aresta->destino->nome, arestaCelula->aresta->distancia);
        i++;
    }
}