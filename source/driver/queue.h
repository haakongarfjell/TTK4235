#pragma once
#include "elevio.h"
#include "con_load.h"

//constexpr int g_queueSize = 10;

typedef struct {
    ButtonType buttonType;
    int floor;
} Request;       // Navn: request

Request buttonCheck();

void leftShiftQueue(Request* queue_ptr, int size);

void addToQueue(Request* queue_ptr, Request element, int size);

void resetQueue(Request* queue_ptr);

void removeDuplicateNeighboursInQueue(Request* queue_ptr);




// Request queue[g_queueSize]; Skal være global i main.

