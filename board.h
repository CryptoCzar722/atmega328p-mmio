#ifndef BOARD_H_
#define BOARD_H_

#include "mmio/gpio.h"

typedef struct 
    {
    pin_data uart_tx;
    pin_data uart_rx;
    pin_data led;
    pin_data i2c_clk;
    pin_data i2c_dio;
    
    }BOARD;

BOARD boardPins = {
    .uart_tx = {.port = PORT_C, .pin = 5, .pullup = 1, .requires_init = 0},
    .uart_rx = {.port = PORT_C, .pin = 5, .pullup = 1, .requires_init = 0},

    .i2c_clk = {.port = PORT_C, .pin = 5, .pullup = 1, .requires_init = 1},
    .i2c_dio = {.port = PORT_C, .pin = 4, .pullup = 1, .requires_init = 1},
};

#endif