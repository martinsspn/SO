#include "trem.h"
#include <QtCore>
#include <semaphore.h>

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1
            if (y == 30 && x <330)
                x+=10;
            else if (x == 330 && y < 150)
                //Região Crítica
                y+=10;
            else if (x > 60 && y == 150){
                if(x >= 190){
                    //Região Crítica
                }
                x-=10;
            }else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if (y == 30 && x <600)
                x+=10;
            else if (x == 600 && y < 150)
                //Região Crítica
                y+=10;
            else if (x > 330 && y == 150){
                if(x <= 460){
                    //Região Crítica
                }
                x-=10;
            }else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if (y == 30 && x <870)
                x+=10;
            else if (x == 870 && y < 150)
                y+=10;
            else if (x > 600 && y == 150){
                if(x <= 730){
                    //Região Crítica
                }
                x-=10;
            }else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            if (y == 150 && x <730)
                x+=10;
            else if (x == 730 && y < 270)
                y+=10;
            else if (x > 460 && y == 270)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if (y == 150 && x <460)
                x+=10;
            else if (x == 460 && y < 270)
                //Região Crítica
                y+=10;
            else if (x > 190 && y == 270)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        default:/*Regiões Críticas:
                1 - x = (190,460) y = 150
                2 - x = 330 y = (30, 150)
                3 - x = (460, 730) y = 150
                4 - x = 600 y = (30, 150)
                5 - x = 460 y = (150, 270)*/
            break;
        }
        msleep(velocidade);
    }
}




