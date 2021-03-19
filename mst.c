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
    arvMST->iniArestasMST = NULL;
    arvMST->fimArestasMST = NULL;
    arvMST->nArestasMST = 0;
    return arvMST;
}

Conjunto *criaConjunto()
{
    Conjunto *conjuntos = (Conjunto *)malloc(sizeof(Conjunto));
    conjuntos->pontos = (malloc(sizeof(Ponto *)));
    conjuntos->nPontos = 0;
    conjuntos->root = NULL;
    return conjuntos;
}

void geraVetorArestasMST(ArvMST *arvMST)
{

    Ponto *A = arvMST->vetorArestas[0]->origem;
    Ponto *B = arvMST->vetorArestas[1]->origem;

    for (int i = 0; i < arvMST->nVetorArestas; i++)
    {

        if (!conectado(arvMST->vetorArestas[i]->origem, arvMST->vetorArestas[i]->destino))
        {
            ArestasMST *aresta = (ArestasMST *)malloc(sizeof(ArestasMST));
            aresta->prox = arvMST->iniArestasMST;
            aresta->aresta = arvMST->vetorArestas[i];
            arvMST->iniArestasMST = aresta;

            if (arvMST->fimArestasMST == NULL)
                arvMST->fimArestasMST = aresta;

            arvMST->nArestasMST++;
            Union(arvMST->vetorArestas[i]->origem, arvMST->vetorArestas[i]->destino);
        }
    }
}

//Retorna o ponto líder do grupo.
Ponto *find(Ponto *p)
{

    Ponto *root = p->pai;

    while (root->id != p->pai->pai->id)
        root->id = p->pai->pai->id;

    while (p->id != root->id)
    {
        int prox = p->pai->pai->id;
        p->pai->pai->id = root->id;
        p->id = prox;
    }

    return root;
}

// Dado dois pontos, unem eles.
void Union(Ponto *p1, Ponto *p2)
{
    Ponto *root1 = find(p1);
    Ponto *root2 = find(p2);

    if (root1->rank < root2->rank)
    {
        //p2->rank += p1->rank;
        root1->pai = root2;
    }

    else if (root1->rank > root2->rank)
    {
        //p1->rank += p2->rank;
        root2->pai = root1;
    }
    else
    {
        root2->pai = root1;
        root1->rank++;
    }
}

bool conectado(Ponto *p1, Ponto *p2)
{
    return find(p1)->id == find(p2)->id;
}

void removeArestas(ArvMST *arvMST)
{
    ArestasMST *aresta;
    int qtEliminar = arvMST->nConjuntos - 1;

    if (qtEliminar == 0)
        return;

    for (aresta = arvMST->iniArestasMST; aresta != NULL; aresta = aresta->prox)
    {
        if (arvMST->nArestasMST == 0)
            break;

        Ponto *rootOrigem = find(aresta->aresta->origem);
        Ponto *rootDestino = find(aresta->aresta->destino);
        rootOrigem->pai = rootOrigem;
        rootDestino->pai = rootDestino;

        Aresta* aux;
        arvMST->iniArestasMST = aresta->prox;
        //libera(aux)
        qtEliminar--;

        if (qtEliminar == 0)
            break;
    }
}