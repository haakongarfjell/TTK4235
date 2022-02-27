#pragma once
#include "elevio.h"
#include "con_load.h"



/*
Hvis buttonType = CAB: floor er etasjen som vi skal til.
Hvis buttonType = UP/DOWN: floor er etasjen der knappen har blitt trykket.
*/

typedef struct {
    ButtonType buttonType;
    int floor;
} Request;       // Navn: request

Request buttonCheck();

void leftShiftQueue(Request* queue_ptr, int size);

void addToQueue(Request* queue_ptr, Request element, int size);

void resetQueue(Request* queue_ptr, int size);

void removeDuplicateNeighboursInQueue(Request* queue_ptr);




// Request queue[g_queueSize]; Skal være global i main.

