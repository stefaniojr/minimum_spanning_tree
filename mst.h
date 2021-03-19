#ifndef MST_H_
#define MST_H_

#include "ponto.h"


typedef struct aresta Aresta;
typedef struct arvMST ArvMST;
typedef struct arestasMST ArestasMST;
typedef struct conjunto Conjunto;

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

    ArestasMST *iniArestasMST;
    ArestasMST *fimArestasMST;
    int nArestasMST;
};

struct arestasMST{
    Aresta* aresta;
    ArestasMST* prox;
};

struct conjunto {
    Ponto** pontos;
    Ponto* root;
    int nPontos;
};

Aresta* insereAresta(ListaPontos *lista, int id1, int id2, double distancia);
void imprimeArestas(Aresta *lista);
ArvMST* criaArvMST(int nItensPorSubConjunto);
void algoritmoMST(ArvMST* arvMST, int sizeListaArestas);
Ponto* find(Ponto *p);
void Union(Ponto *p1, Ponto *p2);
bool conectado(Ponto *p1, Ponto *p2);
void geraVetorArestasMST(ArvMST *arvMST);
void removeArestas(ArvMST* arvMST);
Conjunto *criaConjunto();

#endif /* MST_H_ */