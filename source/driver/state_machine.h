#pragma once
#include "elevio.h"
#include "con_load.h"
#include "queue.h"
#include "door.h"

typedef enum {
    STOP = 0,
    UP = 1,
    DOWN = 2,
    AT_FLOOR = 3,
    IDLE = 4
} State;

void runStateMachine(Request* queue, int size, State* state);