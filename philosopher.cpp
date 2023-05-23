#include "philosopher.hpp"
#include <iostream>
#include <string> 

using namespace std;

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

#define COL_WIDTH 15


void col_print(string s, int col_id, int w, int n_col){

    string s_out = "";
    
    for(int i = 0; i < col_id; i++){
        s_out += "|";
        s_out.append(w - 1, ' ');
    }
    
    int len_i = s_out.length();
    s_out += "|";
    s_out += s;
    int diff = s_out.length() - len_i;
    s_out.append(w - diff, ' ');

    for(int i = col_id + 1; i < n_col; i++){
        s_out += "|";
        s_out.append(w - 1, ' ');
    }
    
    s_out += "\n";
    cout << s_out;
}

string int2string(int n){
    char buf[10];
    sprintf(buf, "%d", n);
    return ((string)buf);
}


void Philosopher::think() {
    int thinkTime = rand() % (MAXTHINKTIME - MINTHINKTIME) + MINTHINKTIME;

    string s = "think-" + int2string(thinkTime) + "_sec";
    col_print(s, id, COL_WIDTH, PHILOSOPHERS);

    sleep(thinkTime);
}


void Philosopher::eat() {
    
    enter();

    pickup();

    // char s[COL_WIDTH];
    // sprintf(s, "eat\n"); 
    // col_print(s, id, COL_WIDTH, PHILOSOPHERS);

    
    col_print((string)"eat", id, COL_WIDTH, PHILOSOPHERS);

    sleep(EATTIME);

    putdown();

    leave();
}


void Philosopher::pickup() {
    // TODO: implement the pickup interface, the philosopher needs to pick up the left fork first, then the right fork

    leftFork->wait();
    rightFork->wait();
}

void Philosopher::putdown() {
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