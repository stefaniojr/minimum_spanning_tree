#ifndef PONTO_H_
#define PONTO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct ponto Ponto;
typedef struct listapontos ListaPontos;
typedef struct celulaponto CelulaPonto;

struct ponto
{
    char *nome;
    int id;
    double *coordenadas;
    size_t sCoordenadas; // sCoordenadas ajuda a iterar o vetor de double.
    Ponto *pai;
    int rank;
    bool agrupado;
};

struct celulaponto
{
    Ponto *ponto;
    CelulaPonto *prox;
};

struct listapontos
{
    CelulaPonto *ini;
    CelulaPonto *fim;
};

// Cria uma lista de pontos.
ListaPontos *criaListaPontos();
// Inicializa um ponto através dos dados de uma string. A string é quebrada usando strtok.
Ponto *iniciaPonto(char *dadosPonto, int id);
// Dado um ponto já inicializado, insere ele na lista encadeada de pontos.
void inserePonto(Ponto *ponto, ListaPontos *lista);
// Dado um vetor de strings, preenche uma lista encadeada com suas informações.
void preencheLista(ListaPontos *lista, char **arrayPontos, int nPontos);
// Dado dois pontos, calcula a distância entre eles.
double calcDistancia(ListaPontos *lista, int id1, int id2);
// Libera (tenta, pelo menos) a lista de pontos.
void liberaLista(ListaPontos *lista);
// Libera (tenta, pelo menos) um ponto.
void liberaPonto(Ponto *ponto);

#endif /* PONTO_H_ */