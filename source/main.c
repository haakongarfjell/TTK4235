#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

#include "driver/door.h"
#include "driver/queue.h"
#include "driver/state_machine.h"

// Haakon sin token: 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
// haha jeg har tilgang til repoet ditt

        // Dette er en endring

int g_queue_size = 10;

int main(){

    elevio_init();

    //elevio_motorDirection(DIRN_UP);

    elevio_doorOpenLamp(0);
    elevio_stopLamp(0);
    // Her er en endring
    Request queue[g_queue_size];
    resetQueue(&queue, g_queue_size);

    State2 s = INIT;
    int current_floor = 0;

    // test
    elevio_motorDirection(DIRN_DOWN);

    // time_t initSeconds;
    // initSeconds = time(NULL);
    int doorFlag = 0;
    while(1){
        //int floor = elevio_floorSensor();
        //printf("floor: %d \n",floor);
        // time_t seconds;
        // if (s == DOOR && doorFlag == 1) {
        //     seconds = time(NULL);
        //     printf("Seconds: %d \n", seconds-initSeconds);
        // }

        // if ((seconds - initSeconds) == 3) {
        //     elevio_doorOpenLamp(0);
        //     s = INIT;
        //     doorFlag = 0;
        // }
        if (doorFlag == 1) {
            time_t initSeconds;
            initSeconds = time(NULL);
            while (1) {
                Request request = buttonCheck();
                addToQueue(&queue, request, g_queue_size);
                removeDuplicates(&queue, g_queue_size);
                time_t seconds;
                seconds = time(NULL);
                if ((seconds - initSeconds) > 2) {
                    elevio_doorOpenLamp(0);
                    doorFlag = 0;
                    s = INIT;
                    break;
                }
            }           
        }

        printQueue(&queue, g_queue_size);
        if (elevio_stopButton()) {
            s = STOP;
        }
        if (doorFlag == 0) {
            runStateMachine2(&queue, g_queue_size, &s, &current_floor, &doorFlag);
        }
        
        Request request = buttonCheck();
        addToQueue(&queue, request, g_queue_size);
        removeDuplicates(&queue, g_queue_size);

        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    } 


    return 0;
    }
