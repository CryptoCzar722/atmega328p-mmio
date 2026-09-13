// #define F_CPU 16000000UL // 16 MHz clock speed
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
//
#include "mmio/gpio.h"
#include "mmio/uart.h"
#include "mmio/twi.h"
#include "mmio/eeprom.h"
//
#include "drivers/mcp23017.h"

// #define STR_LEN 13
// char str[STR_LEN] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\n','\r'};

char gpioStr[4] = {'B', '4', '-','>'};


int main(void) 
    {
    // MMIO
    gpio_open();
    uart_open();
    twi_open();
    // Drivers
    mcp23017_open();
    //give 10ms for peripheral IO
    _delay_ms(10);
    //
    uint8_t ee = eeprom_read(0);
    static uint8_t lastButton = 0;
    static uint8_t led = 0;
    static uint8_t write_once = 0;

    if (ee == 0x01)
        {
        led = 1;
        lastButton = 1;
        gpio_write(PORT_B, 5, 1);
        mcp_write(A,4,1);
        }

    while(1) 
        {        

        uint8_t button = mcp_read(0,0); 
        //
        uart_print(gpioStr, 4, 0);
        uart_write_hex(button,1);

        if (!button && lastButton)
            {
            led = !led;
            lastButton = 0;
            }
        else if (button && !lastButton) 
            {
            lastButton = 1;
            }
        //
        if (led && !write_once)
            {
            eeprom_write(0, 0x01);
            write_once = 1;
            gpio_write(PORT_B, 5, 1);
            mcp_write(A,4,1);
            }
        else if (!led && write_once) 
            {
            eeprom_write(0, 0x00);
            write_once = 0;
            gpio_write(PORT_B, 5, 0);  
            mcp_write(A,4,0);  
            }
       _delay_ms(10);      // Delay 500 ms
        }
    }
