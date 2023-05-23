#include "philosopher.hpp"

#include <stdlib.h>
#include <unistd.h>
#include <vector>
using namespace std;

int main(int argc, char** argv) {

    // TODO: create forks, table, and philosophers. The number of forks and philosophers are defined in the config.hpp

    Table *table = new Table();
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


    sleep(RUNTIME);

    // TODO: cancel philosopher threads 

    // TODO: join philosopher threads (i.e. wait for them to finish) 

    // TODO: delete forks, table, and philosophers
    
    return 0;
}