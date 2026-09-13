#include "mcp23017.h"

void mcp23017_open()
    {
    // Set reset pin high.
    gpio_pin_open(PORT_C, 0, 1, 0);
    gpio_write(PORT_C, 0, 1);

    _delay_ms(10);

    twi_write_reg(ADDR, IODIRA, 0b00001111); //input A0
    twi_write_reg(ADDR, 0x0C, 0b00001111);    //pullup A0
    }

uint8_t mcp_read(uint8_t port, uint8_t pin)
    {
    uint8_t reg = 0;
    switch (port)
        {
        case A:
            reg = GPIOA;
            break;
        case B:
            reg = GPIOB;
            break;
        default:
            return 0xFF;
        }
    uint8_t gpio;
    twi_read_reg(ADDR, reg, &gpio);    //pullup A0
    return ( 0x01 & gpio);
    }

uint8_t mcp_write(uint8_t port, uint8_t pin, uint8_t state)
    {   
    uint8_t reg = 0;
    switch (port)
        {
        case A:
            reg = GPIOA;
            break;
        case B:
            reg = GPIOB;
            break;
        default:
            return 0xFF;
        } 
    uint8_t gpio;
    twi_read_reg(ADDR, reg, &gpio);    //pullup A0

    if (state) gpio |= (1 << pin);
    else gpio &= ~(1 << pin);

    twi_write_reg(ADDR, reg, gpio);

    return 1;
    }


    