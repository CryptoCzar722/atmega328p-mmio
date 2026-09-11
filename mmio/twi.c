#include "twi.h"

//page 225 stop/start conditions
// page 226

twi_pins i2c_pins = {
    .clock = {PORT_C, 5},
    .data = {PORT_C, 4}
};

TWI i2c = {
    .twamr = (volatile uint8_t *)0xBD,
    .twcr  = (volatile uint8_t *)0xBC,
    .twdr  = (volatile uint8_t *)0xBB,
    .twar  = (volatile uint8_t *)0xBA,
    .twsr  = (volatile uint8_t *)0xB9,
    .twbr  = (volatile uint8_t *)0xB8,
};



void twi_open()
    {
    gpio_pin_open(i2c_pins.clock.port, i2c_pins.clock.pin, 1, 1);
    gpio_pin_open(i2c_pins.data.port, i2c_pins.data.pin, 1, 1);

    *i2c.twcr |= (1 << 2);
    }

void twi_read()
    {

    }

void twi_write()
    {
    
    }