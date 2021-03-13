#ifndef PONTO_H_
#define PONTO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ponto Ponto;
typedef struct listapontos ListaPontos;

ListaPontos *criaLista();
Ponto *iniciaPonto(char *dadosPonto);
void inserePonto(Ponto *ponto, ListaPontos *lista);
void imprime(ListaPontos *lista);
ListaPontos *liberaLista(ListaPontos *lista);
void liberaPonto(Ponto *ponto);

#endif /* PONTO_H_ */