#include "mst.h"

Aresta *insereAresta(ListaPontos *lista, int id1Ponto, int id2Ponto, double distancia)
{
    Aresta *aresta = (Aresta *)malloc(sizeof(Aresta));

    //*********************************************************///
    celulaPonto *pontoCelula;
    Ponto *p1 = NULL, *p2 = NULL;

    for (pontoCelula = lista->ini; pontoCelula != NULL; pontoCelula = pontoCelula->prox)
    {
        if (pontoCelula->ponto->id == id1Ponto)
        {
            p1 = (Ponto *)malloc(sizeof(Ponto));
            p1 = pontoCelula->ponto;
        }

        if (pontoCelula->ponto->id == id2Ponto)
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

ArvMST *criaArvMST(int nConjuntos)
{
    ArvMST *arvMST = (ArvMST *)malloc(sizeof(ArvMST));
    arvMST->nConjuntos = nConjuntos;
    arvMST->vetorArestas = (malloc(sizeof(Aresta *)));
    arvMST->nVetorArestas = 0;
    arvMST->vetorArestasMST = (malloc(sizeof(Aresta *)));
    arvMST->nVetorArestasMST = 0;
    return arvMST;
}

void geraVetorArestasMST(ArvMST *arvMST)
{

    for (int i = 0; i < arvMST->nVetorArestas; i++)
    {

        if (!conectado(arvMST->vetorArestas[i]->origem, arvMST->vetorArestas[i]->destino))
        {
            //printf("O lider de %s é: %s || O lider de %s é: %s\n", arvMST->vetorArestas[i]->origem->nome, arvMST->vetorArestas[i]->origem->pai->nome, arvMST->vetorArestas[i]->destino->nome, arvMST->vetorArestas[i]->destino->pai->nome);

            arvMST->vetorArestasMST[arvMST->nVetorArestasMST] = arvMST->vetorArestas[i];
            arvMST->nVetorArestasMST++;
            Union(arvMST->vetorArestas[i]->origem, arvMST->vetorArestas[i]->destino);
            arvMST->vetorArestasMST = realloc(arvMST->vetorArestasMST, (arvMST->nVetorArestasMST + 1) * sizeof(Aresta *));
            
        }
    }
}

// Retorna o líder do grupo.
// int find(Ponto *p)
// {
//     while (p->id != p->pai->id)
//     {
//         p->pai = p->pai->pai;
//         p->id = p->pai->id;
//     }
//     return p->id;
// }

int find(Ponto *p)
{
    // while (p->id != p->pai->id)
    // {
    //     p->pai = p->pai->pai;
    //     p->id = p->pai->id;
    // }
    // return p->id;
    int x = p->pai->id;

    if(p->id != p->pai->id)
        x = find(p->pai);
    
    return x;
}


// Dado dois pontos, unem eles.
void Union(Ponto *p1, Ponto *p2)
{

    if (p1->rank < p2->rank)
    {
        p1->pai = p2;
        p2->rank += p1->rank;
    }

    else
    {
        p2->pai = p1;
        p1->rank += p2->rank;
    }
}

bool conectado(Ponto *p1, Ponto *p2)
{
    return find(p1) == find(p2);
}