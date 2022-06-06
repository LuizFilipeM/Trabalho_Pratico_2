#include "Renderizador.h"

typedef struct grafo{
    pixel V;
    struct grafo* A[8];
}grafo;


grafo* registro_de_grafo(int, int, FILE*, grafo*);
void apontador_de_grafo(int, int, grafo*);
void limpeza_de_grafo(int, int,  grafo*);
void remocao_de_grafo(int, int,  grafo*);
void gravador_de_grafo(int, int,  grafo*);
void calculador_de_grafo(int, int,  grafo*, int);
grafo* transpor_de_grafo(int, int, grafo*);
int menorcaminhoGrafo(int, grafo*);
