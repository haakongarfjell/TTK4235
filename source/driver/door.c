#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "elevio.h"
#include "con_load.h"
#include "door.h"



void utdeltTestfunksjon() {

    elevio_init();
    



    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    elevio_motorDirection(DIRN_DOWN);

    while(1){
        int floor = elevio_floorSensor();
        printf("floor: %d \n",floor);

        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }


        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }
        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

}

void doorTest(int nextFloor) {
    int currentFloor = elevio_floorSensor();
    if (currentFloor == nextFloor) {
        elevio_doorOpenLamp(1);
        //sleep(3);
        elevio_doorOpenLamp(0);
    } else {
        elevio_doorOpenLamp(0);
    }

} // ehhh NEI. prøver noe annet -> spesifikasjonene er for spesifikke hehehe

// Prøver noe her bare

void testDoorstruct() {
    int floor = elevio_floorSensor();

    if (floor != 1) {
        elevio_motorDirection(DIRN_DOWN);
    } else {
        elevio_motorDirection(DIRN_STOP);
    }
}

/*
void Door::doorWait() {
    elevio_doorOpenLamp(1);
    sleep(3);
    elevio_doorOpenLamp(0);
}

void Door::doorOpen() {
    elevio_doorOpenLamp(1);
}

void Door::doorClose() {
    elevio_doorOpenLamp(0);
}

*/


//prøver engang til

void doorWait() {
    elevio_doorOpenLamp(1);
    sleep(3);
    elevio_doorOpenLamp(0);
}

void doorOpen() {
    elevio_doorOpenLamp(1);
} 

void doorClose() {
    elevio_doorOpenLamp(0);
}  