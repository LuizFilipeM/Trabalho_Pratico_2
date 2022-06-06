#include "Grafo.h"


grafo* registro_de_grafo(int altura, int largura, FILE *file,  grafo* matriz){
    //**FUNÇAO REGISTRO de dados*****
        int  valor, n = 0, cont = 1;
        char leitor[500];
        matriz = ( grafo*) malloc((largura * altura) * sizeof( grafo));
        matriz[n].V.R = 0;
        matriz[n].V.G = 0;
        matriz[n].V.B = 0;

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
                        matriz[n].V.Intensidade = 0.30 * matriz[n].V.R + 0.59 * matriz[n].V.G + 0.11 * matriz[n].V.B;
                        if(n == (altura * largura) - 1){
                            break;
                        }
                        if(n < (altura * largura) - 1){
                            cont = 1;
                            n++;
                            matriz[n].V.R = 0;
                            matriz[n].V.G = 0;
                            matriz[n].V.B = 0;

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
                                matriz[n].V.R = matriz[n].V.R * 10 + valor;
                                break;
                            case 2:
                                matriz[n].V.G = matriz[n].V.G * 10 + valor;
                                break;
                            case 3:
                                matriz[n].V.B = matriz[n].V.B * 10 + valor;
                                break;
                        }
                    }
                }
            }
            cont++; //avanca o registro entre R, G e B
            if(cont > 3){
                cont = 1;
                matriz[n].V.Intensidade = 0.30 * matriz[n].V.R + 0.59 * matriz[n].V.G + 0.11 * matriz[n].V.B;
            }
            
            //avança uma linha na matriz e reinicia o contador da coluna da matriz
            if(n < (altura * largura) - 1){
                cont = 1;
                n++;
                matriz[n].V.R = 0;
                matriz[n].V.G = 0;
                matriz[n].V.B = 0;
            }
        }
        apontador_de_grafo(altura, largura, matriz);

        return matriz;
}

//relaiza o apontamento dos vertices adjacentes de cada vertice do grafo
void apontador_de_grafo(int altura, int largura,  grafo* matriz){
    int n = 0;
    matriz[n].A[0] = &matriz[n];
    matriz[n].A[1] = &matriz[n];
    matriz[n].A[2] = &matriz[n + 1];
    matriz[n].A[3] = &matriz[n];
    matriz[n].A[4] = &matriz[n + 1];
    matriz[n].A[5] = &matriz[n + largura];
    matriz[n].A[6] = &matriz[n + largura];
    matriz[n].A[7] = &matriz[n + largura + 1];
    n++;
    for(n; n < largura - 1; n++){
        matriz[n].A[0] = &matriz[n - 1];
        matriz[n].A[1] = &matriz[n];
        matriz[n].A[2] = &matriz[n + 1];
        matriz[n].A[3] = &matriz[n - 1];
        matriz[n].A[4] = &matriz[n + 1];
        matriz[n].A[5] = &matriz[n + largura - 1];
        matriz[n].A[6] = &matriz[n + largura];
        matriz[n].A[7] = &matriz[n + largura + 1];
    }
    matriz[n].A[0] = &matriz[n - 1];
    matriz[n].A[1] = &matriz[n];
    matriz[n].A[2] = &matriz[n];
    matriz[n].A[3] = &matriz[n - 1];
    matriz[n].A[4] = &matriz[n];
    matriz[n].A[5] = &matriz[n + largura - 1];
    matriz[n].A[6] = &matriz[n + largura];
    matriz[n].A[7] = &matriz[n + largura];
    n++;
    for(n ; n < ((altura*largura) - largura - 1);){
        matriz[n].A[0] = &matriz[n - largura];
        matriz[n].A[1] = &matriz[n - largura];
        matriz[n].A[2] = &matriz[n - largura + 1];
        matriz[n].A[3] = &matriz[n];
        matriz[n].A[4] = &matriz[n + 1];
        matriz[n].A[5] = &matriz[n + largura];
        matriz[n].A[6] = &matriz[n + largura];
        matriz[n].A[7] = &matriz[n + largura + 1];
        n++;
        for(n; ((n+1)%largura) != 0; n++){
            matriz[n].A[0] = &matriz[n - largura - 1];
            matriz[n].A[1] = &matriz[n - largura];
            matriz[n].A[2] = &matriz[n - largura + 1];
            matriz[n].A[3] = &matriz[n - 1];
            matriz[n].A[4] = &matriz[n + 1];
            matriz[n].A[5] = &matriz[n + largura - 1];
            matriz[n].A[6] = &matriz[n + largura];
            matriz[n].A[7] = &matriz[n + largura + 1];
        }
        matriz[n].A[0] = &matriz[n - largura - 1];
        matriz[n].A[1] = &matriz[n - largura];
        matriz[n].A[2] = &matriz[n - largura];
        matriz[n].A[3] = &matriz[n - 1];
        matriz[n].A[4] = &matriz[n];
        matriz[n].A[5] = &matriz[n + largura - 1];
        matriz[n].A[6] = &matriz[n + largura];
        matriz[n].A[7] = &matriz[n + largura];
        n++;
    }
    matriz[n].A[0] = &matriz[n - largura];
    matriz[n].A[1] = &matriz[n - largura];
    matriz[n].A[2] = &matriz[n - largura + 1];
    matriz[n].A[3] = &matriz[n];
    matriz[n].A[4] = &matriz[n + 1];
    matriz[n].A[5] = &matriz[n];
    matriz[n].A[6] = &matriz[n];
    matriz[n].A[7] = &matriz[n + 1];
    n++;
    for(n; ((n+1)%largura) != 0; n++){
        matriz[n].A[0] = &matriz[n - largura - 1];
        matriz[n].A[1] = &matriz[n - largura];
        matriz[n].A[2] = &matriz[n - largura + 1];
        matriz[n].A[3] = &matriz[n - 1];
        matriz[n].A[4] = &matriz[n + 1];
        matriz[n].A[5] = &matriz[n - 1];
        matriz[n].A[6] = &matriz[n];
        matriz[n].A[7] = &matriz[n + 1];
    }
    matriz[n].A[0] = &matriz[n - largura - 1];
    matriz[n].A[1] = &matriz[n - largura];
    matriz[n].A[2] = &matriz[n - largura];
    matriz[n].A[3] = &matriz[n - 1];
    matriz[n].A[4] = &matriz[n];
    matriz[n].A[5] = &matriz[n + largura];
    matriz[n].A[6] = &matriz[n];
    matriz[n].A[7] = &matriz[n];
}

//libera a memória anteriormente alocada pelo grafo
void limpeza_de_grafo(int altura, int largura,  grafo* matriz){
    //Libera a memória alocada pelo grafo
    free(matriz);
}

//Remove uma coluna da imagem, pelo tipo grafo 
void remocao_de_grafo(int largura, int altura,  grafo* matriz){
    int x = 0, y = 0, x_aux, direcao, cont;
    double min = 1000000000;
    for(x; x < largura; x++){
        if(min > matriz[x].V.Caminho){
            x_aux = x;
            min = matriz[x].V.Caminho;
        }
    }
    
    for(y; y < altura; y++){
        direcao = matriz[x_aux].V.Direcao;

        for(x = x_aux; (x+1)%largura != 0; x++){
            matriz[x].V = matriz[x+1].V;
        }
        if(y < altura - 1){

        switch(direcao){
            case 1:
                x_aux = x_aux + largura - 1;
            break;
            case 2:
                x_aux = x_aux + largura;
            break;
            case 3:
                x_aux = x_aux + largura + 1;
            break;
        }
        }
    }
    x = largura - 2;
    for(y = 1; (largura*altura)-(largura-1)*(y+1) >= altura; y++){
        for(cont = 1; cont < largura; cont++){
            matriz[x + cont].V = matriz[x + cont +y].V;
        }
        x = x+cont - 1;
    }
    largura--;
    apontador_de_grafo(altura, largura, matriz);
}

//grava os dados finais em um arquivo do tipo .ppm
void gravador_de_grafo(int altura, int largura,  grafo* matriz){
    FILE *file = fopen("saida.ppm", "w");
    int i = 0, cont;
    fprintf(file, "P3\n");
    fprintf(file, "%d %d\n", largura, altura);
    fprintf(file, "255\n");
    for(int y = 0; y < altura; y++){
        for(cont = 0; cont < largura; cont++){
            fprintf(file, "%d %d %d ", matriz[i + cont].V.R, matriz[i + cont].V.G, matriz[i + cont].V.B);
            }
        i+= cont;
        fprintf(file, "\n");
        }
    fclose(file);
}

//calcula as energis de cada vertice e os caminhos
void calculador_de_grafo(int altura, int largura,  grafo* matriz, int operador){
    int y;
    y = (altura * largura) - 1;
    
    if(operador == 0){
    for(y; y >= ((altura * largura) - largura); y--){
        matriz[y].V.Energia =  Operador_de_Sobel(matriz[y].A[0]->V.Intensidade, matriz[y].A[1]->V.Intensidade, matriz[y].A[2]->V.Intensidade, matriz[y].A[3]->V.Intensidade, matriz[y].A[4]->V.Intensidade, matriz[y].A[3]->V.Intensidade, matriz[y].V.Intensidade, matriz[y].A[4]->V.Intensidade);
        matriz[y].V.Caminho = matriz[y].V.Energia;
        
    }
    for(y; y >= largura - 1;){
        matriz[y].V.Energia =  Operador_de_Sobel(matriz[y].A[0]->V.Intensidade, matriz[y].A[1]->V.Intensidade, matriz[y].A[2]->V.Intensidade, matriz[y].A[3]->V.Intensidade, matriz[y].A[4]->V.Intensidade, matriz[y].A[5]->V.Intensidade, matriz[y].A[6]->V.Intensidade, matriz[y].A[7]->V.Intensidade);
        matriz[y].V = calculador_de_caminho(matriz[y].A[5]->V.Caminho, matriz[y].A[6]->V.Caminho, -1, matriz[y].V);
        y--;

        for(y; (y+1)%largura != 1; y--){
            matriz[y].V.Energia =  Operador_de_Sobel(matriz[y].A[0]->V.Intensidade, matriz[y].A[1]->V.Intensidade, matriz[y].A[2]->V.Intensidade, matriz[y].A[3]->V.Intensidade, matriz[y].A[4]->V.Intensidade, matriz[y].A[5]->V.Intensidade, matriz[y].A[6]->V.Intensidade, matriz[y].A[7]->V.Intensidade);
            matriz[y].V = calculador_de_caminho(matriz[y].A[5]->V.Caminho, matriz[y].A[6]->V.Caminho, matriz[y].A[7]->V.Caminho, matriz[y].V);
        }

        matriz[y].V.Energia =  Operador_de_Sobel(matriz[y].A[0]->V.Intensidade, matriz[y].A[1]->V.Intensidade, matriz[y].A[2]->V.Intensidade, matriz[y].A[3]->V.Intensidade, matriz[y].A[4]->V.Intensidade, matriz[y].A[5]->V.Intensidade, matriz[y].A[6]->V.Intensidade, matriz[y].A[7]->V.Intensidade);
        matriz[y].V = calculador_de_caminho(-1, matriz[y].A[6]->V.Caminho, matriz[y].A[7]->V.Caminho, matriz[y].V);
        if(y == 20){
            printf("%.2f -- %.2f\n", matriz[y].V.Energia, matriz[y].V.Caminho);
            printf("%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",matriz[y].A[0]->V.Intensidade, matriz[y].A[1]->V.Intensidade, matriz[y].A[2]->V.Intensidade, matriz[y].A[3]->V.Intensidade, matriz[y].A[4]->V.Intensidade, matriz[y].A[5]->V.Intensidade, matriz[y].A[6]->V.Intensidade, matriz[y].A[7]->V.Intensidade);
        }
        y--;
    }
    }
    if(operador == 1){
        for(y; y >= ((altura * largura) - largura); y--){
        matriz[y].V.Energia =  Operador_de_Prewwit(matriz[y].A[0]->V.Intensidade, matriz[y].A[1]->V.Intensidade, matriz[y].A[2]->V.Intensidade, matriz[y].A[3]->V.Intensidade, matriz[y].A[4]->V.Intensidade, matriz[y].A[3]->V.Intensidade, matriz[y].V.Intensidade, matriz[y].A[4]->V.Intensidade);
        matriz[y].V.Caminho = matriz[y].V.Energia;
        
    }
    for(y; y >= largura - 1;){
        matriz[y].V.Energia =  Operador_de_Prewwit(matriz[y].A[0]->V.Intensidade, matriz[y].A[1]->V.Intensidade, matriz[y].A[2]->V.Intensidade, matriz[y].A[3]->V.Intensidade, matriz[y].A[4]->V.Intensidade, matriz[y].A[5]->V.Intensidade, matriz[y].A[6]->V.Intensidade, matriz[y].A[7]->V.Intensidade);
        matriz[y].V = calculador_de_caminho(matriz[y].A[5]->V.Caminho, matriz[y].A[6]->V.Caminho, -1, matriz[y].V);
        y--;

        for(y; (y+1)%largura != 1; y--){
            matriz[y].V.Energia =  Operador_de_Prewwit(matriz[y].A[0]->V.Intensidade, matriz[y].A[1]->V.Intensidade, matriz[y].A[2]->V.Intensidade, matriz[y].A[3]->V.Intensidade, matriz[y].A[4]->V.Intensidade, matriz[y].A[5]->V.Intensidade, matriz[y].A[6]->V.Intensidade, matriz[y].A[7]->V.Intensidade);
            matriz[y].V = calculador_de_caminho(matriz[y].A[5]->V.Caminho, matriz[y].A[6]->V.Caminho, matriz[y].A[7]->V.Caminho, matriz[y].V);
        }

        matriz[y].V.Energia =  Operador_de_Prewwit(matriz[y].A[0]->V.Intensidade, matriz[y].A[1]->V.Intensidade, matriz[y].A[2]->V.Intensidade, matriz[y].A[3]->V.Intensidade, matriz[y].A[4]->V.Intensidade, matriz[y].A[5]->V.Intensidade, matriz[y].A[6]->V.Intensidade, matriz[y].A[7]->V.Intensidade);
        matriz[y].V = calculador_de_caminho(-1, matriz[y].A[6]->V.Caminho, matriz[y].A[7]->V.Caminho, matriz[y].V);
        if(y == 20){
            printf("%.2f -- %.2f\n", matriz[y].V.Energia, matriz[y].V.Caminho);
            printf("%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",matriz[y].A[0]->V.Intensidade, matriz[y].A[1]->V.Intensidade, matriz[y].A[2]->V.Intensidade, matriz[y].A[3]->V.Intensidade, matriz[y].A[4]->V.Intensidade, matriz[y].A[5]->V.Intensidade, matriz[y].A[6]->V.Intensidade, matriz[y].A[7]->V.Intensidade);
        }
        y--;
    }
    }
}

//transpoe o grafo
grafo* transpor_de_grafo(int altura, int largura, grafo* grafo1){
    grafo *grafo2;
    grafo2 = (grafo*) malloc((largura * altura) * sizeof( grafo));
    int n = 0;
    for (int i = 0; i < altura; i++){
        for(int j = 0; j < largura; j++){
        grafo2[i + j*altura] = grafo1[n];
        n++;
        }
    }
    for(int i =0; i < (largura * altura); i++){
        grafo1[i] = grafo2[i];
    }
    free(grafo2);
    return grafo1;
}

//retorna a energia do menor caminho
int menorcaminhoGrafo(int largura, grafo* matriz){
    double min = 1000000000;
    for(int x = 0; x < largura; x++){
        if(min > matriz[x].V.Caminho){
            min = matriz[x].V.Caminho;
        }
    }
    return min;
}
