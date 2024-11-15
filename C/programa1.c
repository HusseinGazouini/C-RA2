#include "grafo.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Uso: %s <pontos.txt> <vizinhos.txt> <grafo.bin>\n", argv[0]);
        return 1;
    }

    Grafo grafo;
    ler_pontos(&grafo, argv[1]);
    ler_vizinhos(&grafo, argv[2]);
    salvar_grafo_binario(&grafo, argv[3]);

    printf("Grafo salvo em %s com sucesso!\n", argv[3]);

    // Libere a memória após o uso
    free(grafo.pontos);
    free(grafo.vizinhos);

    return 0;
}
