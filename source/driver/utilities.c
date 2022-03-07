#include "utilities.h"

void startInit() {
    int current_floor;
    elevio_floorIndicator(0);
    while(1) {
        elevio_motorDirection(DIRN_DOWN);
        current_floor = elevio_floorSensor();
        //printf("Current floor : %d \n", current_floor);
        if (current_floor == 0) {
            elevio_motorDirection(DIRN_STOP);
            break;
        }
    }
    allQueueLightsOff();
    elevio_doorOpenLamp(0);
    elevio_stopLamp(0);
}

