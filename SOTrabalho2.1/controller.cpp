#include "controller.h"

Controller::Controller(sem_t s[7], sem_t mtx[3])
{
    for(int i=0;i<7;i++){
        count[i] = 0;
        this->s[i] = s[i];
    }
    for(int i=0;i<3;i++){
        this->mtx[i] = mtx[i];
    }
}
