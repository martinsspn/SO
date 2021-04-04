#include "trem.h"
#include <QtCore>
#include <semaphore.h>
#include <pthread.h>
#include "controller.h"
#include <stdio.h>

//Construtor
Trem::Trem(int ID, int x, int y, Controller *controller){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->controller = controller;
    velocidade = 100;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1
            if (y == 30 && x <330){
                if(x==310){
                    //sem_wait(&controller->mtx[1]);
                    pthread_mutex_lock(&controller->mtx[1]);
                    sem_wait(&controller->s[0]);
                }else if(x == 320){
                    
                }
                x+=10;
            }else if (x == 330 && y < 150){
                //Região Crítica
                if(y == 130){
                    sem_wait(&controller->s[2]);
                }
                y+=10;
            }else if (x > 60 && y == 150){
                if(x==170)
                    sem_post(&controller->s[2]);
                else if(x==310){
                    sem_post(&controller->s[0]);
                    //sem_post(&controller->mtx[1]);
                    pthread_mutex_unlock(&controller->mtx[1]);
                }
                x-=10;
            }else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if (y == 30 && x <600){
                if(x == 350){
                    sem_post(&controller->s[0]);
                }else if(x==580){
                    //sem_wait(&controller->mtx[2]);
                    pthread_mutex_lock(&controller->mtx[2]);
                    sem_wait(&controller->s[1]);
                }
                x+=10;
            }else if (x == 600 && y < 150){
                if(y == 130){
                    sem_wait(&controller->s[4]);
                }
                y+=10;
            }else if (x > 330 && y == 150){
                if(x == 350){
                    sem_wait(&controller->s[0]);
                }else if(x == 580){
                    sem_post(&controller->s[1]);
                    //sem_post(&controller->mtx[2]);
                    pthread_mutex_unlock(&controller->mtx[2]);

                }else if(x == 470){

                }else if(x == 480){
                    sem_wait(&controller->s[5]);
                    sem_wait(&controller->s[3]);
                }else if(x == 440){
                    sem_post(&controller->s[4]);
                }else if(x == 600){
                }
                x-=10;
            }else{
                if(y==130){
                    sem_post(&controller->s[5]);
                    sem_post(&controller->s[3]);
                }
                if(x == 330){
                }
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if (y == 30 && x <870){
                if(x==620){
                    sem_post(&controller->s[1]);
                }
                x+=10;
            }else if (x == 870 && y < 150)
                y+=10;
            else if (x > 600 && y == 150){
                if(x == 620){
                    //Região Crítica
                    sem_wait(&controller->s[1]);
                }else if(x == 750){
                    //sem_wait(&controller->mtx[2]);
                    pthread_mutex_lock(&controller->mtx[2]);
                    sem_wait(&controller->s[5]);
                }
                x-=10;
            }else{
                if(y == 130){
                    sem_post(&controller->s[5]);
                    //sem_post(&controller->mtx[2]);
                    pthread_mutex_unlock(&controller->mtx[2]);

                }
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            if (y == 150 && x <730){
                if(x == 480){                   
                    sem_post(&controller->s[6]);
                    //sem_post(&controller->mtx[0]);
                    pthread_mutex_unlock(&controller->mtx[0]);

                }else if(x == 620){
                    sem_post(&controller->s[4]);
                }else if(x == 580){
                    sem_wait(&controller->s[5]);
                }
                x+=10;
            }else if (x == 730 && y < 270){
                if(y == 170){
                    sem_post(&controller->s[5]);
                }
                y+=10;
            }else if (x > 460 && y == 270){
                if(x == 480){
                    //sem_wait(&controller->mtx[0]);
                    pthread_mutex_lock(&controller->mtx[0]);
                    sem_wait(&controller->s[6]);
                }
                x-=10;
            }else{
                if(y == 170){
                    sem_wait(&controller->s[4]);
                }else if(y == 160){
                }
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if (y == 150 && x <460){
                if(x==350){
                    sem_post(&controller->s[2]);
                    //sem_post(&controller->mtx[1]);
                    pthread_mutex_unlock(&controller->mtx[1]);

                }else if(x == 440){
                    sem_wait(&controller->s[6]);
                }else if(x == 310){
                    //sem_wait(&controller->mtx[0]);
                    pthread_mutex_lock(&controller->mtx[0]);
                    sem_wait(&controller->s[3]);
                }
                x+=10;
            }else if (x == 460 && y < 270){
                if(y == 170){
                    sem_post(&controller->s[3]);
                    //sem_post(&controller->mtx[0]);
                    pthread_mutex_unlock(&controller->mtx[0]);

                }
                y+=10;
            }else if (x > 190 && y == 270){
                if(x == 440){
                    sem_post(&controller->s[6]);
                }
                x-=10;
            }else{
                if(y==170){
                    //sem_wait(&controller->mtx[1]);
                    pthread_mutex_lock(&controller->mtx[1]);
                    sem_wait(&controller->s[2]);

                }else if(y == 160){
                }
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        default:/*Regiões Críticas:
                1 - x = (190,460) y = 150
                2 - x = 330 y = (30, 150)
                3 - x = (460, 730) y = 150
                R4 - x = 600 y = (30, 150)
                5 - x = 460 y = (150, 270)*/
            break;
        }
        msleep(velocidade);
    }
};

void Trem::setVelocidade(int value){
    this->velocidade = value;
};




