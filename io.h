#ifndef IO_H_
#define IO_H_
#include "conjunto.h"

// Percorre o arquivo aberto (início ao fim) contando quantas linhas o arquivo possui, ou seja, o número de pontos.
int contaLinhas(FILE *entrada);
// Percorre o arquivo aberto (início ao fim) a fim de ler linha a linha para um vetor de strings/matrix de caractéres.
void lerPontosParaArray(char **arrayPontos, char *line, FILE *entrada);
// Imprime em um arquivo de saída os k grupos.
void geraArquivoSaida(Conjunto** conjuntos, FILE* saida, ArvMST* arvMST);
#endif /* IO_H_ */