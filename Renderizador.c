#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <getopt.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>

typedef struct pixel{
    int R, G, B, Direcao;
   float Intensidade, Energia;
    double Caminho;
} pixel;


typedef struct parametros{
    int linhas, colunas, operador;
    char estrategia[2], file[60];
} parametros;



pixel** registro_de_matriz_dinamica(int ,int ,FILE* , pixel**);
void limpeza_de_matriz_dinamica(int , pixel**);
void remocao_de_matriz_dinamica(int , int, pixel**);
float Operador_de_Sobel(float, float, float, float, float, float, float, float);
float Operador_de_Prewwit(float, float, float, float, float, float, float, float);
void gravador_de_matriz_dinamica(int, int, pixel**);
void calculador_de_matriz_dinamica(int, int, pixel**, int);
pixel calculador_de_caminho(double, double, double, pixel);
pixel** transpor_de_matriz_dinamica(int, int, pixel**);
int menorcaminhoDinamica(int, pixel**);
int retorna_parametros(int, char**, parametros*);
//funções para medir o tempo
float diffUserTime(struct rusage *, struct rusage *);
float diffSystemTime(struct rusage *, struct rusage *);
