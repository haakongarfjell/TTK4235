#include "queue.h"

Button buttonCheck() {
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int btnPressed = elevio_callButton(f, b);
            if (btnPressed == 1) {
                Button tempButton;
                tempButton.buttonType = b;
                tempButton.floor = f;
                return tempButton;
            }
        }
    }
}


void leftShiftQueue(Button* queue_ptr, int size) {    // bytt navn til queue_ptr

    Button *queue_ptr_next = queue_ptr;
    for (int i = 0; i < size; i++) {

        queue_ptr_next++;

        (*queue_ptr) = (*queue_ptr_next);
        queue_ptr++;
    }
    (*queue_ptr_next).floor = -1;

}

void addToQueue(Button button, int size) {
    
}