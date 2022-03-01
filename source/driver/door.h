#pragma once

#include "elevio.h"
#include "time.h"

void utdeltTestfunksjon();

void doorTest();

void testDoorstruct();

/*
struct Door {
    void doorWait();
    void doorOpen(); // heisdørlampe på indikerer at døren er åpen. Få inn noen asserts her slik at heisen ikke beveger seg når døren er åpen?
    void doorClose();  
}
*/

void doorWait();
void doorOpen(); 
void doorClose();  