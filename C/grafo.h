#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    char id;
    float x, y;
    char rua1[50];
    char rua2[50];
} Ponto;

typedef struct {
    char origem;
    char destino;
    char rua[50];
    float distancia;
} Vizinho;

typedef struct {
    int num_pontos;
    int num_vizinhos;
    Ponto* pontos;
    Vizinho* vizinhos;
} Grafo;

float calcular_distancia(float x1, float y1, float x2, float y2);
void ler_pontos(Grafo* grafo, const char* arquivo_pontos);
void ler_vizinhos(Grafo* grafo, const char* arquivo_vizinhos);
void salvar_grafo_binario(Grafo* grafo, const char* arquivo_saida);
void carregar_grafo_binario(Grafo* grafo, const char* arquivo_entrada);

#endif
