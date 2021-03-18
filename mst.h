#ifndef MST_H_
#define MST_H_

#include "ponto.h"
#include <stdbool.h>

typedef struct aresta Aresta;
typedef struct arvMST ArvMST;
typedef struct subArvMST SubArvMST;

struct aresta
{
    Ponto *origem;
    Ponto *destino;
    double distancia;
    int id;
};

struct arvMST {
    int nConjuntos;
    Aresta** vetorArestas;
    int nVetorArestas;
    Aresta** vetorArestasMST;
    int nVetorArestasMST;
};

struct subArvMST {
    Ponto* pai;
    int rank;
    SubArvMST* prox;
};

Aresta* insereAresta(ListaPontos *lista, int id1, int id2, double distancia);
void imprimeArestas(Aresta *lista);
ArvMST* criaArvMST(int nItensPorSubConjunto);
void algoritmoMST(ArvMST* arvMST, int sizeListaArestas);
Ponto* find(Ponto *p);
void Union(Ponto *p1, Ponto *p2);
bool conectado(Ponto *p1, Ponto *p2);
void geraVetorArestasMST(ArvMST *arvMST);
void removeKArestas(ArvMST* arvMST);

#endif /* MST_H_ */