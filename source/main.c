#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

#include "driver/door.h"
#include "driver/queue.h"
#include "driver/state_machine.h"
#include "driver/utilities.h"

// Haakon sin token: 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
// haha jeg har tilgang til repoet ditt

// Dette er en endring

int g_queue_size = 10;

int main(){

    elevio_init();
    elevio_doorOpenLamp(0);
    elevio_stopLamp(0);

    Request queue[g_queue_size];
    resetQueue(&queue, g_queue_size);

    State2 s = INIT;
    start_init();
    int current_floor = 0;
    int doorFlag = 0;
    int stop_flag = 0;

    while(1){
        //printf("Stopbutton %d \n", elevio_stopButton());
        // if (elevio_stopButton()) {
        //     s = STOP;
        // }

        // if (s == STOP) {
        //     elevio_motorDirection(DIRN_STOP);
        //     resetQueue(queue, g_queue_size);
        //     if (current_floor != -1) {
        //         elevio_doorOpenLamp(1);
        //     } else {
        //         elevio_doorOpenLamp(0);
        //     }
        //     while(1) {
        //         int stop_button = elevio_stopButton();
        //         if (stop_button == 1) {
        //             continue;
        //         } else {
        //             s = INIT;
        //             break;
        //         }
        //     }
        // }

        requestLights(&queue, g_queue_size);
        if (doorFlag == 1) {
            time_t initSeconds;
            initSeconds = time(NULL);
            while (1) {
                if (elevio_obstruction()) {
                    initSeconds = time(NULL);
                    requestLights(&queue, g_queue_size);
                    Request request = buttonCheck();
                    addToQueue(&queue, request, g_queue_size);
                    removeDuplicates(&queue, g_queue_size);
                    continue;
                }
                requestLights(&queue, g_queue_size);
                Request request = buttonCheck();
                addToQueue(&queue, request, g_queue_size);
                removeDuplicates(&queue, g_queue_size);
                time_t seconds;
                seconds = time(NULL);
                if ((seconds - initSeconds) == 3) {
                    elevio_doorOpenLamp(0);
                    doorFlag = 0;
                    s = INIT;
                    break;
                }
            }           
        }

        printQueue(&queue, g_queue_size);

        if (doorFlag == 0) {
            runStateMachine2(&queue, g_queue_size, &s, &current_floor, &doorFlag, &stop_flag);
        }
        
        Request request = buttonCheck();
        addToQueue(&queue, request, g_queue_size);
        removeDuplicates(&queue, g_queue_size);

        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    } 


    return 0;
    }
