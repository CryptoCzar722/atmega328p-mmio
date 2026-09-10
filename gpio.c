#include "gpio.h"


// enum port { 
//   PORT_B,
//   PORT_C,
//   PORT_D,
// }

// enum {
//   POIN_B,
//   POIN_C,
//   POIN_D,
// }
// enum port_out {
//   POUT_B,
//   POUT_C,
//   POUT_D
// }

IO IO_B  = 
  {
  // .portin = 0x23,
  .ddr = 0x24, 
  .port = 0x25
  };

// IO IOC  = 
//   {
//   .portin = 0x26
//   .ddr = 0x27, 
//   .port = 0x28
//   };

// IO IOD  = 
//   {
//   .portin = 0x29,
//   .ddr = 0x2A, 
//   .port = 0x2B
//   };


void gpio_open()
  {
  // *(volatile uint8_t *)0x24 = 1 << 5;
  *IO_B.ddr |= 1 << 5;
  }

void gpio_write(){ //uint8_t port, uint8_t pin){
  // PORTB ^= 1 << PB5;
  // *(volatile uint8_t *)0x25 ^= 1 << 5;
  // case 
  *IO_B.port ^= 1 << 5;
}