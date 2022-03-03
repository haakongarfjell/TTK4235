#include "state_machine.h"



// void runStateMachine(Request* queue, int size, State* state) {

//     printf("Stopbutton: %d \n", elevio_stopButton());


//     if (checkNoRequests(queue,size)) {
//         *state = IDLE;
//     }
//     if (elevio_stopButton()) {
//         *state = STOP;
//     }
    
//     Request firstInQueue = *queue;
//     ButtonType buttonType = firstInQueue.buttonType;
//     int floor = firstInQueue.floor;
//     int current_floor = elevio_floorSensor();

//     if (floor == -1 && checkNoRequests(queue, size) == 0) {
//         leftShiftQueue(queue, size);
//         return;
//     }

//     switch (*state)
//     {
//     case IDLE: {
//         printf("You are now IDLE \n");
//         elevio_motorDirection(DIRN_STOP);
//         printf("Buttontype: %d \n", buttonType);
//         printf("CheckReq: %d \n", checkNoRequests(queue,size));


//         if (checkNoRequests(queue,size)) {
//             *state = IDLE;
//             break;
//         }
//         if (buttonType == BUTTON_HALL_UP) {
//             if (floor > current_floor) {
//                 *state = UP;
//             } else {
//                 *state = DOWN;
//             }
//             break;
//         }
//         if (buttonType == BUTTON_HALL_DOWN) {
//             if (floor < current_floor) {
//                 *state = UP;
//             } else {
//                 *state = DOWN;
//             }
//             break;
//         }
//         if (buttonType == BUTTON_CAB) {
//             if (floor > current_floor) {
//                 *state = UP;
//                 break;
//             }
//             if (floor < current_floor) {
//                 *state = DOWN;
//                 break;
//             }
//             // else {
//             //     *state = AT_FLOOR;
//             //     break;
//         }
//         break;
//     }
//     case STOP: {
//         printf("State : STOP \n");
//         elevio_motorDirection(DIRN_STOP);
//         resetQueue(queue, size);
//         elevio_stopLamp(1);
//         //printf("StopButton2 : %d", elevio_stopButton());
//         if (elevio_stopButton()) {
//             if (current_floor == -1) {
//                 break;
//             }
//             doorOpen();
//             break;
//         } 
//         else {
//             elevio_stopLamp(0);
//             if (current_floor == -1) {
//                 *state = IDLE;
//                 doorClose();
//                 break;
//             }
//             doorWait();
//             *state = IDLE;
//             break;
//         }
//         // Stop lys knapp
//         // Queue reset
//         // Hvis i en etasje - åpne dør
//         // Heisen skal stoppe
//         // Hvis knapp - gå til UP/DOWN
//     }
//     case UP: {
//         printf("State : UP \n");
//         if (current_floor == floor) {
//             *state = AT_FLOOR;
//             break;
//         }
//         elevio_motorDirection(DIRN_UP);
//         elevio_doorOpenLamp(0);
//         break;
//     }
//     case DOWN: {
//         printf("State : DOWN \n");
//         if (current_floor == floor) {
//             *state = AT_FLOOR;
//             break;
//         }
//         elevio_motorDirection(DIRN_DOWN);
//         elevio_doorOpenLamp(0);
//         break;
//     }
//     case AT_FLOOR: {
//         printf("State : AT_FLOOR \n");
//         if (floor == -1 ) {
//             *state = IDLE;
//             break;
//         }
//         elevio_motorDirection(DIRN_STOP);
//         doorWait();     // Evt. doorOpen()
//         leftShiftQueue(queue, size);
//         // leftshift
//         // dør greier
//         // sjekk queue[0]
//         *state = IDLE;
//         break;
//     }
//     default: {
//         // udefinert atm
//         printf("Feil \n");
//         break;
//     }

//     }


// }




void runStateMachine2(Request* queue, int size, State2* state, int* current_floor) {

    Request firstInQueue = *queue;
    ButtonType buttonType = firstInQueue.buttonType;
    int floor = firstInQueue.floor;
    int floor_sensor = elevio_floorSensor();
    
    if (floor_sensor != -1) {
        *current_floor = floor_sensor;
    }

    if (floor == -1 && checkNoRequests(queue, size) == 0) {
        leftShiftQueue(queue, size);
        return;
    }

    switch(*state)
    {
        case INIT: {
            //printf("State : INIT \n");
            if (checkNoRequests(queue, size) != 1) {
                *state = MOVE;
            }
            break;
        }
        case MOVE: {
            if (floor == *current_floor) {
                leftShiftQueue(queue, size);
                *state = AT_FLOOR;
                break;
            }
            if (floor < *current_floor) {
                elevio_motorDirection(DIRN_DOWN);
            } else {
                elevio_motorDirection(DIRN_UP);
            }

            break;
        }
        case AT_FLOOR: {
            elevio_motorDirection(DIRN_STOP);
            //printf("State : AT_FLOOR \n");
            elevio_stopLamp(0);
            *state = DOOR;
            break;
        }
        case STOP: {
            //printf("State : STOP \n");
            elevio_stopLamp(1);
            elevio_motorDirection(DIRN_STOP);
            if (current_floor != -1) {
                *state = AT_FLOOR;
            }
            resetQueue(queue, size);
            break;
        }
        case DOOR: {
            elevio_doorOpenLamp(1);
            break;
        }
        default: {
            break;
        }

    }

}