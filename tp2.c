#include "Grafo.h"




int main(int argc, char *argv[]){
     //uso para medir tempo
    struct rusage start, end;
    getpid();
    getrusage(RUSAGE_SELF, &start);
   



    parametros param;
    char magic_var[2], tipo_de_remocao[3], estrategia[5];
    int altura, largura, aux_de_trans, max_range, energia_linhas, energia_colunas;
    if(retorna_parametros(argc, argv, &param)){
    FILE *file = fopen(param.file, "r");
    if(file == NULL){
        printf("Erro, arquivo não encontrado.\n");
        return 0;
    }
    else{
        if((param.operador != 0) && (param.operador != 1)){
            printf("Tipo de operador invalido\n");
            return 0;
        }
        fscanf(file, "%s", magic_var);
        if(strcmp(magic_var,"P3") != 0) printf("Erro na variavel magica\n");
            fscanf(file, "%d %d", &largura, &altura);
            
            fscanf(file, "%d ", &max_range); 
            if((param.colunas > largura-2) || (param.linhas > altura - 2)){
                printf("Erro, remocao invalida, tente um numero menor");
                return 0;
            } 

        //metodo de memoria dinamica 
        if(param.estrategia[0] == 'D'){
            pixel** matriz;
            matriz = registro_de_matriz_dinamica(altura, largura, file, matriz);
            calculador_de_matriz_dinamica(altura, largura, matriz, param.operador);

            //remoção simultânea
            while((param.colunas != 0) && (param.linhas != 0)){
                //descobre a energia do menor caminho para remoção de colunas
                calculador_de_matriz_dinamica(altura, largura, matriz, param.operador);
                energia_colunas = menorcaminhoDinamica(largura, matriz);
                //descobre a energia do menor caminho para remoção de linhas
                matriz = transpor_de_matriz_dinamica(altura, largura, matriz);
                aux_de_trans = altura;
                altura = largura;
                largura = aux_de_trans;
                calculador_de_matriz_dinamica(altura, largura, matriz, param.operador);
                energia_linhas = menorcaminhoDinamica(largura, matriz);
                //caso seja melhor remover uma linha
                if(energia_colunas >= energia_linhas){
                    remocao_de_matriz_dinamica(largura, altura, matriz);
                    largura--;
                    calculador_de_matriz_dinamica(altura, largura, matriz, param.operador);
                    param.linhas--;
                }
                //caso seja melhor remover uma coluna
                else{
                    matriz = transpor_de_matriz_dinamica(altura, largura, matriz);
                    aux_de_trans = altura;
                    altura = largura;
                    largura = aux_de_trans;
                    calculador_de_matriz_dinamica(altura, largura, matriz, param.operador);
                    remocao_de_matriz_dinamica(largura, altura, matriz);
                    largura--;
                    calculador_de_matriz_dinamica(altura, largura, matriz, param.operador);
                    param.colunas--;
                }
            }

            //remoção de colunas
            while(param.colunas != 0){
                remocao_de_matriz_dinamica(largura, altura, matriz);
                largura--;
                calculador_de_matriz_dinamica(altura, largura, matriz, param.operador);
                param.colunas--;
            }
            
            //remoção de linhas
            if(param.linhas != 0){
                matriz = transpor_de_matriz_dinamica(altura, largura, matriz);
                aux_de_trans = altura;
                altura = largura;
                largura = aux_de_trans;
                calculador_de_matriz_dinamica(altura, largura, matriz, param.operador);

                while(param.linhas != 0){
                    remocao_de_matriz_dinamica(largura, altura, matriz);
                    largura--;
                    calculador_de_matriz_dinamica(altura, largura, matriz, param.operador);
                    param.linhas--;
                }
                
                matriz = transpor_de_matriz_dinamica(altura, largura, matriz);
                aux_de_trans = altura;
                altura = largura;
                largura = aux_de_trans;
            }

            gravador_de_matriz_dinamica(altura, largura, matriz);
            limpeza_de_matriz_dinamica(altura, matriz);
        }
        
        //metodo de grafos
        if(param.estrategia[0] == 'G'){
            grafo* Grafo;
            Grafo = registro_de_grafo(altura, largura, file, Grafo);
            calculador_de_grafo(altura, largura, Grafo, param.operador);

            //remoção simultânea
            while((param.colunas != 0) && (param.linhas != 0)){
                //descobre a energia do menor caminho para remoção de colunas
                calculador_de_grafo(altura, largura, Grafo, param.operador);
                energia_colunas = menorcaminhoGrafo(largura, Grafo);
                //descobre a energia do menor caminho para remoção de linhas
                Grafo = transpor_de_grafo(altura, largura, Grafo);
                aux_de_trans = altura;
                altura = largura;
                largura = aux_de_trans;
                calculador_de_grafo(altura, largura, Grafo, param.operador);
                energia_linhas = menorcaminhoGrafo(largura, Grafo);
                //caso seja melhor remover uma linha
                if(energia_colunas >= energia_linhas){
                    remocao_de_grafo(largura, altura, Grafo);
                    largura--;
                    calculador_de_grafo(altura, largura, Grafo, param.operador);
                    param.linhas--;
                }
                //caso seja melhor remover uma coluna
                else{
                Grafo = transpor_de_grafo(altura, largura, Grafo);
                aux_de_trans = altura;
                altura = largura;
                largura = aux_de_trans;
                calculador_de_grafo(altura, largura, Grafo, param.operador);
                remocao_de_grafo(largura, altura, Grafo);
                largura--;
                calculador_de_grafo(altura, largura, Grafo, param.operador);
                param.colunas--;
                }
            }

            //remoção de colunas
            while(param.colunas != 0){
                remocao_de_grafo(largura, altura, Grafo);
                largura--;
                calculador_de_grafo(altura, largura, Grafo, param.operador);
                param.colunas--;
            }

            //remoção de linhas
            if(param.linhas != 0){
                Grafo = transpor_de_grafo(altura, largura, Grafo);
                aux_de_trans = altura;
                altura = largura;
                largura = aux_de_trans;
                calculador_de_grafo(altura, largura, Grafo, param.operador);
                while(param.linhas != 0){
                    remocao_de_grafo(largura, altura, Grafo);
                    largura--;
                    calculador_de_grafo(altura, largura, Grafo, param.operador);
                    param.linhas--;
                }
                Grafo = transpor_de_grafo(altura, largura, Grafo);
                aux_de_trans = altura;
                altura = largura;
                largura = aux_de_trans;
            }
            gravador_de_grafo(altura, largura, Grafo);
            limpeza_de_grafo(altura, largura, Grafo);
        }
    }
    fclose(file);
    }
    //medição do tempo de execução e exporta para uma tabela
    getrusage(RUSAGE_SELF, &end);
   

    fclose(tmp_csv);
    return 0;
}
