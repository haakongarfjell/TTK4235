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
 * @brief Sets lamp on a given @p floor and @p button to given @p value.
 * 
 * @param[in] floor     Floor to turn on button lamp at.
 * @param[in] button    Type of button.
 * @param[in] value     Value of button lamp. On/off: 1/0.
 */
void elevio_buttonLamp(int floor, ButtonType button, int value);


/**
 * @brief Turns on lamp at a given @p floor
 * 
 * @param[in] floor     Floor to turn on lamp at.
 */
void elevio_floorIndicator(int floor);


/**
 * @brief Sets door lamp to given @p value.
 * 
 * @param[in] value     Value of door lamp. On/off: 1/0.
 */
void elevio_doorOpenLamp(int value);

/**
 * @brief Sets stop lamp to given @p value.
 * 
 * @param[in] value     Value of stop lamp. On/off: 1/0.
 */
void elevio_stopLamp(int value);

/**
 * @brief Checks if a button has been pressed on a given @p floor.
 * 
 * @param floor     Floor to check button press at.
 * @param button    Type of button pressed
 * @return 1 if a button has been pressed, 0 if not.
 */
int elevio_callButton(int floor, ButtonType button);


/**
 * @brief Reads from the floor sensor and returns the position of the
 * elevator.
 * 
 * @return 0 to 3, where 0 is the ground floor and 3 is the top.
 */
int elevio_floorSensor(void);

/**
 * @brief Checks if the emergency stop button has been pressed.
 * 
 * @return 1 if pressed, 0 if not.
 */
int elevio_stopButton(void);


/**
 * @brief Checks if obstruction switch is activated.
 * 
 * @return 1 if activated, 0 otherwise.
 */
int elevio_obstruction(void);

