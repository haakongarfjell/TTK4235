#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

#include "driver/queue.h"
#include "driver/fsm.h"
#include "driver/startUpInit.h"


int g_queue_size = 10;

int main(){

    elevio_init();

    Request queue[g_queue_size];
    resetQueue(&queue, g_queue_size);

    State state = INIT;
    int current_floor = 0;
    bool between_floors = false;
    Direction dir = DOWN;

    startInit();

    while(1){
        queueLightsOn(&queue, g_queue_size);

        runStateMachine(&queue, g_queue_size, &state, &current_floor, &between_floors, &dir);

        Request request = buttonCheck();
        addToQueue(&queue, request, g_queue_size);
        removeDuplicates(&queue, g_queue_size);

        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    } 

    return 0;
}

