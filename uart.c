#include "uart.h"

UART serial  = 
  {
  .prr    = (volatile uint8_t *)0x64, 
  .ubrr0h = (volatile uint8_t *)0xC5,  
  .ubrr0l = (volatile uint8_t *)0xC4,
  .ucsr0c = (volatile uint8_t *)0xC2,
  .ucsr0b = (volatile uint8_t *)0xC1,
  .ucsr0a = (volatile uint8_t *)0xC0,
  .udr0   = (volatile uint8_t *)0xC6
  };

void uart_open()
  {
  //serial ensure enabled
  *serial.prr &= 0 << 1; 
  // set baud 9600
  *serial.ubrr0h = BAUD_9600 >> 8;
  *serial.ubrr0l = BAUD_9600 & 0xFF; 
  // enable TX and RX
  *serial.ucsr0b = (1 << 3) | (1 << 4);
  // Set frame and format 8 data bits, 2 stop bits
  *serial.ucsr0c = (1 << 3) | (3 << 1);
  }

void uart_print(char *str, uint8_t len)
  {
  for (int i = 0; i < len; i++)
    {
    while (!(*serial.ucsr0a & (1 << 5)));
    *serial.udr0 = str[i];
    }

  while (!(*serial.ucsr0a & (1 << 5)));
  *serial.udr0 = '\n';
  }

