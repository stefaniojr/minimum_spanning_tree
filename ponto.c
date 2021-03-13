#include "ponto.h"

typedef struct cel TCelula;

struct ponto
{
    char *nome;
    double *coordenadas;
    size_t sCoordenadas;
};

struct cel
{
    Ponto *ponto;
    TCelula *prox;
};

struct listapontos
{
    TCelula *ini;
    TCelula *fim;
};

ListaPontos *criaLista()
{
    ListaPontos *lista = (ListaPontos *)malloc(sizeof(ListaPontos));

    lista->ini = NULL;
    lista->fim = NULL;

    return lista;
}

Ponto *iniciaPonto(char *dadosPonto)
{

    Ponto *ponto = (Ponto *)malloc(sizeof(Ponto));

    char *substr = strtok(dadosPonto, ",\n");
    ponto->nome = (char *)malloc((strlen(substr) + 1) * (sizeof(char)));
    strcpy(ponto->nome, substr);
    ponto->coordenadas = (double *)malloc(sizeof(double));
    ponto->sCoordenadas = (sizeof(double));

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
    TCelula *novoPonto = (TCelula *)malloc(sizeof(TCelula));

    novoPonto->prox = lista->ini;
    novoPonto->ponto = ponto;
    lista->ini = novoPonto;

    if (lista->fim == NULL)
        lista->fim = novoPonto;
}

void imprime(ListaPontos *lista)
{
    TCelula *pontoCelula;

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
    TCelula *pontoCelula = lista->ini;

    while (pontoCelula != NULL)
    {
        TCelula *pontoCelulaAtual = pontoCelula->prox;
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
