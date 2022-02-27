#include "state_machine.h"



void runStateMachine(Request* queue, int size, State* state) {

    Request nextInQueue = *queue;
    int floor = elevio_floorSensor();

    if (elevio_stopButton()) {
        *state = STOP;
    }

    switch (*state)
    {
    case IDLE: {
        printf("You are now IDLE \n");
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
        // if floor == queue[0].floor
        // state = at_floor
        break;
    }
    case DOWN: {

        break;
    }
    case AT_FLOOR: {
        // leftshift
        // dør greier
        // sjekk queue[0]
        break;
    }
    default: {
        // udefinert atm
        break;
    }

    }


}