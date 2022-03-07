#pragma once
#include "elevio.h"
#include "con_load.h"
#include <stdbool.h>

typedef struct {
    ButtonType buttonType;
    int floor;
} Request;       

typedef enum {
    UP      = 0,
    DOWN    = 1
} Direction;

Request buttonCheck();

void leftShiftQueue(Request* queue_ptr, int size);

bool checkIfInQueue(Request* queue_ptr, Request element, int size);

void addToQueue(Request* queue_ptr, Request element, int size);

void resetQueue(Request* queue_ptr, int size);

bool checkNoRequests(Request* queue_ptr, int size);

void printQueue(Request* queue_ptr, int size);

void removeDuplicates(Request* queue_ptr, int size);

int numRequestsAtFloor(Request* queue_ptr, int floor);

void queueLightsOn(Request* queue_ptr, int size);

void removeFloorRequest(Request* queue_ptr, int size, int floor);

bool requestOnTheWay(Request* queue_ptr, ButtonType direction, int floor, int size);    // 1 up, 0 down

void allQueueLightsOff();
