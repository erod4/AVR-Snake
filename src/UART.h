#ifndef UART_H
#define UART_H

/**
 * Initialize UART
 */
void UART_init(void);

/**
 * Transmits data via UART for logging messages
 * @param message is message we wish to print
 */
void transmit(char *message);

/**
 * Receives data via UART
 */
void receive(void);


#endif