#include <cstdio>       // printf
#include <thread>       // thread
#include <cstdlib>      // rand, srand
#include <unistd.h>     // sleep
#include <mutex>        // mutex
#include <semaphore.h>  // semaphore

using namespace std;

// Resources that will be used
#define MAX_RESOURCES 5                     // Maximum resources possible
int available_resources = MAX_RESOURCES;    // Avaliable resources

/*
    === Reading Code ===
    Start by reading the application() and main() functions.
    main() will create 10 threads that call application.
    application() will hold some resources for some time and then return it.

    === Semaphores ===
    Semeaphores can be declared as:
        sem_t s;
    In main, you should initialize the semaphores using:
        sem_init(&s, 0, value);
            @value: value to initialize semaphore to (i.e. 1 for a mutex style semaphore)
    Operations include:
        sem_wait(&s); - Wait, and decriments semaphore
        sem_post(&s); - Singal, and increments semaphore

    === Mutex ===
    Mutex can be declared as:
        mutex m;
    Operations include:
        m.lock();
        m.unlock();

    === PARTS 1 & 2 ===
    You will find instructions in the application() function.
    Always be sure to avoid deadlock and race conditions

    === IMPORTANT ===
    When the program finishes it should always report 5 available resources!
        Any more or less, then something isn't right!
    Make sure to declare Semaphores and Mutex globally so they can be shared by all threads
*/

// === Part 1 Function ===
// Decrease the resources by a given amount
// @Param count: The number to decrease the resources by
// Returns true if successful, and false if there isn't enough resources.
bool decrease_count(int count) {
    if(available_resources < count) {
        return false;
    }
    available_resources -= count;
    return true;
}

// === Part 1 Function ===
// Increase the resources by a given amount
// @Param count: The number to increase the resources by
void increase_count(int count) {
    available_resources += count;
}

// === Part 2 Function ===
// Decrease the resources by a given amount
// @Param count: The number to decrease the resources by
void decrease_S(int count) {
    // Make sure to keep track of the resources so that it never goes below 0
}

// === Part 2 Function ===
// Increase the resources by a given amount
// @Param count: The number to increase the resources by
void increase_S(int count) {
    // Make sure to keep track of the resources so that it never goes below 0
}

// An "applicaion" function that threads will run
// Takes 1-3 resources and holds them for some time
// Afterwords it returns the resources and finishes
void application(int myID) {    
    // Start a random number of application instances (between 1 and 3)
    int c = ((int) rand() % 3)+1;

    /*
        === PART 1 ===
        Identify the race conditions in the code below.
        Modify the functions decrease_count() and increase_count() above
            - Use either a mutex or binary semaphore to prevent race conditions.
            - Make sure to keep track of the resources so that it never goes below 0

        There should be no DEADLOCK or RACE CONDITIONS

        Note: This approach is busy waiting!
            Can a counting semaphore be used instead of busy waiting?
            Part 2 explores this option
    */    

    while(!decrease_count(c));  // Holding resources
    printf("Application %d is starting %d instances.\n", myID, c);
    sleep(rand() % 2);          // Using resource for some time
    increase_count(c);          // Releaseing resources

    /*
        === Part 2 ===
        Implemenat the functions decrease_S() and increase_S() above
            - Use a counting semaphore to prevent race conditions
            - Make sure to keep track of the resources so that it never goes below 0

        There should be no DEADLOCK or RACE CONDITIONS
        Hint: Also use a mutex and/or binary semaphore
        
        Note: Comment the code above from part 1
            and uncomment the code below for part 2
    */

    // decrease_S(c);      // Holding resources
    // printf("Application %d is starting %d instances.\n", myID, c);
    // sleep(rand() % 2);  // Using resource for some time
    // increase_S(c);      // Releaseing resources
}

// Starts application threads and waits on them to finish.
int main(int argc, char** argv) {
    // Init
    thread applications[10];    // Worker threads
    srand((unsigned)time(0));   // Seeding the random number generator

    /*
        === PART 1 & 2 ===
        Initilize semaphores here
    */
    
    // Creating application worker threads
    for(int i = 0; i < 10; i++) {
        applications[i] = thread(application, i); 
    }

    // Wait for threads to finish
    for(int i = 0; i < 10; i++) {
        applications[i].join();
    }

    // Printing resources avaliable - SHOULD BE 5!
    printf("Final Available Resources: %d\n", available_resources);
}
