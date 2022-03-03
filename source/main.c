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
    while(current_floor != 0) {
        elevio_motorDirection(DIRN_DOWN);
    }


    while(1){
        //int floor = elevio_floorSensor();
        //printf("floor: %d \n",floor);

        printQueue(&queue, g_queue_size);
        //printf("Stopbutton: %d", stop);
        if (elevio_stopButton()) {
            s = STOP;
        }
            
        runStateMachine2(&queue, g_queue_size, &s, &current_floor);

        Request request = buttonCheck();
        if (checkIfInQueue(&queue, request, g_queue_size) == false) {
            printf("Adding to queue \n");
            addToQueue(&queue, request, g_queue_size);
        }

        //printf("Current_floor %d \n", current_floor);

        // if(floor == 0){
        //     elevio_motorDirection(DIRN_UP);
        // }

        // if(floor == N_FLOORS-1){
        //     elevio_motorDirection(DIRN_DOWN);
        // }

        // for(int f = 0; f < N_FLOORS; f++){
        //     for(int b = 0; b < N_BUTTONS; b++){
        //         int btnPressed = elevio_callButton(f, b);
        //         //printf("knapp: %d \n",btnPressed);
        //         elevio_buttonLamp(f, b, btnPressed);
        //     }
        // }    

        // if(elevio_stopButton()){
        //     elevio_motorDirection(DIRN_STOP);
        //     break;
        // }

        // if (floor == 1){
        //     elevio_motorDirection(DIRN_STOP);
        //     doorWait();
        //     break;
        // }
        
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    } 


    return 0;
    }
