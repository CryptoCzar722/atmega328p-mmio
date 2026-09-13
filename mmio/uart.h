#ifndef UART_H_
#define UART_H_
// PD0 RX
// PD1 TX

#include "stdint.h"

// #define BAUD_ 207
#define BAUD_9600 103

typedef struct 
  {
  volatile uint8_t * prr;     // power reduction set 1 to disable
  volatile uint8_t * ubrr0h; // usart baud speed High
  volatile uint8_t * ubrr0l; // usart baud speed Low
  volatile uint8_t * ucsr0c; // enable mode
  volatile uint8_t * ucsr0b; // enable TX & RX 
  volatile uint8_t * ucsr0a; // 
  volatile uint8_t * udr0;   // data transmisstion register
  }UART;

void uart_open();

void uart_print(char *str, uint8_t len, uint8_t newline);
void uart_write(uint8_t *str, uint8_t len, uint8_t newline);

#endif