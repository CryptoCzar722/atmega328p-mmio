#ifndef TWI_H_
#define TWI_H_
#include "gpio.h"
#include <stdint.h>

typedef struct {
    pin_data clock; //PC5
    pin_data data;  //PC4
}twi_pins;

typedef struct{
    volatile uint8_t * twamr; // slave address mask register
    volatile uint8_t * twcr;  // control register
    volatile uint8_t * twdr;  // data register
    volatile uint8_t * twar;  // address register
    volatile uint8_t * twsr;  // status register
    volatile uint8_t * twbr;  // bitrate register
}TWI;

void twi_open();

#endif