#include <stdlib.h>
#include <stdio.h>

struct pixel{
    int r, g, b;
    float intensidade;
};



void main(){
    FILE *img = fopen("papa.ppm", "r");
    if (img == NULL) {printf("Erro ao abrir arquivo"); return;} 

    int dim_x, dim_y, max_brilho, R, G, B;
    char magic[3], *aux1;
    int aux;
    char sharp, lixo[20000];

    fscanf(img," %s %d %d %d", magic, &dim_x, &dim_y, &max_brilho);
    
    struct pixel* matriz[dim_x][dim_y];

    for (int i = 0; i < dim_x; i++){
        
        for (int j = 0; j < dim_y; ){
            //printf("%d ; %d\n", i, j);
            fscanf(img, "%d", &aux);
            fscanf(img, "%c", &sharp);
            if(sharp == '#') {fgets(lixo, 20000, img);}
            
            else {matriz[i][j] = (struct pixel*)malloc(sizeof(struct pixel));
                fscanf(img," %d %d ", &G, &B);
                
                matriz[i][j]->r = aux;
                matriz[i][j]->g = G;
                matriz[i][j]->b = B;
                j++;
                }
        }
    }
    

    fclose(img);
}
