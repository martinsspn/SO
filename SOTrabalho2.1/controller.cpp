#include "controller.h"

Controller::Controller(sem_t s[7], sem_t mtx)
{
    for(int i=0;i<7;i++){
        this->s[i] = s[i];
    }
    this->mtx = mtx;
}
