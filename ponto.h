#ifndef PONTO_H_
#define PONTO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct ponto Ponto;
typedef struct listapontos ListaPontos;

ListaPontos *criaLista();
Ponto *iniciaPonto(char *dadosPonto, int id);
void inserePonto(Ponto *ponto, ListaPontos *lista);
void imprime(ListaPontos *lista);
ListaPontos *liberaLista(ListaPontos *lista);
void liberaPonto(Ponto *ponto);
double calcDistancia(ListaPontos *lista, int id1, int id2);

#endif /* PONTO_H_ */