#include "UART.h"
#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>
#define BAUD 9600
#define UBRR_VALUE ((F_CPU / 16 / BAUD) - 1)
#define BUFFER_SIZE 128
static volatile char tx_buffer[BUFFER_SIZE];
static volatile uint8_t tx_buffer_head = 0;
static volatile uint8_t tx_buffer_tail = 0;
void UART_init(void)
{
    // enable tx/rx
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    // set UBRR value into register
    // 9600 fits into the lower 8 bits of register
    UBRR0H = (unsigned char)(UBRR_VALUE >> 8);
    UBRR0L = (unsigned char)UBRR_VALUE;
    // 8 bit transmission with 1 stop bit and no parity bit
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
    // enable UDRE interrupt
    UCSR0B |= (1 << UDRIE0);
}

void transmit(char *message)
{
    uint8_t len = strlen(message);
    for (uint8_t i = 0; i < len; i++)
    {
        uint8_t next_head = (tx_buffer_head + 1) % BUFFER_SIZE;
        // wait if buffer is full
        while (next_head == tx_buffer_tail)
            ;
        tx_buffer[tx_buffer_head] = message[i];
        tx_buffer_head = next_head;
    }
    // Enable UDRE interrupt to start transmission
    UCSR0B |= (1 << UDRIE0);
}

ISR(USART_UDRE_vect)
{
    // Check if there is data to be sent
    if (tx_buffer_head != tx_buffer_tail)
    {
        // Send the next character from the buffer
        UDR0 = tx_buffer[tx_buffer_tail];
        tx_buffer_tail = (tx_buffer_tail + 1) % BUFFER_SIZE;
    }
    else
    {
        // If no more data to send, disable UDRE interrupt
        UCSR0B &= ~(1 << UDRIE0);
    }
}
