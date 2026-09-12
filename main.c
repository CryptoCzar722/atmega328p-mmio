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
        // // {
        // uint8_t data = twi_write(0x22, 0x01);
        // // uint8_t data = twi_write(addr, 0x00);
        // // uint8_t data = twi_write_reg(addr, 0x00, 0x00);
        // if (data == 0 || data == 3)
        //     {
        //     uint8_t twi_ascii = data + '0';   // 0 -> '0' (0x30), 1 -> '1' (0x31)
        //     uart_print(twiStr, 9);
        //     uart_write(&twi_ascii, 1);
        //     uart_print(new_line, 2);
        //     }
        //     _delay_ms(10);
        // // }

    // uint8_t twiCount = twi_scan();
    // while(1)
    //     {
    //     uint8_t twi_ascii = twiCount + '0';   // 0 -> '0' (0x30), 1 -> '1' (0x31)
    //     uart_print(twiStr, 11);
    //     uart_write(&twi_ascii, 1);
    //     uart_print(new_line, 2);
    //     _delay_ms(1000);
    //     }

    while(1) 
        {
        // uint8_t p5 = gpio_read(POIN_D, 5);
        // if (!p5) gpio_write(1);
        // else gpio_write(0);
        // gpio_write(POIN_B, 5, p5);

        uint8_t mcp_a0 = mcp_read(0,0);
        uart_print(gpioStr, 4, 0);
        uint8_t p5_ascii = mcp_a0 + '0';   // 0 -> '0' (0x30), 1 -> '1' (0x31)
        uart_write(&p5_ascii, 1, 1);
 
        gpio_toggle(PORT_B, 5);
       _delay_ms(500);      // Delay 500 ms
        // for (uint16_t delay = 0; delay < 50000; delay++){
        //     __asm__("nop");
        // }
        }
    }
