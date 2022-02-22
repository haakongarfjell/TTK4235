#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

#include "driver/door.h"

// Haakon sin token: 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

int main(){

    elevio_init();

    elevio_motorDirection(DIRN_DOWN);

    elevio_doorOpenLamp(0);

    // Her er en endring


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
                printf("knapp: %d \n",btnPressed);
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
