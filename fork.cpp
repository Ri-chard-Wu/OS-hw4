#include "fork.hpp"
#include <cassert>
#include "config.hpp"

Fork::Fork() {
    // TODO: implement fork constructor (value, mutex, cond)
    // int ret = pthread_mutex_init(&mutex, NULL);
    // if(ret != 0) printf("\n mutex init has failed\n");

    // mutex = PTHREAD_MUTEX_INITIALIZER;
    // cond = PTHREAD_COND_INITIALIZER; 

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    value = 1;

    next_tk = 0;
    serv_tk = 0;  
    n_tk_out = 0;
    n_tk_max = PHILOSOPHERS;  
}

int Fork::get_ticket(int *tk){
    
    bool success;

    pthread_mutex_lock(&mutex);
   
    if(n_tk_out == n_tk_max){
        success = false;
    }
    else{
        *tk = next_tk;
        next_tk = (next_tk + 1) % n_tk_max;
        n_tk_out++;
        success = true;
    }

    pthread_mutex_unlock(&mutex);

    if(success) return 1;
    else return 0;
}


void Fork::wait(int tk) {
    // TODO: implement semaphore wait

    pthread_mutex_lock(&mutex);

    while((value == 0) || serv_tk != tk) pthread_cond_wait(&cond, &mutex);

    serv_tk = (serv_tk + 1) % n_tk_max;
    value--;

    assert(value >= 0);

    pthread_mutex_unlock(&mutex);
}

void Fork::signal() {
    // TODO: implement semaphore signal
    pthread_mutex_lock(&mutex);
    value++;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);
}

Fork::~Fork() {
    // TODO: implement fork destructor (mutex, cond)

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}