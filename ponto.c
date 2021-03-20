#include "ponto.h"

// Cria uma lista de pontos.
ListaPontos *criaListaPontos()
{
    ListaPontos *lista = (ListaPontos *)malloc(sizeof(ListaPontos));

    lista->ini = NULL;
    lista->fim = NULL;

    return lista;
}

// Dado um vetor de strings, preenche uma lista encadeada com suas informações.
void preencheLista(ListaPontos *lista, char **arrayPontos, int nPontos)
{
    int i = 0;
    for (i = 0; i < nPontos; i++)
    {
        inserePonto(iniciaPonto(arrayPontos[i], i), lista);
        free(arrayPontos[i]);
    }

    free(arrayPontos);
}

// Inicializa um ponto através dos dados de uma string. A string é quebrada usando strtok.
// Cada separador (vírgula ou \n) indica o fim de uma informação, isto é, a string é separada por vírgulas e cada palavra entre as vírgulas é uma informação.
// Essas informações já estão em uma ordem previamente conhecida (ponto + coordenadas).
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

// Dado um ponto já inicializado, insere ele na lista encadeada de pontos.
void inserePonto(Ponto *ponto, ListaPontos *lista)
{
    CelulaPonto *novoPonto = (CelulaPonto *)malloc(sizeof(CelulaPonto));

    novoPonto->prox = lista->ini;
    novoPonto->ponto = ponto;
    lista->ini = novoPonto;

    if (lista->fim == NULL)
        lista->fim = novoPonto;
}

// Dado dois pontos, calcula a distância entre eles.
// PS: uma das funções mais importantes deste TAD!!
double calcDistancia(ListaPontos *lista, int id1, int id2)
{
    double distancia = 0;
    size_t sIterator = 0;
    Ponto *p1 = NULL;
    Ponto *p2 = NULL;

    CelulaPonto *pontoCelula;

    // Encontra dois pontos. (Repetição de código, usamos o mesmo bloco em alguma na função insereAresta() do TAD aresta,
    // mas por algum motivo estranho não conseguimos criar uma função desse trecho). Fica pra uma próxima :(
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

    if ((p1 == NULL) && (p2 == NULL))
        return -1;

    // Cálculo da distância entre esses pontos. Não foi utilizado sqrt.
    for (int i = 0; sIterator != p1->sCoordenadas; i++)
    {
        distancia += (p2->coordenadas[i] - p1->coordenadas[i]) * (p2->coordenadas[i] - p1->coordenadas[i]);
        sIterator += sizeof(p1->coordenadas[i]);
    }

    return distancia;
}

// Libera (tenta, pelo menos) a lista de pontos.
void liberaLista(ListaPontos *lista)
{
    CelulaPonto *pontoCelula = lista->ini;

    while (pontoCelula != NULL)
    {
        CelulaPonto *pontoCelulaAtual = pontoCelula->prox;
        liberaPonto(pontoCelula->ponto);
        free(pontoCelula);
        pontoCelula = pontoCelulaAtual;
    }

    free(lista);
}

// Libera (tenta, pelo menos) um ponto.
void liberaPonto(Ponto *ponto)
{
    if (ponto != NULL)
    {
        free(ponto->nome);
        free(ponto->coordenadas);
        free(ponto);
    }
}