/**
 * @file
 * @brief The state machine is used for controlling the logic that 
 * operates the elevator. This library consists of all handler functions 
 * handles the logical control at each state.
 */

#pragma once
#include "elevio.h"
#include "con_load.h"
#include "queue.h"
#include "time.h"

/**
 * @brief An enum used to determine the direction the elevator is heading.
 * 
 */
typedef enum {
    UP      = 0,
    DOWN    = 1
} Direction;

/**
 * @brief A enum defining all the states the elevator can be at.
 * 
 */
typedef enum {
    INIT = 0,
    MOVE = 1,
    AT_FLOOR = 2,
    STOP = 3,
    DOOR = 4
} State;

/**
 * @brief A switch case that checks what @p state the elevator is at and 
 * calls the correct handler function.
 * 
 * @param[in,out] queue             A pointer to the queue to operate on.
 * @param[in] size                  The size of the queue.
 * @param[in,out] state             A pointer to the current state. Can be changed by handler function.
 * @param[in,out] current_floor     A pointer to the current floor.
 * @param[in,out] between_floors    Used to check or set if the elevator is between floors.
 * @param[in,out] dir               Used to check or set the current elevator direction.
 */
void runStateMachine(Request* queue, int size, State* state, int* current_floor, bool* between_floors, Direction* dir);

/**
 * @brief Called when @p state is INIT.
 * 
 * @param[in,out] queue     A pointer to the queue.
 * @param[in] size          The size of the queue.
 * @param[in,out] state     A pointer to the current @p state. @p state will be set to MOVE if there are requests in the queue.
 */
void initHandler(Request* queue, int size, State* state);

/**
 * @brief Called when @p state is AT_FLOOR. The next @p state will always be set to DOOR.
 * 
 * @param[in] current_floor     The floor the elevator is currently at.
 * @param[in,out] state         A pointer to the current @p state. 
 */
void atFloorHandler(int current_floor, State* state);

/**
 * @brief Called when @p state is STOP. The next @p state will be set to DOOR if the elevator is at a floor, otherwise it will be set
 * to INIT. 
 * 
 * @param[in,out] queue             A pointer to the queue.
 * @param[in] size                  The size of the queue.
 * @param[in,out] state             A pointer to the current state
 * @param[out] between_floors       Set to true if the elevator is between floors.
 */
void stopHandler(Request* queue, int size, State* state, bool* between_floors);

/**
 * @brief Called when @p state is DOOR. The next @p state will always be set to INIT.
 * 
 * @param[in,out] queue     A pointer to the queue.
 * @param[in] size          The size of the queue.
 * @param[in,out] state     A pointer to the current @p state.
 */
void doorHandler(Request* queue, int size, State* state);

/**
 * @brief Called when  @p state is MOVE. The next @p state will always be set to AT_FLOOR.
 * 
 * @param[in,out] queue             A pointer to the queue.
 * @param[in] size                  The size of the queue.
 * @param[in,out] state             A pointer to the current state.
 * @param[in] current_floor         A pointer to the floor the elevator is currently at.
 * @param[in] floor                 Floor connected to the first request in the queue.
 * @param[in,out] between_floors    Checks if the elevator is between floors. Wil always be set to false.
 * @param[in,out] dir               Sets the direction the elevator is moving in.
 */
void moveHandler(Request* queue, int size, State* state, int* current_floor, int floor, bool* between_floors, Direction* dir);