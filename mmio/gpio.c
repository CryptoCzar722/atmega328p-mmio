#include "gpio.h"

#include <stddef.h>

IO IO_B  = 
  {
  .portin = (volatile uint8_t *)0x23,
  .ddr    = (volatile uint8_t *)0x24, 
  .port   = (volatile uint8_t *)0x25
  };

IO IO_C  = 
  {
  .portin = (volatile uint8_t *)0x26,
  .ddr    = (volatile uint8_t *)0x27, 
  .port   = (volatile uint8_t *)0x28
  };

IO IO_D  = 
  {
  .portin = (volatile uint8_t *)0x29,
  .ddr    = (volatile uint8_t *)0x2A, 
  .port   = (volatile uint8_t *)0x2B
  };


void gpio_open()
  {
  // *(volatile uint8_t *)0x24 = 1 << 5;
  *IO_B.ddr |= 1 << 5;
  *IO_D.ddr &= ~(1 << 5);
  }

void gpio_write2(uint8_t set)
    { //uint8_t port, uint8_t pin){
    if (set) *IO_B.port |= 1 << 5;
    else *IO_B.port &= ~(1 << 5);
    }

void gpio_toggle(uint8_t port, uint8_t pin)
    { 
    volatile uint8_t * port_mem = NULL;
    switch (port)
        {
        case PORT_B:
            port_mem = IO_B.port;
            // *IO_B.port ^= 1<<pin;
            break;
        case PORT_C:
            port_mem = IO_C.port;
            break;
        case PORT_D:
            port_mem = IO_D.port;
            break;
        }   
    if(port_mem == NULL) return;  
    *port_mem ^= 1<<pin;
    }


void gpio_write(uint8_t port, uint8_t pin, uint8_t state)
    { 
    volatile uint8_t * port_mem = NULL;
    switch (port)
        {
        case PORT_B:
            port_mem = IO_B.port;
            break;
        case PORT_C:
            port_mem = IO_C.port;
            break;
        case PORT_D:
            port_mem = IO_D.port;
            break;
        }   
    if(port_mem == NULL) return; 
    if (state) *port_mem |= 1<<pin;
    else *port_mem &= ~(1 << pin);
    }


uint8_t gpio_read(uint8_t portin, uint8_t pin)
    { 
    volatile uint8_t port_mem;
    switch (portin)
        {
        case POIN_B:
            port_mem = *IO_B.portin;
            break;
        case POIN_C:
            port_mem = *IO_C.portin;
            break;
        case POIN_D:
            port_mem = *IO_D.portin;
            break;
        }    
    uint8_t mem_read = (port_mem >> pin) & 0x01;
    return mem_read;
    }