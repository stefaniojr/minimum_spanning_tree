#ifndef ARESTA_H_
#define ARESTA_H_

#include "ponto.h"

typedef struct aresta Aresta;
typedef struct arvMST ArvMST;
typedef struct arestasMST ArestasMST;

struct aresta
{
    Ponto *origem;
    Ponto *destino;
    double distancia;
    int id;
};

struct arvMST
{
    int nConjuntos;
    Aresta **vetorArestas; // O vetor de arestas contém TODAS as possíveis arestas.
    int nVetorArestas;

    ArestasMST *iniArestasMST; // A lista encadeada arestas MST contém SOMENTE as arestas da MST.
    ArestasMST *fimArestasMST;
    int nArestasMST;
};

struct arestasMST
{
    Aresta *aresta;
    ArestasMST *prox;
};

// Dados dois pontos, insere em uma estrutura aresta.
Aresta *insereAresta(ListaPontos *lista, int id1, int id2, double distancia);
// Cria uma árvore MST.
ArvMST *criaArvMST(int nItensPorSubConjunto);
//Retorna o ponto root do grupo.
Ponto *find(Ponto *p);
// Dado dois pontos, unem eles.
void Union(Ponto *p1, Ponto *p2);
// Dado dois pontos, verificam se eles fazem parte da mesma componente conexa.
bool conectado(Ponto *p1, Ponto *p2);
// Gera o vetor de arestasMST, as arestasMST são as arestas que compõe a MST.
void geraVetorArestasMST(ArvMST *arvMST);
// Remove as k-1 arestas da única componente conexa criada.
void removeArestas(ArvMST *arvMST);
// Utiliza a matriz de distâncias para registrar as distâncias em um vetor de arestas.
void registraArestasDistancias(ArvMST *arvMST, ListaPontos *lista, double **distanciaPontos, int nPontos);
// Libera (tenta, pelo menos) as arestas MST.
ArvMST *liberaArestasMST(ArvMST *arvMST);
// Libera (tenta, pelo menos) as arestas.
ArvMST *liberaArestas(ArvMST *arvMST);

#endif /* ARESTA_H_ */