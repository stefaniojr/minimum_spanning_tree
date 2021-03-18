#include "ponto.h"



ListaPontos *criaListaPontos()
{
    ListaPontos *lista = (ListaPontos *)malloc(sizeof(ListaPontos));

    lista->ini = NULL;
    lista->fim = NULL;

    return lista;
}

Ponto *iniciaPonto(char *dadosPonto, int id)
{

    Ponto *ponto = (Ponto *)malloc(sizeof(Ponto));

    ponto->id = id;
    ponto->rank = 0;
    char *substr = strtok(dadosPonto, ",\n");
    ponto->nome = (char *)malloc((strlen(substr) + 1) * (sizeof(char)));
    strcpy(ponto->nome, substr);
    ponto->coordenadas = (double *)malloc(sizeof(double));
    ponto->sCoordenadas = (sizeof(double));

    ponto->pai = ponto;
    for (int i = 0; substr != NULL; i++)
    {
        substr = strtok(NULL, ",\n");
        if (substr != NULL)
        {
            ponto->coordenadas = (double *)realloc(ponto->coordenadas, (i + 1) * sizeof(double));
            ponto->sCoordenadas = ((i + 1) * sizeof(double));
            ponto->coordenadas[i] = atof(substr);
        }
    }

    return ponto;
}

void inserePonto(Ponto *ponto, ListaPontos *lista)
{
    celulaPonto *novoPonto = (celulaPonto *)malloc(sizeof(celulaPonto));

    novoPonto->prox = lista->ini;
    novoPonto->ponto = ponto;
    lista->ini = novoPonto;

    if (lista->fim == NULL)
        lista->fim = novoPonto;
}

void imprime(ListaPontos *lista)
{
    celulaPonto *pontoCelula;
    
    for (pontoCelula = lista->ini; pontoCelula != NULL; pontoCelula = pontoCelula->prox)
    {
        printf("%s ", pontoCelula->ponto->nome);
        size_t sIterator = 0;
        for (int i = 0; sIterator != pontoCelula->ponto->sCoordenadas; i++)
        {
            printf("%lf ", pontoCelula->ponto->coordenadas[i]);
            sIterator += sizeof(pontoCelula->ponto->coordenadas[i]);
        }
        printf("\n");
    }
}

ListaPontos *liberaLista(ListaPontos *lista)
{
    celulaPonto *pontoCelula = lista->ini;

    while (pontoCelula != NULL)
    {
        celulaPonto *pontoCelulaAtual = pontoCelula->prox;
        liberaPonto(pontoCelula->ponto);
        free(pontoCelula);
        pontoCelula = pontoCelulaAtual;
    }

    free(lista);
}

void liberaPonto(Ponto *ponto)
{
    if (ponto != NULL)
    {
        free(ponto->nome);
        free(ponto->coordenadas);
        free(ponto);
    }
}

// void encontraPontos(ListaPontos *lista, int id1, int id2, Ponto *p1, Ponto *p2)
// {
//     celulaPonto *pontoCelula;

//     for (pontoCelula = lista->ini; pontoCelula != NULL; pontoCelula = pontoCelula->prox)
//     {
//         if (pontoCelula->ponto->id == id1)
//         {
//             p1 = (Ponto *)malloc(sizeof(Ponto));
//             p1 = pontoCelula->ponto;
//         }

//         if (pontoCelula->ponto->id == id2)
//         {
//             p2 = (Ponto *)malloc(sizeof(Ponto));
//             p2 = pontoCelula->ponto;
//         }

//         // Se encontrou os dois pontos:
//         if ((p1 != NULL) && (p2 != NULL))
//             break;
//     }
//     return;
// }

double calcDistancia(ListaPontos *lista, int id1, int id2)
{
    double distancia = 0;
    size_t sIterator = 0;
    Ponto *p1 = NULL;
    Ponto *p2 = NULL;

    // encontraPontos(lista, id1, id2, p1, p2);


    //*********************************************************///
    celulaPonto *pontoCelula;

    for (pontoCelula = lista->ini; pontoCelula != NULL; pontoCelula = pontoCelula->prox)
    {
        if (pontoCelula->ponto->id == id1)
        {
            p1 = (Ponto *)malloc(sizeof(Ponto));
            p1 = pontoCelula->ponto;
        }

        if (pontoCelula->ponto->id == id2)
        {
            p2 = (Ponto *)malloc(sizeof(Ponto));
            p2 = pontoCelula->ponto;
        }

        // Se encontrou os dois pontos:
        if ((p1 != NULL) && (p2 != NULL))
            break;
    }

    //*********************************************************///

    if ((p1 == NULL) && (p2 == NULL))
        return -1;

    for (int i = 0; sIterator != p1->sCoordenadas; i++)
    {
        distancia += (p2->coordenadas[i] - p1->coordenadas[i]) * (p2->coordenadas[i] - p1->coordenadas[i]);
        sIterator += sizeof(p1->coordenadas[i]);
    }

    // printf("%.2lf ", sqrt(distancia));
    return distancia;
}
