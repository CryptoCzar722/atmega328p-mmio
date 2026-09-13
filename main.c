// #define F_CPU 16000000UL // 16 MHz clock speed
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
//
#include "mmio/gpio.h"
#include "mmio/uart.h"
#include "mmio/twi.h"
//
#include "drivers/mcp23017.h"


// #define STR_LEN 13
// char str[STR_LEN] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\n','\r'};

char gpioStr[4] = {'B', '5', '-','>'};
// char twiStr[11] = {'T', 'W', 'I', ' ', 'c', 'o', 'u', 'n', 't','-','>' };
char twiStr[9] = {'T', 'W', 'I', ' ', 'D', 'e', 'v','-','>' };

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
    // for (uint8_t addr = 1; addr < 127; addr++)
    //     {
    //     // uint8_t data = twi_write(0x22, 0x01);
    //     // uint8_t data = twi_write(addr, 0x00);
    //     uint8_t data = twi_write_reg(addr, 0x00, 0x00);
    //     if (data == 0 || data == 3)
    //         {
    //         uint8_t twi_ascii = addr + '0';   // 0 -> '0' (0x30), 1 -> '1' (0x31)
    //         uart_print(twiStr, 9,0);
    //         uart_write(&twi_ascii, 1,1);
    //         }
    //         _delay_ms(10);
    //     }


    while(1) 
        {
        static uint8_t lastButton = 0;
        static uint8_t toggle = 0;
        static uint8_t write_once = 0;

        uint8_t button = mcp_read(0,0); 
        uint8_t p5_ascii = button + '0';   // 0 -> '0' (0x30), 1 -> '1' (0x31)
        uart_print(gpioStr, 4, 0);
        uart_write(&p5_ascii, 1, 1);

        
        if (!button && lastButton)
            {
            toggle = !toggle;
            lastButton = 0;
            }
        else if (button && !lastButton) 
            {
            lastButton = 1;
            }
        //
        if (toggle && !write_once)
            {
            write_once = 1;
            gpio_write(PORT_B, 5, 1);    
            mcp_write(1,1,1);
            }
        else if (!toggle && write_once) 
            {
            write_once = 0;
            gpio_write(PORT_B, 5, 0);  
            mcp_write(1,1,0);  
            }
       _delay_ms(500);      // Delay 500 ms
        }
    }
