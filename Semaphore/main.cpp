//
//  main.cpp
//  Semaphore
//
//  Created by Steven Garcia on 4/30/19.
//  Copyright © 2019 StevenOnSoftware. All rights reserved.
//

#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

const int MAX_INT = std::numeric_limits<int>::max();
const int GROUP_CHUNK_SIZE = 512;
const int SEGMENT_SIZE = GROUP_CHUNK_SIZE * 3;

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

/* speed_check operation
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

