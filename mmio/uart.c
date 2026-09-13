#include "uart.h"

char new_line[2] = {'\n','\r'};

UART serial = 
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

void uart_printf(char *str, ...)
  {
  // snprintf();
  }

void uart_print(char *str, uint8_t len, uint8_t newline)
  {
  for (int i = 0; i < len; i++)
    {
    while (!(*serial.ucsr0a & (1 << 5)));
    *serial.udr0 = str[i];
    }

    if (newline)
      {
      while (!(*serial.ucsr0a & (1 << 5)));
      *serial.udr0 = '\n';
      while (!(*serial.ucsr0a & (1 << 5)));
      *serial.udr0 = '\r';
      }
  }

void uart_write(uint8_t *str, uint8_t len, uint8_t newline)
  {
  for (int i = 0; i < len; i++)
    {
    while (!(*serial.ucsr0a & (1 << 5)));
    *serial.udr0 = str[i];
    }

    if (newline)
      {
      while (!(*serial.ucsr0a & (1 << 5)));
      *serial.udr0 = '\n';
      while (!(*serial.ucsr0a & (1 << 5)));
      *serial.udr0 = '\r';
      }
  }

  void uart_write_hex(uint8_t value, uint8_t newline)
    {
    char str[2] = {'0','x'};
    static const char hex_digits[] = "0123456789ABCDEF";
    uint8_t buf[2];
    buf[0] = hex_digits[(value >> 4) & 0x0F];
    buf[1] = hex_digits[value & 0x0F];
    uart_print(str,2,0);
    uart_write(buf, 2, newline);
    }


