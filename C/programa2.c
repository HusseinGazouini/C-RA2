#include "grafo.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: %s <grafo.bin>\n", argv[0]);
        return 1;
    }

    Grafo grafo;
    carregar_grafo_binario(&grafo, argv[1]);

    // Aqui você pode implementar a lógica para buscar o menor caminho com o algoritmo de Dijkstra.
    // Exemplo de apenas exibir os pontos carregados:

    printf("Pontos carregados:\n");
    for (int i = 0; i < grafo.num_pontos; i++) {
        printf("Ponto %c: (%f, %f), %s, %s\n", grafo.pontos[i].id,
                grafo.pontos[i].x, grafo.pontos[i].y,
                grafo.pontos[i].rua1, grafo.pontos[i].rua2);
    }

    // Libere a memória após o uso
    free(grafo.pontos);
    free(grafo.vizinhos);

    return 0;
}
