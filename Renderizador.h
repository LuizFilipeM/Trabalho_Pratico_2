#include "Renderizador.h"


//registra os dados da imagem passada em uma matriz dinâmica
pixel** registro_de_matriz_dinamica(int altura, int largura, FILE *file, pixel** matriz){
    //**FUNÇAO REGISTRO*****
        int  valor, n = 0, m = 0, cont = 1;
        char leitor[500];
        matriz = (pixel**) malloc(altura * sizeof(pixel*));
        matriz[n] = (pixel*) malloc(largura * sizeof(pixel));
        matriz[n][m].R = 0;
        matriz[n][m].G = 0;
        matriz[n][m].B = 0;

        //percorre a linha em busca dos valores de R, G e B
        while(fgets(leitor, 500, file) != NULL){

            for(int i = 0; i < 500; i++){

                if((leitor[i] == '#') || (leitor[i] == '\n') || (leitor[i] == '\0')){
                    break; //para a busca na linha
                }
                else{
                    if((leitor[i-1] == ' ') && (leitor[i]) != ' '){
                        cont++;
                    }
                    if(cont > 3){
                        matriz[n][m].Intensidade = 0.30 * matriz[n][m].R + 0.59 * matriz[n][m].G + 0.11 * matriz[n][m].B;
                        if((n == altura - 1) && (m == largura - 1)){
                            break;
                        }
                        if((m == largura-1) && (n < altura - 1)){
                            cont = 1;
                            m = 0;
                            n++;
                            matriz[n] = (pixel*) malloc(largura * sizeof(pixel));
                            matriz[n][m].R = 0;
                            matriz[n][m].G = 0;
                            matriz[n][m].B = 0;
                        }
                        else{
                            m++; //avança uma coluna na matriz
                            matriz[n][m].R = 0;
                            matriz[n][m].G = 0;
                            matriz[n][m].B = 0;
                        }
                        cont = 1;
                    }
                    if(leitor[i] != ' '){
                        if(leitor[i] == '0'){
                            valor = 0;
                        }
                        if(leitor[i] == '1'){
                            valor = 1;
                        }
                        if(leitor[i] == '2'){
                            valor = 2;
                        }
                        if(leitor[i] == '3'){
                            valor = 3;
                        }
                        if(leitor[i] == '4'){
                            valor = 4;
                        }
                        if(leitor[i] == '5'){
                            valor = 5;
                        }
                        if(leitor[i] == '6'){
                            valor = 6;
                        }
                        if(leitor[i] == '7'){
                            valor = 7;
                        }
                        if(leitor[i] == '8'){
                            valor = 8;
                        }
                        if(leitor[i] == '9'){
                            valor = 9;
                        }
                        switch (cont){
                            case 1:
                                matriz[n][m].R = matriz[n][m].R * 10 + valor;
                                break;
                            case 2:
                                matriz[n][m].G = matriz[n][m].G * 10 + valor;
                                break;
                            case 3:
                                matriz[n][m].B = matriz[n][m].B * 10 + valor;
                                break;
                        }
                    }
                }
            }

            cont++; //avanca o registro entre R, G e B

            if(cont > 3){
                matriz[n][m].Intensidade = 0.30 * matriz[n][m].R + 0.59 * matriz[n][m].G + 0.11 * matriz[n][m].B;
                if((n == altura - 1) && (m == largura - 1)){
                break;
            }
            }
            
            //avança uma linha na matriz e reinicia o contador da coluna da matriz
            if((m == largura-1) && (n < altura - 1)){
                cont = 1;
                m = 0;
                n++;
                matriz[n] = (pixel*) malloc(largura * sizeof(pixel));
                matriz[n][m].R = 0;
                matriz[n][m].G = 0;
                matriz[n][m].B = 0;
            }
        }
        return matriz;
}

//libera os dados anteriormente alocados na memória
void limpeza_de_matriz_dinamica(int altura, pixel** matriz){
    //***FUNCAO LIMPEZA****
    for(int i = 0; i < altura; i++){
        free(matriz[i]);
    }
    free(matriz);
}

//realiza a remoção do melhor caminho
void remocao_de_matriz_dinamica(int largura, int altura, pixel** matriz){
    //***FUNCAO REMOCAO****
    int x = 0, y = 0, x_aux, direcao;
    double min = 1000000000;
    for(x; x < largura; x++){
        if(min > matriz[y][x].Caminho){
            x_aux = x;
            min = matriz[y][x].Caminho;
        }
    }
    
    for(y; y < altura; y++){
        direcao = matriz[y][x_aux].Direcao;

        for(x = x_aux; x < largura - 1; x++){
            matriz[y][x] = matriz[y][x+1];
        }
        if(y < altura - 1){
            switch(direcao){
                case 1:
                    x_aux = x_aux - 1;
                break;
                case 2:
                    x_aux = x_aux;
                break;
                case 3:
                    x_aux = x_aux + 1;
                break;
            }
        }
    }
}

//calcula a relevância de um pixel baseado no operador de Sobel
float Operador_de_Sobel(float sup_esq, float sup, float sup_dir, float esq, float dir, float inf_esq, float inf, float inf_dir){
    float mascara_x, mascara_y, energia_do_pixel;
    mascara_x = (1 * sup_esq) + (-1 * sup_dir) + (2 * esq) + (-2 * dir) + (1 * inf_esq) + (-1 * inf_dir); 
    mascara_y = (1 * sup_esq) + (2 * sup) + (1 * sup_dir) + (-1 * inf_esq) + (-2 * inf) + (-1 * inf_dir);
    mascara_x = (mascara_x * mascara_x);
    mascara_y = (mascara_y * mascara_y);
    energia_do_pixel = (mascara_x) + (mascara_y);
    energia_do_pixel = sqrtf(energia_do_pixel);
    return energia_do_pixel;
}

//calcula a relevância de um pixel baseado no operador de Prewwit
float Operador_de_Prewwit(float sup_esq, float sup, float sup_dir, float esq, float dir, float inf_esq, float inf, float inf_dir){
    float mascara_x, mascara_y, energia_do_pixel;
    mascara_x = (-1 * sup_esq) + (1 * sup_dir) + (-1 * esq) + (1 * dir) + (-1 * inf_esq) + (1 * inf_dir); 
    mascara_y = (-1 * sup_esq) + (-1 * sup) + (-1 * sup_dir) + (1 * inf_esq) + (1 * inf) + (1 * inf_dir);
    mascara_x = (mascara_x * mascara_x);
    mascara_y = (mascara_y * mascara_y);
    energia_do_pixel = (mascara_x) + (mascara_y);
    energia_do_pixel = sqrtf(energia_do_pixel);
    return energia_do_pixel;
}

//registra em um arquivo .ppm os resultados da remoção
void gravador_de_matriz_dinamica(int altura, int largura, pixel** matriz){
    FILE *file = fopen("saida.ppm", "w");
    fprintf(file, "P3\n");
    fprintf(file, "%d %d\n", largura, altura);
    fprintf(file, "255\n");
    for(int i = 0; i < altura; i++){
        for(int j = 0; j < largura; j++){
            fprintf(file, "%d %d %d ", matriz[i][j].R, matriz[i][j].G, matriz[i][j].B);
        }
        fprintf(file, "\n");
    }
    fclose(file);

}

//calcula as energias de cada pixel, e os caminhos
void calculador_de_matriz_dinamica(int altura, int largura, pixel** matriz, int operador){
    int x = 0, y = 0;
    y = altura - 1;
    
    if(operador == 0){
    //***INFERIOR
    //inferior lateral esquerdo
    matriz[y][x].Energia =  Operador_de_Sobel(matriz[y - 1][x].Intensidade, matriz[y - 1][x].Intensidade, matriz[y - 1][x + 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade);
    matriz[y][x].Caminho = matriz[y][x].Energia;
    x++;
    for(x ; x < largura - 1; x++){
        //inferior meio
        matriz[y][x].Energia =  Operador_de_Sobel(matriz[y - 1][x - 1].Intensidade, matriz[y - 1][x].Intensidade, matriz[y - 1][x + 1].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x + 1].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade);
        matriz[y][x].Caminho = matriz[y][x].Energia;
    }
    //inferior lateral direito
    matriz[y][x].Energia =  Operador_de_Sobel(matriz[y - 1][x - 1].Intensidade, matriz[y - 1][x].Intensidade, matriz[y - 1][x].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x].Intensidade);
    matriz[y][x].Caminho = matriz[y][x].Energia;
    y--;
    x = 0;

    //***MEIO
    for(y; y > 0; y--){
        //meio lateral esquerdo
        matriz[y][x].Energia =  Operador_de_Sobel(matriz[y - 1][x].Intensidade, matriz[y - 1][x].Intensidade, matriz[y - 1][x + 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x + 1].Intensidade);
        matriz[y][x] = calculador_de_caminho(-1, matriz[y + 1][x].Caminho, matriz[y + 1][x + 1].Caminho, matriz[y][x]);
        x++;
        for(x ; x < largura - 1; x++){
            //meio
            matriz[y][x].Energia =  Operador_de_Sobel(matriz[y - 1][x - 1].Intensidade, matriz[y - 1][x].Intensidade, matriz[y - 1][x + 1].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x + 1].Intensidade, matriz[y + 1][x - 1].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x + 1].Intensidade);
            matriz[y][x] = calculador_de_caminho(matriz[y + 1][x - 1].Caminho, matriz[y + 1][x].Caminho, matriz[y + 1][x + 1].Caminho, matriz[y][x]);
        }
        //meio lateral direito
        matriz[y][x].Energia =  Operador_de_Sobel(matriz[y - 1][x - 1].Intensidade, matriz[y - 1][x].Intensidade, matriz[y - 1][x].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x].Intensidade, matriz[y + 1][x - 1].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x].Intensidade);
        matriz[y][x] = calculador_de_caminho(matriz[y + 1][x - 1].Caminho, matriz[y + 1][x].Caminho, -1, matriz[y][x]);
        x = 0;
    }

    //***SUPERIOR
    //superior lateral esquerdo
    matriz[y][x].Energia =  Operador_de_Sobel(matriz[y][x].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x + 1].Intensidade);
    matriz[y][x] = calculador_de_caminho(-1, matriz[y + 1][x].Caminho, matriz[y + 1][x + 1].Caminho, matriz[y][x]);
    x++;
    for(x ; x < largura - 1; x++){
        //superior meio
        matriz[y][x].Energia =  Operador_de_Sobel(matriz[y][x - 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x + 1].Intensidade, matriz[y + 1][x - 1].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x + 1].Intensidade);
        matriz[y][x] = calculador_de_caminho(matriz[y + 1][x - 1].Caminho, matriz[y + 1][x].Caminho, matriz[y + 1][x + 1].Caminho, matriz[y][x]);
    }
    //superior lateral direito
    matriz[y][x].Energia =  Operador_de_Sobel(matriz[y][x - 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x].Intensidade, matriz[y + 1][x - 1].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x].Intensidade);
    matriz[y][x] = calculador_de_caminho(matriz[y + 1][x - 1].Caminho, matriz[y + 1][x].Caminho, -1, matriz[y][x]);
    }

    if(operador == 1){
      //***INFERIOR
    //inferior lateral esquerdo
    matriz[y][x].Energia =  Operador_de_Prewwit(matriz[y - 1][x].Intensidade, matriz[y - 1][x].Intensidade, matriz[y - 1][x + 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade);
    matriz[y][x].Caminho = matriz[y][x].Energia;
    x++;
    for(x ; x < largura - 1; x++){
        //inferior meio
        matriz[y][x].Energia =  Operador_de_Prewwit(matriz[y - 1][x - 1].Intensidade, matriz[y - 1][x].Intensidade, matriz[y - 1][x + 1].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x + 1].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade);
        matriz[y][x].Caminho = matriz[y][x].Energia;
    }
    //inferior lateral direito
    matriz[y][x].Energia =  Operador_de_Prewwit(matriz[y - 1][x - 1].Intensidade, matriz[y - 1][x].Intensidade, matriz[y - 1][x].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x].Intensidade);
    matriz[y][x].Caminho = matriz[y][x].Energia;
    y--;
    x = 0;

    //***MEIO
    for(y; y > 0; y--){
        //meio lateral esquerdo
        matriz[y][x].Energia =  Operador_de_Prewwit(matriz[y - 1][x].Intensidade, matriz[y - 1][x].Intensidade, matriz[y - 1][x + 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x + 1].Intensidade);
        matriz[y][x] = calculador_de_caminho(-1, matriz[y + 1][x].Caminho, matriz[y + 1][x + 1].Caminho, matriz[y][x]);
        x++;
        for(x ; x < largura - 1; x++){
            //meio
            matriz[y][x].Energia =  Operador_de_Prewwit(matriz[y - 1][x - 1].Intensidade, matriz[y - 1][x].Intensidade, matriz[y - 1][x + 1].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x + 1].Intensidade, matriz[y + 1][x - 1].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x + 1].Intensidade);
            matriz[y][x] = calculador_de_caminho(matriz[y + 1][x - 1].Caminho, matriz[y + 1][x].Caminho, matriz[y + 1][x + 1].Caminho, matriz[y][x]);
        }
        //meio lateral direito
        matriz[y][x].Energia =  Operador_de_Prewwit(matriz[y - 1][x - 1].Intensidade, matriz[y - 1][x].Intensidade, matriz[y - 1][x].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x].Intensidade, matriz[y + 1][x - 1].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x].Intensidade);
        matriz[y][x] = calculador_de_caminho(matriz[y + 1][x - 1].Caminho, matriz[y + 1][x].Caminho, -1, matriz[y][x]);
        x = 0;
    }

    //***SUPERIOR
    //superior lateral esquerdo
    matriz[y][x].Energia =  Operador_de_Prewwit(matriz[y][x].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x + 1].Intensidade);
    matriz[y][x] = calculador_de_caminho(-1, matriz[y + 1][x].Caminho, matriz[y + 1][x + 1].Caminho, matriz[y][x]);
    x++;
    for(x ; x < largura - 1; x++){
        //superior meio
        matriz[y][x].Energia =  Operador_de_Prewwit(matriz[y][x - 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x + 1].Intensidade, matriz[y + 1][x - 1].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x + 1].Intensidade);
        matriz[y][x] = calculador_de_caminho(matriz[y + 1][x - 1].Caminho, matriz[y + 1][x].Caminho, matriz[y + 1][x + 1].Caminho, matriz[y][x]);
    }
    //superior lateral direito
    matriz[y][x].Energia =  Operador_de_Prewwit(matriz[y][x - 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x].Intensidade, matriz[y + 1][x - 1].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x].Intensidade);
    matriz[y][x] = calculador_de_caminho(matriz[y + 1][x - 1].Caminho, matriz[y + 1][x].Caminho, -1, matriz[y][x]);  
    }
}

//calcula o melhor caminho de um pixel para outro
pixel calculador_de_caminho(double esq, double baixo, double dir, pixel elemento){
    double min = 10000000;
    int direcao = 0;
    if(esq != -1){
        if(min > esq){
            min = esq;
            direcao = 1;
        }
    }
    if(baixo != -1){
        if(min > baixo){
            min = baixo;
            direcao = 2;
        }
    }
    if(dir != -1){
        if(min > dir){
            min = dir;
            direcao = 3;
        }
    }
    elemento.Caminho = elemento.Energia + min;
    elemento.Direcao = direcao;
    return elemento;
}

//trasnpoe uma matriz
pixel** transpor_de_matriz_dinamica(int altura, int largura, pixel** matriz){
    pixel** matriz2;
    matriz2 = (pixel**) malloc(largura * sizeof(pixel*));
    for (int i=0; i < largura;i++ ){
        matriz2[i] = (pixel*)malloc(altura * sizeof(pixel));
    }
    

    for(int i = 0; i < largura; i++){
        for(int j = 0; j < altura; j++){

            matriz2[i][j] = matriz[j][i];            

        }   
    }
    for(int i = 0; i < altura; i++) free(matriz[i]);
    free(matriz);
    
    return matriz2;
}

//coleta os parametros passados na execução
int retorna_parametros(int argc, char **argv, parametros *param){
    param->operador = 0;
    param->linhas = 0;
    param->colunas = 0;
    char opt;
    strcpy(param->estrategia, argv[1]);
    strcpy(param->file, argv[2]);
    while((opt = getopt(argc, argv, "h:w:t:")) != -1){
        switch(opt){
            case 'h':
                if(optarg != NULL)
                    param->linhas = atoi(optarg);
            break;
            case 'w':
                if(optarg != NULL)
                    param->colunas = atoi(optarg);
            break;
            case 't':
                param->operador = atoi(optarg);
            break;
            default:
                printf("Tente novamente entrada invalida.\n");
                return 0;
                break;
            break;
        }
    }
    return 1;
}

//retorna a energia do menor caminho
int menorcaminhoDinamica(int largura, pixel** matriz){
    double min = 1000000000;
    int y = 0;
    for(int x = 0; x < largura; x++){
        if(min > matriz[y][x].Caminho){
            min = matriz[y][x].Caminho;
        }
    }
    return min;
}
