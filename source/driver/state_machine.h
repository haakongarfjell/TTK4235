#pragma once
#include "elevio.h"
#include "con_load.h"
#include "queue.h"
#include "door.h"

// typedef enum {
//     STOP = 0,
//     UP = 1,
//     DOWN = 2,
//     AT_FLOOR = 3,
//     IDLE = 4
// } State;

//void runStateMachine(Request* queue, int size, State* state);

typedef enum {
    INIT = 0,
    MOVE = 1,
    AT_FLOOR = 2,
    STOP = 3,
    DOOR = 4
} State2;


void runStateMachine2(Request* queue, int size, State2* state, int* current_floor, int* doorFlag);

