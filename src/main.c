#include <avr/io.h>
#include <avr/interrupt.h>
#include "state_machine.h"
#include "buttons.h"
#include "UART.h"
#include "LCD.h"

int main(void)
{
    // Enable global interrupts
    sei();
    // UART_init();
    gpio_init();
    LCD_init();
    fsm_init();
    timer_init();

    while (1)
    {

        fsm_update();
    }
}
