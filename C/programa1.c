#include "grafo.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Uso: %s <pontos.txt> <vizinhos.txt> <grafo.bin>\n", argv[0]);
        return 1;
    }

    Grafo grafo;
    ler_pontos(&grafo, argv[1]);
    printf("Pontos lidos:\n");
    for (int i = 0; i < grafo.num_pontos; i++) {
        printf("Ponto %c: (%.2f, %.2f) - %s e %s\n",
               grafo.pontos[i].id, grafo.pontos[i].x, grafo.pontos[i].y,
               grafo.pontos[i].rua1, grafo.pontos[i].rua2);
    }

    ler_vizinhos(&grafo, argv[2]);
    printf("Vizinhos lidos:\n");
    for (int i = 0; i < grafo.num_vizinhos; i++) {
        printf("Vizinho: %c -> %c (%s, %.2f)\n",
               grafo.vizinhos[i].origem, grafo.vizinhos[i].destino,
               grafo.vizinhos[i].rua, grafo.vizinhos[i].distancia);
    }

    salvar_grafo_binario(&grafo, argv[3]);

    printf("Grafo salvo em %s com sucesso!\n", argv[3]);

    // Libere a memória após o uso
    free(grafo.pontos);
    free(grafo.vizinhos);

    return 0;
}
