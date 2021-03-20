#ifndef CONJUNTO_H_
#define CONJUNTO_H_

#include "aresta.h"

typedef struct conjunto Conjunto;

struct conjunto
{
    Ponto **pontos; // Vetor de referências para ponto.
    Ponto *root; // Qual é o root desse conjunto de pontos?
    int nPontos; // Quantos pontos existem nesse conjunto?
};

// Cria k conjuntos iterativamente.
void criaConjuntos(Conjunto **conjuntos, int k);
// Inicia um conjunto e o retorna.
Conjunto *iniciaConjunto();
// Dado n conjuntos já inicializados, os preenche com arestas seguindo o critério de possuirem o mesmo root.
void insereArestasEmCadaConjunto(ArvMST *arvMST, ListaPontos *lista, Conjunto **conjuntos);

#endif /* CONJUNTO_H_ */