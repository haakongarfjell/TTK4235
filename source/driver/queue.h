#pragma once
#include "elevio.h"
#include "con_load.h"

//constexpr int g_queueSize = 10;

typedef struct {
    ButtonType buttonType;
    int floor;
} Button;       // Navn?

Button buttonCheck();

void leftShiftQueue(Button* queue, int size);

void addToQueue(Button button);

void resetQueue(Button* queue);

void removeDuplicateNeighboursInQueue(Button* queue);




// Button queue[g_queueSize]; Skal være global i main.

