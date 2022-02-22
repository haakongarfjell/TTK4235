

#pragma once
#include "elevio.h"
#include "con_load.h"

int queueSize; //Husk på dette 
    
typedef struct {
    int currentLevel = 0;
    int nextLevel = 0;
} Level;

Level level;

// Matrise med button directions lagt inn.
int queue[4] = [0,-1.,-1,-1];
// Hvis hele queuen er -1, stå stille. Hvis ikke kjør vanlig queuehandler.


void queueHandler(int* queue[4]) {  // Bedre navn
    for (int i = 0; i < 3; i++) {
        (*queue)[i] = (*queue)[i+1];
        queue[3] = -1;
    }
}

void addToQueue(int floor) {
    // if (floor > 4 || floor < 0) return;
    queue[4] = floor;   // size-1
}

while(1) {
    if (level.nextLevel == elevio_floorSensor()) {
        elevio_motorDirection(DIRN_STOP);
        doorWait();
        // med mer
        level.currentLevel = level.nextLevel;
        level.nextLevel = queue[0];
        queueHandler(&queue);
    }

    if (level.nextLevel > level.currentLevel) {
        elevio_motorDirection(DIRN_UP);
    }
    if (level.nextLevel < level.currentLevel) {
        elevio_motorDirection(DIRN_DOWN);
    }
    if ()

    if (level.currentLevel == 0) {
        // Activate lights

    }

    // Må passe på at at vi ikke betjener bestillinger utenfra, når motsatt retning
}
