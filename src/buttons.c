#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <avr/delay.h>
#include "buttons.h"

volatile uint8_t button_state = 0;

void gpio_init(void)
{
    // UP-RIGHT-DOWN-LEFT buttons
    // Data direction is input
    DDRB &= ~(1 << DDB3) & ~(1 << DDB2) & ~(1 << DDB1) & ~(1 << DDB0);
    // Enable pull up resistors
    PORTB |= (1 << PORTB3) | (1 << PORTB2) | (1 << PORTB1) | (1 << PORTB0);
    // Data direction is input
    // PAUSE/START-MENU
    DDRB &= ~(1 << DDB5) & ~(1 << DDB4);
    // Enable pull up resistors
    PORTB |= (1 << PORTB5) | (1 << PORTB4);

    // Enable Pin Change Interrupts on PB0 to PB5
    PCICR |= (1 << PCIE0);                                                                                   // Enable pin change interrupt for PCINT[7:0]
    PCMSK0 |= (1 << PCINT0) | (1 << PCINT1) | (1 << PCINT2) | (1 << PCINT3) | (1 << PCINT4) | (1 << PCINT5); // Enable PCINT for PB0 to PB5
}

bool isButtonPressed(uint8_t pin)
{
    // Button is pressed (active low)
    if (!(PINB & (1 << pin)))
    {
        // Simple debounce logic
        _delay_ms(10);
        return !(PINB & (1 << pin));
    }
    return false;
}

bool isButtonStateSet(uint8_t button_pos)
{
    if (button_state & (1 << button_pos))
    {
        // Clear the state after reading
        button_state &= ~(1 << button_pos);
        return true;
    }
    return false;
}

void clearButtonStates(void)
{
    button_state = 0;
}

ISR(PCINT0_vect)
{
    // Disable global interrupts
    cli();
    // Check each button and update the button state
    if (isButtonPressed(START_PAUSE_BUTTON))
    {
        button_state |= (1 << START_BUTTON_POS);
    }
    if (isButtonPressed(UP_BUTTON))
    {
        button_state |= (1 << UP_BUTTON_POS);
    }
    if (isButtonPressed(RIGHT_BUTTON))
    {
        button_state |= (1 << RIGHT_BUTTON_POS);
    }
    if (isButtonPressed(DOWN_BUTTON))
    {
        button_state |= (1 << DOWN_BUTTON_POS);
    }
    if (isButtonPressed(LEFT_BUTTON))
    {
        button_state |= (1 << LEFT_BUTTON_POS);
    }
    if (isButtonPressed(MENU_BUTTON))
    {
        button_state |= (1 << MENU_BUTTON_POS);
    }

    // Re-enable global interrupts
    sei();
}