#ifndef BUTTONS_H
#define BUTTONS_H
#include <avr/io.h>
#include <stdbool.h>

/**
 * Button pin macros
 */
#define LEFT_BUTTON PINB0
#define RIGHT_BUTTON PINB1
#define DOWN_BUTTON PINB2
#define UP_BUTTON PINB3
#define MENU_BUTTON PINB4
#define START_PAUSE_BUTTON PINB5
/**
 * Game control flags
 */
// Define button positions in a single byte
#define MENU_BUTTON_POS 0
#define START_BUTTON_POS 1
#define UP_BUTTON_POS 2
#define RIGHT_BUTTON_POS 3
#define DOWN_BUTTON_POS 4
#define LEFT_BUTTON_POS 5

/**
 * Button states stored in single byte
 */
extern volatile uint8_t button_state;

/**
 * Initialize up,left,right,down buttons, start, menu button
 */
void gpio_init(void);
/**
 * Timer 0 checks menu pressed button every 15ms
 */

/**
 * Checks to see if GPIO pin is high for Port B
 * @param pin to be checked
 * @return true if pin is high otherwise return false
 */
bool isButtonPressed(uint8_t pin);

/**
 *checks to see if button position is set
 @param button_pos, position of button we're checking to be set
 @return true if button pos is set, else return false
 */
bool isButtonStateSet(uint8_t button_pos);

/**
 * Clears all button flags between state transitions
 */
void clearButtonStates(void);
#endif
