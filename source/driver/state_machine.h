#pragma once
#include "elevio.h"
#include "con_load.h"
#include "queue.h"
#include "time.h"

typedef enum {
    INIT = 0,
    MOVE = 1,
    AT_FLOOR = 2,
    STOP = 3,
    DOOR = 4
} State;

void runStateMachine(Request* queue, int size, State* state, int* current_floor, bool* between_floors, Direction* dir);

void initHandler(Request* queue, int size, State* state);

void atFloorHandler(int current_floor, State* state);

void stopHandler(Request* queue, int size, State* state, bool* between_floors);

void doorHandler(Request* queue, int size, State* state);

void moveHandler(Request* queue, int size, State* state, int* current_floor, int floor, bool* between_floors, Direction* dir);