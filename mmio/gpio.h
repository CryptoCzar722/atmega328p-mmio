#ifndef GPIO_H_
#define GPIO_H_

#include "stdint.h"

typedef struct 
  {
  volatile uint8_t * portin; // data input register
  volatile uint8_t * ddr; // data direction register
  volatile uint8_t * port; //memory to port pins 
  }IO;


enum port { 
  PORT_B = 0,
  PORT_C,
  PORT_D,
};

enum portin{
  POIN_B = 0,
  POIN_C,
  POIN_D,
};

enum port_out {
  POUT_B = 1,
  POUT_C,
  POUT_D
};

void gpio_open();
// void gpio_write();
// void gpio_write(uint8_t set);
void gpio_toggle(uint8_t port, uint8_t pin);
void gpio_write(uint8_t port, uint8_t pin, uint8_t state);
uint8_t gpio_read(uint8_t port, uint8_t pin);


#endif