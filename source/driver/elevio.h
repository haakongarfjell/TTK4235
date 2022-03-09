/**
 * @file
 * @brief A library for defining the interface between the control logic
 * and the pysical elevator.
 */


#pragma once
#define N_FLOORS 4

typedef enum { 
    DIRN_DOWN   = -1,
    DIRN_STOP   = 0,
    DIRN_UP     = 1
} MotorDirection;


#define N_BUTTONS 3

typedef enum { 
    BUTTON_HALL_UP      = 0,
    BUTTON_HALL_DOWN    = 1,
    BUTTON_CAB          = 2,
    BUTTON_NONE         = 3
} ButtonType;

/**
 * @brief Called to set up communication between the microcontroller used 
 * and the physical elevator.
 */
void elevio_init(void);

/**
 * @brief Sets the motor to drive the elecator in a given direction.
 * 
 * @param[in] dirn      Motor direction.
 */
void elevio_motorDirection(MotorDirection dirn);

/**
 * @brief Sets lamp on a given @p floor and @p button to @p value.
 * 
 * @param[in] floor     Floor.
 * @param[in] button    Type of button.
 * @param[in] value     Value of lamp. On/off: 1/0.
 */
void elevio_buttonLamp(int floor, ButtonType button, int value);


/**
 * @brief 
 * 
 * @param[in] floor 
 */
void elevio_floorIndicator(int floor);


/**
 * @brief 
 * 
 * @param[in] value 
 */
void elevio_doorOpenLamp(int value);
void elevio_stopLamp(int value);

int elevio_callButton(int floor, ButtonType button);
int elevio_floorSensor(void);
int elevio_stopButton(void);
int elevio_obstruction(void);

