#ifndef MST_H_
#define MST_H_

#include "ponto.h"

typedef struct aresta Aresta;
typedef struct listaarestas ListaArestas;
typedef struct celulaaresta celulaAresta;

struct aresta
{
    Ponto *origem;
    Ponto *destino;
    double distancia;
};

struct celulaaresta
{
    Aresta *aresta;
    celulaAresta *prox;
};

struct listaarestas
{
    celulaAresta *ini;
    celulaAresta *fim;
};

ListaArestas *criaListaArestas();
Aresta *iniciaAresta(ListaPontos *lista, int id1, int id2, double distancia);
void insereAresta(Aresta *aresta, ListaArestas *lista);
void imprimeArestas(ListaArestas *lista);

#endif /* MST_H_ */