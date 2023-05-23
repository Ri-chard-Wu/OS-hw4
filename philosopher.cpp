#include "philosopher.hpp"


Philosopher::Philosopher(int id, Fork *leftFork, Fork *rightFork, Table *table) :id(id), cancelled(false), leftFork(leftFork), rightFork(rightFork), table(table) {
    srand((unsigned) time(&t1));

}

void Philosopher::start() {
    // TODO: start a philosopher thread

    int ret = pthread_create(&t, NULL, run, (void *)this);
    if(ret != 0) printf("create thread failed.\n");
}


int Philosopher::join() {
    // TODO: join a philosopher thread
    pthread_join(t, NULL);
}

int Philosopher::cancel() {
    // TODO: cancel a philosopher thread
}

void Philosopher::think() {
    int thinkTime = rand() % (MAXTHINKTIME - MINTHINKTIME) + MINTHINKTIME;
    sleep(thinkTime);
    // printf("Philosopher %d is thinking for %d seconds.\n", id, thinkTime);
}

void Philosopher::eat() {
    // printf("Philosopher %d is eating.\n", id);

    enter();

    pickup();

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

    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    while (!p->cancelled) {

        p->think();

        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

        p->eat();

        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    }
 

    return NULL;
}