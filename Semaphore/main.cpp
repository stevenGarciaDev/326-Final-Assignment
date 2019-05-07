//
//  main.cpp
//  Semaphore
//
//  Created by Steven Garcia on 4/30/19.
//  Copyright © 2019 StevenOnSoftware. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "semaphore.h"

using namespace std;

enum {shared0, shared1, shared2, shared3, shared4}; //set up names of 4 semaphores

void producer_proc(SEMAPHORE &, char *);
void parent_cleanup(SEMAPHORE &, int);
void consumer_proc(SEMAPHORE &, char *);

const int MAX_INT = std::numeric_limits<int>::max();
const int GROUP_CHUNK_SIZE = 512;
const int SEGMENT_SIZE = GROUP_CHUNK_SIZE * 3;
const int TOTAL_SEGMENT_SIZE = SEGMENT_SIZE * 4;

int requiredOperationsAmount;               // specifies how many times to go through loop

/*
 Based on boolean argument,
 create an array based on size,
 and initialize random char
*/
void initRandomChar(char group[], int size, bool isUpperCase) {
    int low;
    int high;
    if (isUpperCase) {
        low = 65;
        high = 90;
    } else {
        low = 97;
        high = 122;
    }
    
    //cout << "the size of the group is " << size << endl;
    
    for (int i = 0; i < size; i++) {
        char randomChar = (rand() % 26) + low;
        group[i] = randomChar;
        //cout << "randomChar is " << randomChar << endl;
    }
}

/*
 speed_check operation
 generate a random number
 check if num is less than 5000
 return false
 else return true
*/
bool shouldPerformSwap() {
    int randomValue = MAX_INT;
    randomValue = rand() % MAX_INT;
    if (randomValue < 5000) {
        return true;
    }
    return false;
}

int main(int argc, const char * argv[]) {
    srand( time(0) );
    
    // the shared memory
    int shmid;
    char *shmBUF;
    
    //initalize semaphores
    SEMAPHORE sem(5);
    
    //increment each semaphore to 1 so they are ready to be used by the child processes
    sem.V(shared0);
    sem.V(shared1);
    sem.V(shared2);
    sem.V(shared3);
    sem.V(shared4);
    
    // shmget, analogous to msgget,
    shmid = shmget(IPC_PRIVATE, TOTAL_SEGMENT_SIZE*sizeof(char), PERMS); // allocate shared memory
    shmBUF = (char *)shmat(shmid, 0, SHM_RND);    // (attach to shared memory) now make it available to this program
    // params deal with memory management,
    // IPC_PRIVATE replaces ftok()
    //     means use default value generated by the system
    //      use ftok() for separate programs accessing same
    //     in this case only 1 program
    
    
    
    
    int operationsAmount;
    
    cout << "Enter the required number of operations: " << endl;
    cin >> operationsAmount;
    
    // create 4 groups of shared memory
    cout << "the segment size is " << SEGMENT_SIZE << endl;
    char group1[SEGMENT_SIZE];
    char group2[SEGMENT_SIZE];
    char group3[SEGMENT_SIZE];
    char group4[SEGMENT_SIZE];
    
    initRandomChar(group1, SEGMENT_SIZE, false);
    initRandomChar(group2, SEGMENT_SIZE, true);
    initRandomChar(group3, SEGMENT_SIZE, true);
    initRandomChar(group4, SEGMENT_SIZE, true);
    
    
    return 0;
}

void parent_cleanup(SEMAPHORE &sem, int shmid) {
    int status;    /* child status */
    wait(0);    /* wait for child to exit */
    shmctl(shmid, IPC_RMID, NULL);    /* cleaning up */
    sem.remove();
} // parent_cleanup,
