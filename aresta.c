#include "aresta.h"

// Função de callback para a qsort.
static int compDouble(const void *item1, const void *item2)
{
    Aresta *a1 = *(Aresta **)item1;
    Aresta *a2 = *(Aresta **)item2;

    if (((a1->distancia) - (a2->distancia)) > 0)
        return 1;
    else if (((a1->distancia) - (a2->distancia)) < 0)
        return -1;
    else
        return 0;
}

// Dados dois pontos, insere em uma estrutura aresta.
Aresta *insereAresta(ListaPontos *lista, int id1Ponto, int id2Ponto, double distancia)
{
    Aresta *aresta = (Aresta *)malloc(sizeof(Aresta));

    CelulaPonto *pontoCelula;
    Ponto *p1 = NULL, *p2 = NULL;

    // Encontrar os dois pontos.
    for (pontoCelula = lista->ini; pontoCelula != NULL; pontoCelula = pontoCelula->prox)
    {
        // Verifica se o id do ponto a ser encontrado coincide com o id do ponto iterado.
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

    // Inserir os dois pontos nos campos respectivos da estrutura.
    aresta->origem = p1;
    aresta->destino = p2;
    aresta->distancia = distancia;

    return aresta;
}

// Cria uma árvore MST.
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

// Gera o vetor de arestasMST, as arestasMST são as arestas que compõe a MST.
void geraVetorArestasMST(ArvMST *arvMST)
{

    qsort(arvMST->vetorArestas, arvMST->nVetorArestas, sizeof(Aresta *), compDouble); // Ordena o vetor de arestas em ordem de distância.

    for (int i = 0; i < arvMST->nVetorArestas; i++)
    {
        // Caso os pontos não estejam conectados, conectam eles a fim de formar uma única componente conexa. (Condição inicial: o root de um ponto é ele mesmo)
        // Importante salientar que, como a lista de arestas está ordenada em ordem crescente de distância, as menores distâncias serão conectadas primeiro.
        // Esse trecho de código impede a formação de ciclos, pois é verificado se os pontos não possuem o mesmo root.
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

//Retorna o ponto root do grupo.
Ponto *find(Ponto *p)
{

    Ponto *root = p->pai;
    // Usando compreessão de caminho de maneira iterativa.
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
        root1->pai = root2;

    else if (root1->rank > root2->rank)
        root2->pai = root1;

    else
    {
        root2->pai = root1;
        root1->rank++;
    }
}

// Dado dois pontos, verificam se eles fazem parte da mesma componente conexa.
bool conectado(Ponto *p1, Ponto *p2)
{
    return find(p1)->id == find(p2)->id;
}

// Remove as k-1 arestas da única componente conexa criada.
void removeArestas(ArvMST *arvMST)
{
    ArestasMST *aresta;
    int qtEliminar = arvMST->nConjuntos - 1;

    if (qtEliminar == 0)
        return;

    // Como a lista está ordenada em ordem descrente, basta remover as k-1 primeiras arestas da lista.
    for (aresta = arvMST->iniArestasMST; aresta != NULL; aresta = aresta->prox)
    {
        if (arvMST->nArestasMST == 0)
            break;
        // !!! PROFESSOR, ATENÇÃO: não conseguimos analisar bem essa parte do código, mas talvez aqui esteja gerando algum tipo de bug na hora de separar os k grupos.
        // O que esse trecho faz: faz o root dos pontos de origem e destino apontarem cada um pra si mesmo respectivamente, pois até então todos eles apontam pra um único.
        // Exemplo: utilizando o exemplo da especificação, D tem root A, G tem root A, mas A tem root C (B também tem root C, e C tem root C). Ao remover a aresta G-F precisamos fazer o root de G, ou seja A, apontar pra si mesmo.
        Ponto *rootOrigem = find(aresta->aresta->origem);
        Ponto *rootDestino = find(aresta->aresta->destino);
        rootOrigem->pai = rootOrigem;
        rootDestino->pai = rootDestino;

        Aresta *aux;
        arvMST->iniArestasMST = aresta->prox;
        qtEliminar--;

        if (qtEliminar == 0)
            break;
    }
}

// Utiliza a matriz de distâncias para registrar as distâncias em um vetor de arestas.
// Optamos por um VETOR, pois esse conjunto de arestas serão ordenadas em ordem crescente de tamanho e a qsort aceita somente vetores.
void registraArestasDistancias(ArvMST *arvMST, ListaPontos *lista, double **distanciaPontos, int nPontos)
{
    int maxPorLinha = 0, i = 0, j = 0;
    for (i = 0; i < nPontos; i++)
    {
        for (j = 0; j < maxPorLinha; j++)
        {
            distanciaPontos[i][j] = calcDistancia(lista, i, j);
            arvMST->vetorArestas[arvMST->nVetorArestas] = insereAresta(lista, i, j, distanciaPontos[i][j]);
            arvMST->nVetorArestas++;
            arvMST->vetorArestas = realloc(arvMST->vetorArestas, (arvMST->nVetorArestas + 1) * sizeof(Aresta *)); // Realoca o vetor de arestas.
        }
        maxPorLinha++;
    }
}

// Libera (tenta, pelo menos) as arestas MST.
ArvMST *liberaArestasMST(ArvMST *arvMST)
{
    ArvMST *arv = arvMST;
    ArestasMST *arestaMST = arv->iniArestasMST;

    while (arestaMST != NULL)
    {
        ArestasMST *arestaMSTAtual = arestaMST->prox;
        free(arestaMST);
        arestaMST = arestaMSTAtual;
    }

    free(arv->iniArestasMST);
    free(arv->fimArestasMST);

    return arv;
}

// Libera (tenta, pelo menos) as arestas.
ArvMST *liberaArestas(ArvMST *arvMST)
{
    ArvMST *arv = arvMST;
    for (int i = 0; i < arv->nVetorArestas; i++)
        free(arv->vetorArestas[i]);
    free(arv->vetorArestas);
    return arv;
}
