#include "state_machine.h"



void runStateMachine(Request* queue, int size, State* state) {

    Request firstInQueue = *queue;
    int floor = elevio_floorSensor();

    if (elevio_stopButton()) {
        *state = STOP;
    }

    switch (*state)
    {
    case IDLE: {
        printf("You are now IDLE \n");
        if (checkNoRequests(&queue, size)) {
            break;
        }
        ButtonType buttonType = firstInQueue.buttonType;
        
        if (buttonType == BUTTON_HALL_UP) {
            *state = UP;
            break;
        }
        if (buttonType == BUTTON_HALL_DOWN) {
            *state = DOWN;
            break;
        }
        if (buttonType == BUTTON_CAB) {
            int cab_floor = firstInQueue.floor;
            if (cab_floor > floor) {
                *state = UP;
                break;
            }
            if (cab_floor < floor) {
                *state = DOWN;
                break;
            }
            else {
                *state = AT_FLOOR;
                break;
            }
        }
        break;
    }
    case STOP: {
        printf("State : STOP \n");
        elevio_motorDirection(DIRN_STOP);
        resetQueue(queue, size);
        elevio_stopLamp(1);
        if (elevio_stopButton()) {
            if (floor == -1) {
                break;
            }
            doorOpen();
            break;
        } 
        else {
            if (floor == -1) {
                elevio_stopLamp(0);
                *state = IDLE;
                break;
            }
            elevio_stopLamp(0);
            doorWait();
            *state = IDLE;
            break;
        }
        // Stop lys knapp
        // Queue reset
        // Hvis i en etasje - åpne dør
        // Heisen skal stoppe
        // Hvis knapp - gå til UP/DOWN
        break;
    }
    case UP: {
        printf("State : UP \n");
        // if floor == queue[0].floor
        // state = at_floor
        break;
    }
    case DOWN: {
        printf("State : DOWN \n");
        elevio_motorDirection(DIRN_DOWN);
        break;
    }
    case AT_FLOOR: {
        printf("State : AT_FLOOR \n");
        // leftshift
        // dør greier
        // sjekk queue[0]
        break;
    }
    default: {
        // udefinert atm
        printf("Feil \n");
        break;
    }

    }


}