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

void addToQueue(Request* queue_ptr, Request element, int size) {
    Request* new_queue_ptr = queue_ptr+(size-1);
    (*new_queue_ptr) = element;
}

void resetQueue(Request* queue_ptr, int size) {
    for (int i = 0; i < size; i++) {
        (*queue_ptr).floor = -1;
        queue_ptr++;
    }
}

bool checkNoRequests(Request* queue_ptr, int size) {
    //int counter = 0;
    //Request* temp_ptr = queue_ptr;
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
        printf("Number: %d \n", i);
        printf("Floor: %d ", req.floor);
        printf("ButtonType: %d \n", req.buttonType);
        queue_ptr++;
    }

}