#include "mcp23017.h"

void mcp23017_open()
    {
    // Set reset pin high.
    gpio_pin_open(PORT_C, 0, 1, 0);
    gpio_write(PORT_C, 0, 1);

    _delay_ms(10);
    
    // uint8_t iocon = 0;
    // twi_read_reg(ADDR_2, 0x0A, &iocon);
    // uint8_t ascii = iocon + '0';   // 0 -> '0' (0x30), 1 -> '1' (0x31)
    // uart_write(&ascii, 1, 1);
    
    // uint8_t iodir = 
    uint8_t gppua = 
    twi_write_reg(ADDR_2, IODIRA, 0b0000001); //input A0
    _delay_ms(10);
    twi_write_reg(ADDR_2, 0x0C, 0b0000001);    //pullup A0
    _delay_ms(10);
    uint8_t data_rd = 0;
    gppua = twi_read_reg(ADDR_2, GPPUA, &data_rd);    //pullup A0
    uint8_t ascii = gppua + '0';   // 0 -> '0' (0x30), 1 -> '1' (0x31)
    uart_write(&ascii, 1, 1);
    }

uint8_t mcp_read(uint8_t port, uint8_t pin)
    {
    uint8_t gpioa;
    twi_read_reg(ADDR_2, 0x12, &gpioa);    //pullup A0
    return ( 0x01 & gpioa);
    }
