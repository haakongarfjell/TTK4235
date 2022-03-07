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

void runStateMachine(Request* queue, int size, State* state) {

    printf("Stopbutton: %d \n", elevio_stopButton());


    if (checkNoRequests(queue,size)) {
        *state = IDLE;
    }
    if (elevio_stopButton()) {
        *state = STOP;
    }
    
    Request firstInQueue = *queue;
    ButtonType buttonType = firstInQueue.buttonType;
    int floor = firstInQueue.floor;
    int current_floor = elevio_floorSensor();

    if (floor == -1 && checkNoRequests(queue, size) == 0) {
        leftShiftQueue(queue, size);
        return;
    }

    switch (*state)
    {
    case IDLE: {
        printf("You are now IDLE \n");
        elevio_motorDirection(DIRN_STOP);
        printf("Buttontype: %d \n", buttonType);
        printf("CheckReq: %d \n", checkNoRequests(queue,size));


        if (checkNoRequests(queue,size)) {
            *state = IDLE;
            break;
        }
        if (buttonType == BUTTON_HALL_UP) {
            if (floor > current_floor) {
                *state = UP;
            } else {
                *state = DOWN;
            }
            break;
        }
        if (buttonType == BUTTON_HALL_DOWN) {
            if (floor < current_floor) {
                *state = UP;
            } else {
                *state = DOWN;
            }
            break;
        }
        if (buttonType == BUTTON_CAB) {
            if (floor > current_floor) {
                *state = UP;
                break;
            }
            if (floor < current_floor) {
                *state = DOWN;
                break;
            }
            // else {
            //     *state = AT_FLOOR;
            //     break;
        }
        break;
    }
    case STOP: {
        printf("State : STOP \n");
        elevio_motorDirection(DIRN_STOP);
        resetQueue(queue, size);
        elevio_stopLamp(1);
        //printf("StopButton2 : %d", elevio_stopButton());
        if (elevio_stopButton()) {
            if (current_floor == -1) {
                break;
            }
            doorOpen();
            break;
        } 
        else {
            elevio_stopLamp(0);
            if (current_floor == -1) {
                *state = IDLE;
                doorClose();
                break;
            }
            doorWait();
            *state = IDLE;
            break;
        }
        // Stop lys knapp
        // Queue reset
        // Hvis i en etasje - åpne dør
        // Heisen skal stoppe
        // Hvis knapp - gå til UP/DOWN
    }
    case UP: {
        printf("State : UP \n");
        if (current_floor == floor) {
            *state = AT_FLOOR;
            break;
        }
        elevio_motorDirection(DIRN_UP);
        elevio_doorOpenLamp(0);
        break;
    }
    case DOWN: {
        printf("State : DOWN \n");
        if (current_floor == floor) {
            *state = AT_FLOOR;
            break;
        }
        elevio_motorDirection(DIRN_DOWN);
        elevio_doorOpenLamp(0);
        break;
    }
    case AT_FLOOR: {
        printf("State : AT_FLOOR \n");
        if (floor == -1 ) {
            *state = IDLE;
            break;
        }
        elevio_motorDirection(DIRN_STOP);
        doorWait();     // Evt. doorOpen()
        leftShiftQueue(queue, size);
        // leftshift
        // dør greier
        // sjekk queue[0]
        *state = IDLE;
        break;
    }
    default: {
        // udefinert atm
        printf("Feil \n");
        break;
    }

    }


}