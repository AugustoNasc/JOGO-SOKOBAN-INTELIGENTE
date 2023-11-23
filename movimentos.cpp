#include "mapa.hpp"
#include <stdio.h>
#include "movimentos.hpp"
#include "voltajogada.hpp"
#include <iostream>

void troca_vazio(MAPA *mapa, int *x, int *y, int cont1, int cont2, int level, int *ja_andou){

            char aux;
            if ((*mapa).mapa[*y+cont2][*x+cont1] == '@'||(*mapa).mapa[*y+cont2][*x+cont1] == '+'){
                  aux = (*mapa).mapa[*y+cont2][*x+cont1];
                  (*mapa).mapa[*y+cont2][*x+cont1]=(*mapa).mapa[*y][*x];
                  (*mapa).mapa[*y][*x]= aux;
                  *x=*x+cont1; *y=*y+cont2;
                  registrando_jogadas(*mapa, level);
                  *ja_andou=1;
            }
}

void troca_caixa(int *x, int *y, int cont1, int cont2, MAPA *mapa, int level){

  if(*x+2*cont1>=0 && *x+2*cont1<12 && *y+2*cont2>=0 && *y+2*cont2<12){

          if((*mapa).mapa[*y+cont2][*x+cont1] == 'B'){

              if ((*mapa).mapa[*y+2*cont2][*x+2*cont1] == '@'||(*mapa).mapa[*y+2*cont2][*x+2*cont1] == '+'){
                      if((*mapa).especial_atual[*y+2*cont2][*x+2*cont1]==1){
                          (*mapa).especial_atual[*y+2*cont2][*x+2*cont1]=0;
                      }
                      if((*mapa).especial_atual[*y+cont2][*x+cont1]==0){
                          if((*mapa).especial_inicio[*y+cont2][*x+cont1]==1){
                          (*mapa).especial_atual[*y+cont2][*x+cont1]=1;}
                      }
                      (*mapa).mapa[*y+2*cont2][*x+2*cont1]='B';
                      (*mapa).mapa[*y+cont2][*x+cont1]='P';
                      (*mapa).mapa[*y][*x]= '@';
                      *y=*y+cont2;
                      *x=*x+cont1;  
                      registrando_jogadas(*mapa, level);

              }
          }
  }

}

void mover_personagem(int *x,int *y,int gFlag, MAPA *mapa, int level, sf::Clock &clock){
    sf::Time elapsed = clock.getElapsedTime();
    if((*mapa).mapa[*y][*x]=='P'&& elapsed.asSeconds() >= 0.1f){

    int ja_andou=0;
    int cont1, cont2;
    if(gFlag == 1)
    {
      cont1=-1; cont2=0;
      if(*x+cont1>=0 && *x+cont1<12 && *y+cont2>=0 && *y+cont2<12){
        troca_vazio(mapa, x, y, cont1, cont2, level, &ja_andou);}

      if(*x+2*cont1>=0 && *x+2*cont1<12 && *y+2*cont2>=0 && *y+2*cont2<12 && !ja_andou){
        troca_caixa(x, y, cont1, cont2, mapa, level);}


    }
  
    else if(gFlag == 2)
    {
        cont1=1; cont2=0;
      if(*x+cont1>=0 && *x+cont1<12 && *y+cont2>=0 && *y+cont2<12){
        troca_vazio(mapa, x, y, cont1, cont2, level, &ja_andou);}

      if(*x+2*cont1>=0 && *x+2*cont1<12 && *y+2*cont2>=0 && *y+2*cont2<12&& !ja_andou){
        troca_caixa(x, y, cont1, cont2, mapa, level); }


    }
    else if(gFlag == 3)
    {
        cont1=0; cont2=1;
      if(*x+cont1>=0 && *x+cont1<12 && *y+cont2>=0 && *y+cont2<12){
        troca_vazio(mapa, x, y, cont1, cont2, level, &ja_andou); }

     if(*x+2*cont1>=0 && *x+2*cont1<12 && *y+2*cont2>=0 && *y+2*cont2<12&& !ja_andou){
        troca_caixa(x, y, cont1, cont2, mapa, level);}


    }
  
    else if(gFlag == 4)
    {
        cont1=0; cont2=-1;
      if(*x+cont1>=0 && *x+cont1<12 && *y+cont2>=0 && *y+cont2<12){
        troca_vazio(mapa, x, y, cont1, cont2, level, &ja_andou); }

      if(*x+2*cont1>=0 && *x+2*cont1<12 && *y+2*cont2>=0 && *y+2*cont2<12&& !ja_andou){
        troca_caixa(x, y, cont1, cont2, mapa, level);}


    }
    clock.restart();
    }
}