#include "conjunto.h"

// Cria k conjuntos iterativamente.
void criaConjuntos(Conjunto **conjuntos, int k)
{
    int i = 0;
    for (i = 0; i < k; i++)
        conjuntos[i] = iniciaConjunto(); // Inicializa o i-ésimo conjunto.
}

// Inicia um conjunto e o retorna.
Conjunto *iniciaConjunto()
{
    Conjunto *conjunto = (Conjunto *)malloc(sizeof(Conjunto));
    conjunto->pontos = (malloc(sizeof(Ponto *)));
    conjunto->nPontos = 0; // Ainda não há pontos, logo essa variável é nula.
    conjunto->root = (malloc(sizeof(Ponto *)));
    conjunto->root = NULL; // Inicializa a variável root com NULL, pois ainda é um conjunto vazio.
    return conjunto;
}

// Dado n conjuntos já inicializados, os preenche com arestas seguindo o critério de possuirem o mesmo root.
void insereArestasEmCadaConjunto(ArvMST *arvMST, ListaPontos *lista, Conjunto **conjuntos)
{
    int i = 0;
    ArestasMST *aresta = (malloc(sizeof(ArestasMST *)));
    ArestasMST *ant = (malloc(sizeof(ArestasMST *)));

    // Nossa lista está em ordem decrescente, então percorremos os n Conjuntos na ordem inversa para os grupos serem formados na ordem desejada.
    for (i = arvMST->nConjuntos - 1; i >= 0; i--)
    {
        ant = arvMST->iniArestasMST;
        aresta = arvMST->iniArestasMST;

        while (aresta != NULL)
        {

            // Conjuntos não tem root registrado, registre um.
            if (conjuntos[i]->root == NULL)
                conjuntos[i]->root = find(aresta->aresta->origem);

            // Caso o root do conjunto atual seja coincidente com o root da aresta em análise, insere nele.
            if ((strcmp(conjuntos[i]->root->nome, find(aresta->aresta->origem)->nome) == 0))
            {
                // Como estamos inserido aresta a aresta(dois pontos), precisamos verificar se um daqueles pontos já está agrupado.
                // Caso já esteja agrupado, não o insere, pois se não teríamos um ponto repetido.
                if (!aresta->aresta->origem->agrupado)
                {
                    conjuntos[i]->pontos[conjuntos[i]->nPontos++] = aresta->aresta->origem;                              // Insere ponto de origem no grupo.
                    conjuntos[i]->pontos = realloc(conjuntos[i]->pontos, (conjuntos[i]->nPontos + 1) * sizeof(Ponto *)); // Realoca o vetor de pontos para a quantidade atual requisitada.
                    aresta->aresta->origem->agrupado = true;                                                             // Seta como true para que não seja mais inserido em nenhum grupo e evite repetição.
                }

                if (!aresta->aresta->destino->agrupado)
                {
                    conjuntos[i]->pontos[conjuntos[i]->nPontos++] = aresta->aresta->destino;                             // Insere ponto de destino no grupo.
                    conjuntos[i]->pontos = realloc(conjuntos[i]->pontos, (conjuntos[i]->nPontos + 1) * sizeof(Ponto *)); // Realoca o vetor de pontos para a quantidade atual requisitada.
                    aresta->aresta->destino->agrupado = true;                                                            // Seta como true para que não seja mais inserido em nenhum grupo e evite repetição.
                }

                // Remove a aresta da lista.
                // Caso a aresta seja a primeira da lista de arestasMST, remove ela da maneira apropriada.
                if ((strcmp(aresta->aresta->origem->nome, arvMST->iniArestasMST->aresta->origem->nome) == 0) && (strcmp(aresta->aresta->destino->nome, arvMST->iniArestasMST->aresta->destino->nome) == 0))
                {
                    ArestasMST *aux = aresta;
                    arvMST->iniArestasMST = aresta->prox;
                    aresta = aresta->prox;
                }
                // Caso contrário remove ela de outra maneira (considerando que ela está no meio da lista).
                else
                {
                    ArestasMST *aux = aresta;
                    ant->prox = aresta->prox;
                    aresta = aresta->prox;
                }
            }
            // Caso contrário, somente pula pra próxima aresta.
            else
            {
                ant = aresta;
                aresta = aresta->prox;
            }
        }
    }
}