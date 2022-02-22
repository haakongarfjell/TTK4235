

#pragma once
#include "elevio.h"
#include "con_load.h"

int queueSize; //Husk på dette 
    
typedef struct {
    int currentLevel = 0;
    int nextLevel = 0;
} Level;

Level level;

// Matrise med button directions lagt inn. Lag queue av ButtonFloor typen.
int queue[4] = [0,1, 1,-1];
// Hvis hele queuen er -1, stå stille. Hvis ikke kjør vanlig queuehandler.

void leftShiftQueue(Button* queue);

void passByFloor(); // Sjekk om en etasje i mellom har requested i riktig retning.

void removeDuplicateNeighbourFloors(); // Fjern like etasjer ved siden av hverandre i køen.

bool checkStop(); // Sjekk om stopknappen er trykket.
// if (checkStop()) continue; Køen slettes
    void resetQueue();




void addToQueue(int floor) {
    // if (floor > 4 || floor < 0) return;
    queue[3] = floor;   // size-1
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

typedef struct {
    ButtonType button;
    int floor;
} ButtonFloor;

// Lage queue av ButtonFloor
ButtonFloor buttonCheck() {

for(int f = 0; f < N_FLOORS; f++){
    for(int b = 0; b < N_BUTTONS; b++){
        int btnPressed = elevio_callButton(f, b);
        if (btnPressed == 1) {
            ButtonFloor tempButton;
            tempButton.button = b;
            tempButton.floor = f;
            return tempButton;
        }
        elevio_buttonLamp(f, b, btnPressed);
        }
    }

}

for(int f = 0; f < N_FLOORS; f++){
    for(int b = 0; b < N_BUTTONS; b++){
        int btnPressed = elevio_callButton(f, b);
        printf("knapp: %d \n",btnPressed);
        elevio_buttonLamp(f, b, btnPressed);
        }
    }

}