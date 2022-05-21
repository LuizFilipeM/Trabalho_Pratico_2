pixel** transpor(int altura, int largura, pixel** matriz){
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
    
    return matriz2;
}
