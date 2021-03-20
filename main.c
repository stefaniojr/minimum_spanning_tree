#include "io.h"
#include <time.h>

/**
 * Tentativa de implementação do Algoritmo de Kruskal (Disciplina: Estrutura de Dados II).
 * 
 * Bugs: - Para alguns números de k, o programa quebra (desconsidera pontos e agrupa o que ele quer!) - ainda não foi amplamente testado;
 *       - Há vazamento de memória;
 *       - Muito demorado. Implementação não recursiva.
 *
 * @author Lívia Barcellos Botelho (liviabbotelho@hotmail.com)
 * @author Stefânio Soares Junior (stefaniojr@live.com)
 * 
 */

int main(int argc, char *argv[])
{
    
    FILE *entrada = NULL, *saida = NULL;
    int nPontos = 0, i = 0, j = 0, q = 0;
    char *line = NULL;
    size_t size = 1000;
    int k = 0;
    // Se a linha de comando não possuir exatamente 4 argumentos então há falta ou excesso de argumentos.
    if (argc != 4)
    {
        printf("Há falta ou excesso de argumentos. Tente novamente.\nAbortando programa...\n");
        return 1;
    }
    
    entrada = fopen(argv[1], "r");
    k = atoi(argv[2]);
    saida = fopen(argv[3], "w");
    // Caso alguns dos argumentos sejam inválidos, aborta o programa.
    if (entrada == NULL || saida == NULL || k < 1)
    {
        printf("Um ou mais parâmetros não foram informados corretamente.\nAbortando programa...\n");
        return 1;
    }

    nPontos = contaLinhas(entrada); // Conta a quantidade de pontos que existem no arquivo de entrada.
    // Aloca um matriz de distância entre pontos.
    double **distanciaPontos = (double **)malloc(nPontos * sizeof(double *));
    for (i = 0; i < nPontos; i++)
        distanciaPontos[i] = (double *)malloc(nPontos * sizeof(double));

    rewind(entrada);

    line = (char *)malloc(size);                 // Variável auxiliar para ajudar na leitura do arquivo.
    char **arrayPontos = malloc(nPontos * size); // Aloca um array de pontos.

    lerPontosParaArray(arrayPontos, line, entrada); // Insere no vetor de pontos: cada linha do arquivo original uma posição no arrayPontos.
    fclose(entrada);
    
    free(line);

    ListaPontos *lista = criaListaPontos();     // Cria uma lista de pontos vazia.
    preencheLista(lista, arrayPontos, nPontos); // Prenche uma lista encadeada "quebrando" (strtok) as informações do array de pontos.
    ArvMST *arvMST = criaArvMST(k);             // Cria uma árvore MST vazia.
    registraArestasDistancias(arvMST, lista, distanciaPontos, nPontos); // Calcula distância entre todas as possibilidades de arestas e insere na matriz de pontos.
    geraVetorArestasMST(arvMST); // Ordena vetor de arestas e seleciona as arestas de menor peso para formar uma MST.
    removeArestas(arvMST); // Remove k-1 arestas.

    //printf("%s\n", arvMST->iniArestasMST->aresta->origem->nome);
    //Cria k conjuntos com as arestas determinadas a cada um.
    Conjunto **conjuntos = malloc(k * sizeof(Conjunto));
    criaConjuntos(conjuntos, k);
    insereArestasEmCadaConjunto(arvMST, lista, conjuntos);
    //Gera arquivo de saída.
    geraArquivoSaida(conjuntos, saida, arvMST);
    fclose(saida);
    

    // Tentativas de liberação da memória:
    for (i = 0; i < nPontos; i++) // Libera a memória alocada para a matriz de distâncias.
        free(distanciaPontos[i]);
    free(distanciaPontos);

    //arvMST = liberaArestasMST(arvMST); // Libera arestasMST da arvMST.
    //arvMST = liberaArestas(arvMST);    // Libera as arestas normais.
    liberaLista(lista);                // Libera lista de pontos.
    //free(arvMST);                      // Libera árvore.


    return 0;
}