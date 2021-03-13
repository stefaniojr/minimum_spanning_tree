#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include "ponto.h"

int main(int argc, char *argv[])
{

    FILE *entrada = NULL;
    char caracterAtual, fimLinha = '\n';
    int nPontos = 0;
    char *line = NULL;
    size_t size = 1000;

    entrada = fopen(argv[1], "r");

    if (entrada == NULL)
    {
        printf("Um ou mais parâmetros não foram informados corretamente.\nAbortando programa...\n");
        return 1;
    }

    // Quantas linhas têm o arquivo? Isto é, quantos pontos?
    while (fread(&caracterAtual, sizeof(char), 1, entrada))
        if (caracterAtual == fimLinha)
            nPontos++;

    rewind(entrada);

    line = (char *)malloc(size);
    char **arrayPontos = malloc(nPontos * size);

    // Lê as linhas do arquivo
    for (int i = 0; getline(&line, &size, entrada) != -1; i++)
    {
        arrayPontos[i] = (char *)malloc(size);
        strcpy(arrayPontos[i], line);
        size = 1000;
    }

    fclose(entrada);
    free(line);

    ListaPontos *lista = criaLista();

    for (int i = 0; i < nPontos; i++)
    {
        inserePonto(iniciaPonto(arrayPontos[i]), lista);
        free(arrayPontos[i]);
    }

    free(arrayPontos);
    liberaLista(lista);

    //imprime(lista);

    return 0;
}