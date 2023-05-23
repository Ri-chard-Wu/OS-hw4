#ifndef FORK_HPP
#define FORK_HPP

#include <pthread.h>

class Fork {
public:
    Fork();
    void wait();
    void signal(); 
    int get_ticket(int *tk);
    ~Fork();
private:
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int value;

    int next_tk;
    int serv_tk;
    int n_tk_max;
    int n_tk_out;
};



#endif // FORK_HPP