#include "queue.h"

Request buttonCheck() {
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int btnPressed = elevio_callButton(f, b);
            if (btnPressed == 1) {
                Request tempRequest;
                tempRequest.buttonType = b;
                tempRequest.floor = f;
                return tempRequest;
            }
        }
    }
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