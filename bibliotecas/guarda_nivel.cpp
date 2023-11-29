#include "guarda_nivel.hpp"
#include <stdio.h>
#include <queue>

void salvar_nivel(int level){
    int nivel_guardado;
    FILE *arq = fopen("jogadas/niveis_salvos.txt", "a+");
    while(fscanf(arq, "%d", &nivel_guardado) != EOF){
        if(nivel_guardado==level){
            fclose(arq);
            return;
        }
    }
    fprintf(arq, "%d\n", level);
    fclose(arq);
}

int ultimo_nivel_desbloqueado(void){

    int level;
    FILE *arq = fopen("jogadas/niveis_salvos.txt", "rt");
    std::priority_queue<int, std::vector<int>, std::greater<int>> fila;

    while(fscanf(arq, "%d", &level) != EOF){
        fila.push(level);
    }
    
    level=fila.top();
    fclose(arq);

    return level;
}

void atualiza_mapas_acessados(bool mapas[]){
    int level;
    FILE *arq = fopen("jogadas/niveis_salvos.txt", "rt");

    for(int i=0; i<12; i++){
        mapas[i]=false;
    }
    while(fscanf(arq, "%d", &level) != EOF){
        mapas[level-1]=true;
    }
    fclose(arq);

}