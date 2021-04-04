#include "controller.h"

//Controller::Controller(sem_t s[7], sem_t mtx[3])
Controller::Controller(sem_t s[7], pthread_mutex_t mtx[3])
{
    for(int i=0;i<7;i++){
        this->s[i] = s[i];
    }
    for(int i=0;i<3;i++){
        this->mtx[i] = mtx[i];
    }
}
