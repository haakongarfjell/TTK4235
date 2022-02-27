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


void leftShiftQueue(Button* queue, int size) {    // bytt navn til queue_ptr

    Button *queue_next = queue;
    for (int i = 0; i < size-1; i++) {
        //printf("%d", (*queue).floor);

        queue_next++;
        //printf("%d", (*queue_next).floor);
        (*queue) = (*queue_next);
    }
    (*queue_next).floor = -1;


    // for (int k = 10; k > 0; k--) {        
    //     queue[k]=queue[k-1];
    // }
    // Button b;
    // b.floor = -1;
}

