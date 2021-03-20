### Makefile ###

COMPILER=g++ -std=c++11


all: trab1

trab1: ponto.o aresta.o conjunto.o io.o main.o
	gcc -o trab1 ponto.o aresta.o conjunto.o io.o main.o

ponto.o: ponto.c
	gcc -c ponto.c

aresta.o: aresta.c
	gcc -c aresta.c

conjunto.o: conjunto.c
	gcc -c conjunto.c

io.o: io.c
	gcc -c io.c
	
main.o: main.c
	gcc -c main.c
	
	
