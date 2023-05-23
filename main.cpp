#include "philosopher.hpp"

#include <stdlib.h>
#include <unistd.h>
#include <vector>
using namespace std;

int main(int argc, char** argv) {

    // TODO: create forks, table, and philosophers. The number of forks and philosophers are defined in the config.hpp

    Table *table = new Table(PHILOSOPHERS);
    vector<Fork *> fork_array;
    vector<Philosopher *> phr_array;

    for (int i = 0; i < PHILOSOPHERS; i++){
        fork_array.push_back(new Fork());
    }

    for (int i = 0; i < PHILOSOPHERS; i++){
        Fork *leftFork = fork_array[i];
        Fork *rightFork = fork_array[(i + 1) % PHILOSOPHERS];
        phr_array.push_back(new Philosopher(i, leftFork, rightFork, table));
    }    
    

    // TODO: start running philosopher threads
    for (int i = 0; i < PHILOSOPHERS; i++){
        phr_array[i]->start();
    }    

    sleep(RUNTIME);

    // TODO: cancel philosopher threads 
    for (int i = 0; i < PHILOSOPHERS; i++){
        phr_array[i]->cancel();
    } 

    // TODO: join philosopher threads (i.e. wait for them to finish) 
    for (int i = 0; i < PHILOSOPHERS; i++){
        phr_array[i]->join();
    } 

    // TODO: delete forks, table, and philosophers
    delete table;
    for (int i = 0; i < PHILOSOPHERS; i++){
        delete fork_array[i];
        delete phr_array[i];
    }
    
    return 0;
}