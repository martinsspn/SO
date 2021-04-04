#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <pthread.h>
#include <semaphore.h>

class Controller
{
public:
    sem_t s[7];
    //sem_t mtx[3];
    pthread_mutex_t mtx[3];
    //Controller(sem_t s[7], sem_t mtx[3]);
    Controller(sem_t s[7], pthread_mutex_t mtx[3]);

};

#endif // CONTROLLER_H
