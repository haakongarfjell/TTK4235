#pragma once
#include "elevio.h"
#include "con_load.h"

//constexpr int g_queueSize = 10;

typedef struct {
    ButtonType buttonType;
    int floor;
} Button;       // Navn: request

Button buttonCheck();

void leftShiftQueue(Button* queue_ptr, int size);

void addToQueue(Button button, int size);

void resetQueue(Button* queue_ptr);

void removeDuplicateNeighboursInQueue(Button* queue_ptr);




// Button queue[g_queueSize]; Skal være global i main.

