#include "philosopher.hpp"


Philosopher::Philosopher(int id, Fork *leftFork, Fork *rightFork, Table *table) :id(id), cancelled(false), leftFork(leftFork), rightFork(rightFork), table(table) {
    srand((unsigned) time(&t1));

}

void Philosopher::start() {
    // TODO: start a philosopher thread

    pthread_create(&t, NULL, run, (void *)this);
}


int Philosopher::join() {
    // TODO: join a philosopher thread
    pthread_join(t, NULL);
}

int Philosopher::cancel() {
    // TODO: cancel a philosopher thread
    pthread_cancel(t);
}

void Philosopher::think() {
    int thinkTime = rand() % (MAXTHINKTIME - MINTHINKTIME) + MINTHINKTIME;
    printf("Philosopher %d begins thinking for %d seconds.\n", id, thinkTime);
    sleep(thinkTime);
}


void Philosopher::eat() {
    
    enter();

    pickup();

    printf("Philosopher %d is eating.\n", id);

    sleep(EATTIME);

    putdown();

    leave();
}


void Philosopher::pickup(int id) {
    // TODO: implement the pickup interface, the philosopher needs to pick up the left fork first, then the right fork

    leftFork->wait();
    rightFork->wait();
}

void Philosopher::putdown(int id) {
    // TODO: implement the putdown interface, the philosopher needs to put down the left fork first, then the right fork

    leftFork->signal();
    rightFork->signal();
}

void Philosopher::enter() {
    // TODO: implement the enter interface, the philosopher needs to join the table first
    table->wait();
}

void Philosopher::leave() {
    // TODO: implement the leave interface, the philosopher needs to let the table know that he has left
    table->signal();
}


void* Philosopher::run(void* arg) {
    // TODO: complete the philosopher thread routine. 

    Philosopher *p = (Philosopher *)arg;

    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    while (1) {

        p->think(); 

        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

        p->eat();

        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    }

    return NULL;
}