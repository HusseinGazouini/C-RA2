#include "grafo.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int encontrar_ponto_minimo(int* distancias, int* visitado, int num_pontos) {
    int min = INT_MAX;
    int min_index = -1;

    for (int i = 0; i < num_pontos; i++) {
        if (!visitado[i] && distancias[i] < min) {
            min = distancias[i];
            min_index = i;
        }
    }

    return min_index;
}

void determinar_direcao(const Grafo* grafo, int atual, int proximo) {
    const char* rua = NULL;

    // Encontre a rua entre os pontos atual e próximo
    for (int j = 0; j < grafo->num_vizinhos; j++) {
        if (grafo->vizinhos[j].origem == grafo->pontos[atual].id &&
            grafo->vizinhos[j].destino == grafo->pontos[proximo].id) {
            rua = grafo->vizinhos[j].rua;
            break;
        }
    }

    if (rua) {
        printf("- Siga pela rua %s do ponto %c para o ponto %c.\n",
               rua, grafo->pontos[atual].id, grafo->pontos[proximo].id);
    } else {
        printf("- Direcao desconhecida entre %c e %c.\n",
               grafo->pontos[atual].id, grafo->pontos[proximo].id);
    }
}

void dijkstra(Grafo* grafo, char origem, char destino) {
    int* distancias = (int*)malloc(grafo->num_pontos * sizeof(int));
    int* prev = (int*)malloc(grafo->num_pontos * sizeof(int));
    int* visitado = (int*)malloc(grafo->num_pontos * sizeof(int));

    for (int i = 0; i < grafo->num_pontos; i++) {
        distancias[i] = INT_MAX;
        prev[i] = -1;
        visitado[i] = 0;
    }

    int origem_idx = -1, destino_idx = -1;
    for (int i = 0; i < grafo->num_pontos; i++) {
        if (grafo->pontos[i].id == origem) {
            origem_idx = i;
        }
        if (grafo->pontos[i].id == destino) {
            destino_idx = i;
        }
    }

    if (origem_idx == -1 || destino_idx == -1) {
        printf("Ponto de origem ou destino nao encontrado.\n");
        free(distancias);
        free(prev);
        free(visitado);
        return;
    }

    distancias[origem_idx] = 0;

    for (int i = 0; i < grafo->num_pontos - 1; i++) {
        int u = encontrar_ponto_minimo(distancias, visitado, grafo->num_pontos);
        if (u == -1) break;
        visitado[u] = 1;

        for (int j = 0; j < grafo->num_vizinhos; j++) {
            if (grafo->vizinhos[j].origem == grafo->pontos[u].id) {
                int v = -1;
                for (int k = 0; k < grafo->num_pontos; k++) {
                    if (grafo->pontos[k].id == grafo->vizinhos[j].destino) {
                        v = k;
                        break;
                    }
                }

                if (v != -1 && distancias[u] + grafo->vizinhos[j].distancia < distancias[v]) {
                    distancias[v] = distancias[u] + grafo->vizinhos[j].distancia;
                    prev[v] = u;
                }
            }
        }
    }

    if (distancias[destino_idx] == INT_MAX) {
        printf("Nao ha caminho entre os pontos fornecidos.\n");
        free(distancias);
        free(prev);
        free(visitado);
        return;
    }

    int caminho[grafo->num_pontos];
    int count = 0;

    for (int u = destino_idx; u != -1; u = prev[u]) {
        caminho[count++] = u;
    }

    printf("Caminho de %c para %c:\n", origem, destino);

    for (int i = count - 1; i > 0; i--) {
        int atual = caminho[i];
        int proximo = caminho[i - 1];
        determinar_direcao(grafo, atual, proximo);
    }

    printf("Voce chegou ao seu destino!\n");

    free(distancias);
    free(prev);
    free(visitado);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: %s <grafo.bin>\n", argv[0]);
        return 1;
    }

    Grafo grafo;
    carregar_grafo_binario(&grafo, argv[1]);

    char origem, destino;

    printf("Digite o ponto de origem: ");
    scanf(" %c", &origem);  
    printf("Digite o ponto de destino: ");
    scanf(" %c", &destino);  

    dijkstra(&grafo, origem, destino);

    free(grafo.pontos);
    free(grafo.vizinhos);

    return 0;
}
