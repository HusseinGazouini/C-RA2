#include "grafo.h"

// Função para calcular a distância entre dois pontos
float calcular_distancia(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Função para ler os pontos do arquivo de texto
void ler_pontos(Grafo* grafo, const char* arquivo_pontos) {
    FILE* fp = fopen(arquivo_pontos, "r");
    if (!fp) {
        perror("Erro ao abrir arquivo de pontos");
        exit(1);
    }

    fscanf(fp, "%d", &grafo->num_pontos);  // Lê o número de pontos
    grafo->pontos = (Ponto*)malloc(grafo->num_pontos * sizeof(Ponto));

    for (int i = 0; i < grafo->num_pontos; i++) {
        fscanf(fp, " %c", &grafo->pontos[i].id);
        fscanf(fp, "%f %f", &grafo->pontos[i].x, &grafo->pontos[i].y);
        fscanf(fp, " %[^\n]", grafo->pontos[i].rua1);
        fscanf(fp, " %[^\n]", grafo->pontos[i].rua2);
    }

    fclose(fp);
}

// Função para ler os vizinhos do arquivo de texto
void ler_vizinhos(Grafo* grafo, const char* arquivo_vizinhos) {
    FILE* fp = fopen(arquivo_vizinhos, "r");
    if (!fp) {
        perror("Erro ao abrir arquivo de vizinhos");
        exit(1);
    }

    fscanf(fp, "%d", &grafo->num_vizinhos);  // Lê o número de vizinhos
    grafo->vizinhos = (Vizinho*)malloc(grafo->num_vizinhos * sizeof(Vizinho));

    for (int i = 0; i < grafo->num_vizinhos; i++) {
        char origem, destino;
        fscanf(fp, " %c %c", &origem, &destino);
        fscanf(fp, " %[^\n]", grafo->vizinhos[i].rua);

        Ponto* ponto_origem = NULL;
        Ponto* ponto_destino = NULL;

        for (int j = 0; j < grafo->num_pontos; j++) {
            if (grafo->pontos[j].id == origem) ponto_origem = &grafo->pontos[j];
            if (grafo->pontos[j].id == destino) ponto_destino = &grafo->pontos[j];
        }

        if (ponto_origem && ponto_destino) {
            grafo->vizinhos[i].origem = origem;
            grafo->vizinhos[i].destino = destino;
            grafo->vizinhos[i].distancia = calcular_distancia(
                ponto_origem->x, ponto_origem->y, ponto_destino->x, ponto_destino->y
            );
        }
    }

    fclose(fp);
}

// Função para salvar o grafo em um arquivo binário
void salvar_grafo_binario(Grafo* grafo, const char* arquivo_saida) {
    FILE* fp = fopen(arquivo_saida, "wb");
    if (!fp) {
        perror("Erro ao abrir arquivo binário");
        exit(1);
    }

    fwrite(&grafo->num_pontos, sizeof(int), 1, fp);
    fwrite(&grafo->num_vizinhos, sizeof(int), 1, fp);
    fwrite(grafo->pontos, sizeof(Ponto), grafo->num_pontos, fp);
    fwrite(grafo->vizinhos, sizeof(Vizinho), grafo->num_vizinhos, fp);

    fclose(fp);
}

// Função para carregar o grafo a partir de um arquivo binário
void carregar_grafo_binario(Grafo* grafo, const char* arquivo_entrada) {
    FILE* fp = fopen(arquivo_entrada, "rb");
    if (!fp) {
        perror("Erro ao abrir arquivo binário");
        exit(1);
    }

    fread(&grafo->num_pontos, sizeof(int), 1, fp);
    fread(&grafo->num_vizinhos, sizeof(int), 1, fp);

    grafo->pontos = (Ponto*)malloc(grafo->num_pontos * sizeof(Ponto));
    grafo->vizinhos = (Vizinho*)malloc(grafo->num_vizinhos * sizeof(Vizinho));

    fread(grafo->pontos, sizeof(Ponto), grafo->num_pontos, fp);
    fread(grafo->vizinhos, sizeof(Vizinho), grafo->num_vizinhos, fp);

    fclose(fp);
}
