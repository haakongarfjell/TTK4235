#include "utilities.h"

void start_init() {
    int current_floor;
    while(1) {
        elevio_motorDirection(DIRN_DOWN);
        current_floor = elevio_floorSensor();
        //printf("Current floor : %d \n", current_floor);
        if (current_floor == 0) {
            elevio_motorDirection(DIRN_STOP);
            break;
        }
    }
}