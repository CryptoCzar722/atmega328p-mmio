#ifndef GPIO_H_
#define GPIO_H_

#include "stdint.h"

typedef struct 
  {
  volatile uint8_t * portin; // data input register
  volatile uint8_t * ddr; // data direction register
  volatile uint8_t * port; //memory to port pins 
  }IO;

void gpio_open();
void gpio_write();


#endif