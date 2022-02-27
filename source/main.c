#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

//#include "driver/door.h"
#include "driver/queue.h"

// Haakon sin token: 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
// haha jeg har tilgang til repoet ditt

int g_queue_size = 4;

int main(){

    elevio_init();

    elevio_motorDirection(DIRN_DOWN);

    elevio_doorOpenLamp(0);

    // Her er en endring
    Request b1,b2,b3,b4;
    b1.buttonType = BUTTON_HALL_DOWN;
    b1.floor = 2;
    b2.buttonType = BUTTON_HALL_UP;
    b2.floor = 0;
    b3.buttonType = BUTTON_CAB;
    b3.floor = 4;
    b4.buttonType = BUTTON_CAB;
    b4.floor = 7;

    Request queue[g_queue_size];
    addToQueue(&queue, b1, g_queue_size);
    leftShiftQueue(&queue, g_queue_size);
    addToQueue(&queue, b2, g_queue_size);
    leftShiftQueue(&queue, g_queue_size);
    addToQueue(&queue, b3, g_queue_size);
    leftShiftQueue(&queue, g_queue_size);
    addToQueue(&queue, b4, g_queue_size);

    printf("b1: %d \n", queue[0].floor);
    printf("b2: %d \n", queue[1].floor);
    printf("b3: %d \n", queue[2].floor);
    printf("b4: %d \n", queue[3].floor);
    printf("%d \n");
    leftShiftQueue(&queue, g_queue_size);
    printf("b1: %d \n", queue[0].floor);
    printf("b2: %d \n", queue[1].floor);
    printf("b3: %d \n", queue[2].floor);
    printf("b4: %d \n", queue[3].floor);
    printf("%d \n");
    addToQueue(&queue, b4, g_queue_size);
    printf("b1: %d \n", queue[0].floor);
    printf("b2: %d \n", queue[1].floor);
    printf("b3: %d \n", queue[2].floor);
    printf("b4: %d \n", queue[3].floor);
    printf("%d \n");
    printf("Queuecheck : %d \n", checkNoRequests(&queue, g_queue_size));
    printf("%d \n");
    resetQueue(&queue, g_queue_size);
    printf("b1: %d \n", queue[0].floor);
    printf("b2: %d \n", queue[1].floor);
    printf("b3: %d \n", queue[2].floor);
    printf("b4: %d \n", queue[3].floor);
    printf("%d \n");
    printf("Queuecheck : %d \n", checkNoRequests(&queue, g_queue_size));
    while(1){
        int floor = elevio_floorSensor();
        //printf("floor: %d \n",floor);

  
        

     

        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }

        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                //printf("knapp: %d \n",btnPressed);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }    

        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }

        // if (floor == 1){
        //     elevio_motorDirection(DIRN_STOP);
        //     doorWait();
        //     break;
        // }
        
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    } 

    elevio_doorOpenLamp(0);

    return 0;
    }
