#ifndef MCP_H_
#define MCP_H_

#include <util/delay.h>
#include "../mmio/gpio.h"
#include "../mmio/twi.h"
#include "../mmio/uart.h"


enum portA
    {
    IODIRA = 0,
    IPOLA,
    GPINTENA,
    DEFVALA,
    INTCONA,
    IOCONA,
    GPPUA,
    INTFA,
    INTCAPA,
    GPIOA,
    OLATA,
    };

enum portB
    {
    IODIRB = 0x10,
    IPOLB,
    GPINTENB,
    DEFVALB,
    INTCONB,
    IOCONB,
    GPPUB,
    INTFB,
    INTCAPB,
    GPIOB,
    OLATB,
    };

#define ADDR    0x20
#define ADDR_1  0x21
#define ADDR_2  0x22
#define ADDR_4  0x24

void mcp23017_open();
uint8_t mcp_read(uint8_t port, uint8_t pin);


#endif