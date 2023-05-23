#include "fork.hpp"
#include <cassert>

Fork::Fork() {
    // TODO: implement fork constructor (value, mutex, cond)
    // int ret = pthread_mutex_init(&mutex, NULL);
    // if(ret != 0) printf("\n mutex init has failed\n");

    // mutex = PTHREAD_MUTEX_INITIALIZER;
    // cond = PTHREAD_COND_INITIALIZER; 

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    value = 1;
    
}

void Fork::wait() {
    // TODO: implement semaphore wait

    pthread_mutex_lock(&mutex);

    while(value == 0) pthread_cond_wait(&cond, &mutex);
    value--;

    assert(value >= 0);

    pthread_mutex_unlock(&mutex);
}

void Fork::signal() {
    // TODO: implement semaphore signal
    pthread_mutex_lock(&mutex);
    value++;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
}

Fork::~Fork() {
    // TODO: implement fork destructor (mutex, cond)

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}