#include "queue.h"

Request buttonCheck() {
    Request tempRequest;
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int btnPressed = elevio_callButton(f, b);
            elevio_buttonLamp(f, b, btnPressed);
            if (btnPressed == 1) {
                tempRequest.buttonType = b;
                tempRequest.floor = f;
                return tempRequest;
            } else {
                tempRequest.floor = -1;
                tempRequest.buttonType = BUTTON_NONE;
            }
        }
    }
    return tempRequest;
}


void leftShiftQueue(Request* queue_ptr, int size) {    // bytt navn til queue_ptr

    Request *queue_ptr_next = queue_ptr;
    for (int i = 0; i < size-1; i++) {

        queue_ptr_next++;

        (*queue_ptr) = (*queue_ptr_next);
        queue_ptr++;
    }
    (*queue_ptr_next).floor = -1;

}

bool checkIfInQueue(Request* queue_ptr, Request element, int size) {
    for (int i = 0; i < size; i++) {
        Request req = *queue_ptr;
        if (req.floor == element.floor && req.buttonType == element.buttonType) {
            return true;
        }
    }
    return false;
}

void addToQueue(Request* queue_ptr, Request element, int size) {
    
    for (int i = 0; i < size; i++) {
        Request req = *queue_ptr;
        if (req.floor == -1 || req.buttonType == 3) {
            *queue_ptr = element;
            break;
        }
        queue_ptr++;
    }
}

void resetQueue(Request* queue_ptr, int size) {
    for (int i = 0; i < size; i++) {
        (*queue_ptr).floor = -1;
        (*queue_ptr).buttonType = BUTTON_NONE;
        queue_ptr++;
    }
}

bool checkNoRequests(Request* queue_ptr, int size) {
    for (int i = 0; i < size; i++) {
        Request req = (*queue_ptr);
        if (req.floor != -1) {
            return false;
        }
        queue_ptr++;
    }
    return true;
}

void printQueue(Request* queue_ptr, int size) {
    for (int i = 0; i < size; i++) {
        Request req = *queue_ptr;
        printf("Floor: %d ", req.floor);
        printf("ButtonType: %d \n", req.buttonType);
        queue_ptr++;
    }
    printf("------------------------\n");
}

void removeDuplicates(Request* queue_ptr, int size) {
    for (int i = 0; i < size; i++) {
        Request current_element = *queue_ptr;
        Request* check_ptr = (queue_ptr+1);
        for (int j = 0; j < size-i-1; j++) {
            Request check_element = *check_ptr;
            if (check_element.floor == current_element.floor && check_element.buttonType == current_element.buttonType) {
                (*check_ptr).floor = -1;
                (*check_ptr).buttonType = BUTTON_NONE;
            }
            check_ptr++;
        }

        queue_ptr++;
    }

}

int numRequestsAtFloor(Request* queue_ptr, int floor) {
    int counter = 0;
    for (int i = 0; i < 3; i++) {       // maks 2 etterfølgende
        Request req = *queue_ptr;
        //printf("reqfloor %d \n", req.floor);
        if (req.floor == floor) {
            counter++;
        }
        queue_ptr++;
    }
    return counter;
}


// Må legges inn flere steder for å oppdateres ofte nok
void requestLights(Request* queue_ptr, int size) {
    for (int i = 0; i < size; i++) {
        Request req = *queue_ptr;
        if (req.floor != -1) {
            elevio_buttonLamp(req.floor, req.buttonType, 1);
        }
        queue_ptr++;
    }
}

void removeFloorRequest(Request* queue_ptr, int size, int floor) {

    for (int i = 0; i < size; i++) {
        Request req = *queue_ptr;
        if (req.floor == floor) {
            (*queue_ptr).floor = -1;
            (*queue_ptr).buttonType = BUTTON_NONE;
        }
        queue_ptr++;
    }

}

bool requestOnTheWay(Request* queue_ptr, ButtonType direction, int floor, int size) {

    for (int i = 0; i < size; i++) {
        Request req = *queue_ptr;
        if (req.floor == floor && req.buttonType == direction) {
            return true;
        }
        queue_ptr++;
    }
    return false;
}