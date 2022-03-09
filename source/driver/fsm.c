#include "fsm.h"

void initHandler(Request* queue, int size, State* state) {
    elevio_doorOpenLamp(0); 
    if (checkNoRequests(queue, size) != 1) {
         *state = MOVE;
   } 
}

void atFloorHandler(int current_floor, State *state) {

    elevio_motorDirection(DIRN_STOP);
    elevio_buttonLamp(current_floor, BUTTON_CAB, 0);
    elevio_buttonLamp(current_floor, BUTTON_HALL_DOWN, 0);
    elevio_buttonLamp(current_floor, BUTTON_HALL_UP, 0);
    elevio_floorIndicator(current_floor);
    elevio_stopLamp(0);
    *state = DOOR;
}

void stopHandler(Request* queue, int size, State* state, bool* between_floors) {
    elevio_stopLamp(1);
    elevio_motorDirection(DIRN_STOP);
    resetQueue(queue, size);
    allQueueLightsOff();

    if (elevio_floorSensor() != -1) {
        elevio_doorOpenLamp(1);
    } else {
        elevio_doorOpenLamp(0);
    }

    while(1) {
        if (elevio_stopButton()) {
            elevio_stopLamp(1);
            continue;
        } 
        elevio_stopLamp(0);
        if (elevio_floorSensor() != -1) {
            *state = DOOR;
            return;
        } else {
            *between_floors = true;
            *state = INIT;
            return;
        }
    }
}

void doorHandler(Request* queue, int size, State* state) {
    elevio_doorOpenLamp(1);
    time_t initSeconds;
    initSeconds = time(NULL);
    while (1) {
        queueLightsOn(queue, size);
        if (elevio_stopButton()) {
            return;
        }

        Request request = buttonCheck();
        addToQueue(queue, request, size);
        removeDuplicates(queue, size);

        if (elevio_obstruction()) {
            initSeconds = time(NULL);
            continue;
        }
        
        time_t seconds;
        seconds = time(NULL);
        
        if ((seconds - initSeconds) == 3) {
            elevio_doorOpenLamp(0);
            *state = INIT;
            return;
        }
    }
}

void moveHandler(Request* queue, int size, State* state, int* current_floor, int floor, bool* between_floors, Direction* dir) {
    int direction = floor-*current_floor;
    int floor_sensor = elevio_floorSensor();
    bool req_way_cab = requestOnTheWay(queue, BUTTON_CAB, floor_sensor, size); 
    if (direction > 0) {
        bool req_way = requestOnTheWay(queue, BUTTON_HALL_UP, floor_sensor, size);
        if (req_way || req_way_cab) {
            removeFloorRequest(queue, size, *current_floor);
            *state = AT_FLOOR;
            return;  
        }
    }
    if (direction < 0) {
        bool req_way = requestOnTheWay(queue, BUTTON_HALL_DOWN, floor_sensor, size);
        if (req_way || req_way_cab) {
            removeFloorRequest(queue, size, *current_floor);
            *state = AT_FLOOR;
            return;  
        }
    }
    if (floor == *current_floor && *between_floors == false) {
        removeFloorRequest(queue, size, *current_floor);
        *state = AT_FLOOR;
        return;
    }
    if (floor == *current_floor && *between_floors == true) {
        if (floor_sensor == floor) {
            *between_floors = false;
        }
        if (*dir == UP) {
            elevio_motorDirection(DIRN_DOWN);

        } else {
            elevio_motorDirection(DIRN_UP);

        }
        return;
    }
    if (floor < *current_floor && *between_floors == false) {
        elevio_motorDirection(DIRN_DOWN);
        *dir = DOWN;
    } else {
        elevio_motorDirection(DIRN_UP);
        *dir = UP;
    }
    
    *between_floors = false;
}

void runStateMachine(Request* queue, int size, State* state, int* current_floor, bool* between_floors, Direction* dir) {
    
    Request firstInQueue = *queue;
    ButtonType buttonType = firstInQueue.buttonType;
    int floor = firstInQueue.floor;
    int floor_sensor = elevio_floorSensor();
    
    queueLightsOn(queue, size);

    if (floor_sensor != -1) {
        *current_floor = floor_sensor;
    }

    if (floor == -1 && checkNoRequests(queue, size) == 0) {
        leftShiftQueue(queue, size);
        return;
    }

    if (elevio_stopButton()) {
        *state = STOP;
    }

    switch(*state)
    {
        case INIT: {
            initHandler(queue, size, state);
            break;
        }
        case MOVE: {
            moveHandler(queue, size, state, current_floor, floor, between_floors, dir);
            break;
        }
        case AT_FLOOR: {
            atFloorHandler(*current_floor, state);
            break;
        }
        case STOP: {
            stopHandler(queue, size, state, between_floors);
            break;
        }
        case DOOR: {
            doorHandler(queue, size, state);
            break;
        }
        default: {
            break;
        }

    }

}