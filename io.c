#include "io.h"

// Função de callback para qsort.
static int compChar(const void *item1, const void *item2)
{
    Ponto *a1 = *(Ponto **)item1;
    Ponto *a2 = *(Ponto **)item2;

    return strcmp(a1->nome, a2->nome);
}

// Percorre o arquivo aberto (início ao fim) contando quantas linhas o arquivo possui, ou seja, o número de pontos.
int contaLinhas(FILE *entrada)
{
    int contador = 0;
    char caracterAtual, fimLinha = '\n';
    while (fread(&caracterAtual, sizeof(char), 1, entrada))
        if (caracterAtual == fimLinha)
            contador++;
    return contador;
}

// Percorre o arquivo aberto (início ao fim) a fim de ler linha a linha para um vetor de strings/matrix de caractéres.
void lerPontosParaArray(char **arrayPontos, char *line, FILE *entrada)
{
    size_t size = 1000;

    for (int i = 0; getline(&line, &size, entrada) != -1; i++)
    {
        arrayPontos[i] = (char *)malloc(size);
        strcpy(arrayPontos[i], line);
        size = 1000;
    }
}

// Imprime em um arquivo de saída os k grupos.
void geraArquivoSaida(Conjunto **conjuntos, FILE *saida, ArvMST *arvMST)
{

    for (int i = 0; i < arvMST->nConjuntos; i++)
    {
        qsort(conjuntos[i]->pontos, conjuntos[i]->nPontos, sizeof(Ponto *), compChar); // Ordena o vetor de pontos do conjunto por ordem alfabética.
        for (int j = 0; j < conjuntos[i]->nPontos; j++)
        {
            if (j == conjuntos[i]->nPontos - 1)
                fprintf(saida, "%s", conjuntos[i]->pontos[j]->nome);
            else
                fprintf(saida, "%s,", conjuntos[i]->pontos[j]->nome);
        }
        fprintf(saida, "\n");
    }
}