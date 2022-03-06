#include "utilities.h"

void start_init() {
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
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            elevio_buttonLamp(f, b, 0);
        }
    }
}

void testLights() {
    for (int i = 0; i < 4; i++) {
        elevio_buttonLamp(i, BUTTON_CAB, 1);
    }
}