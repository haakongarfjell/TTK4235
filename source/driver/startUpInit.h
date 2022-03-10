#pragma once
#include "elevio.h"
#include "con_load.h"
#include "queue.h"
/**
 * @file
 * @brief This module contains the function called to set up the elevator
 * for transportation.
 */

/**
 * @brief When this function is called the elevator will always move to 
 * floor 0. All lamps will be turned off and the elevator will not respond
 * to any button presses during the initialization.
 * 
 */
void startUpInit();

