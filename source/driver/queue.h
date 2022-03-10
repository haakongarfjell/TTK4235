/**
 * @file
 * @brief This is a library to create and operate on a queue, an
 * array of requests. Most of the functions take in a pointer to 
 * the first request in the queue and is used to operate on the elements of the queue.
 */

#pragma once
#include "elevio.h"
#include "con_load.h"
#include <stdbool.h>

/**
 * @brief A struct defining an elevator request. Contains the type of button pressed, and the floor
 * it is pressed at.
 * 
 */
typedef struct {
    ButtonType buttonType;
    int floor;
} Request;       

/**
 * @brief An enum used to determine the direction the elevator is heading.
 * 
 */
typedef enum {
    UP      = 0,
    DOWN    = 1
} Direction;

/**
 * @brief Checks if a button has been pressed.
 * 
 * @return a Request with buttonType and floor as member variables.
 */
Request buttonCheck();


/**
 * @brief Used to left shift the queue when a Request has been handled.
 * 
 * @param[in,out] queue_ptr     Pointer to the queue.
 * @param[in] size              Size of the queue.
 */
void leftShiftQueue(Request* queue_ptr, int size);

/**
 * @brief Checks if an @p element of is in the queue.
 * 
 * @param[in] queue_ptr         Pointer to the queue.
 * @param[in] element           Element to check if is in the queue.
 * @param[in] size              Size of the queue.
 * @return true if @p element is in the queue.
 * @return false otherwise.
 */
bool checkIfInQueue(Request* queue_ptr, Request element, int size);

/**
 * @brief Adds an @p element to the back of the queue.
 * 
 * @param[in,out] queue_ptr     Pointer to the queue.
 * @param[in] element           Element to add to queue.
 * @param[in] size              Size of the queue.
 */
void addToQueue(Request* queue_ptr, Request element, int size);

/**
 * @brief Resets all the elements of the queue. All requests will have
 * buttonType set to BUTTON_NONE and floor to -1.
 * 
 * @param[in,out] queue_ptr     Pointer to the queue.
 * @param[in] size              Size of the queue.
 */
void resetQueue(Request* queue_ptr, int size);

/**
 * @brief Checks if the queue is empty, if there are no requests.
 * 
 * @param[in] queue_ptr         Pointer to the queue.
 * @param[in] size              Size of the queue.
 * @return true if the queue has no requests.
 * @return false otherwise.
 */
bool checkNoRequests(Request* queue_ptr, int size);


void printQueue(Request* queue_ptr, int size);  // Fjernes?


/**
 * @brief Checks if the queue containes any dublicate requests, and
 * removes all instances except one.
 * 
 * @param[in,out] queue_ptr     Pointer to the queue.
 * @param[in] size              Size of the queue.
 */
void removeDuplicates(Request* queue_ptr, int size);


int numRequestsAtFloor(Request* queue_ptr, int floor);  // Fjernes?

/**
 * @brief Turns on the button lamps of all of the requests in the queue.
 * 
 * @param[in] queue_ptr         Pointer to the queue.
 * @param[in] size              Size of the queue.
 */
void queueLightsOn(Request* queue_ptr, int size);

/**
 * @brief Removes all the requests on a given @p floor. All requests at
 * this @p floor will have buttonType set to BUTTON_NONE and floor
 * set to -1.
 * 
 * @param[in,out] queue_ptr     Pointer to the queue.
 * @param[in] size              Size of the queue.
 * @param[in] floor             Floor to remove requests at.
 */
void removeFloorRequest(Request* queue_ptr, int size, int floor);

/**
 * @brief Checks if there are any requests the elevator can pick up on 
 * in the current direction. For example, if @p direction is UP and there 
 * is a request in the queue with buttonType = BUTTON_HALL_UP. ???
 * 
 * @param queue_ptr 
 * @param direction 
 * @param floor 
 * @param size 
 * @return true 
 * @return false 
 */
bool requestOnTheWay(Request* queue_ptr, ButtonType direction, int floor, int size);    // 1 up, 0 down

/**
 * @brief Turns off all button lights.
 * 
 */
void allQueueLightsOff();   // Endre til buttonLightsOff?
