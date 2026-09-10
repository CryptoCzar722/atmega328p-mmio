// #define F_CPU 16000000UL // 16 MHz clock speed
#include <avr/io.h>
#include <util/delay.h>
//
#include "gpio.h"
#include "uart.h"


#define STR_LEN 13
char str[STR_LEN] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\n','\r'};


int main(void) {
    gpio_open();
    uart_open();

    while(1) {
        gpio_write();
        uart_print(str, STR_LEN);
        uart_print(str, STR_LEN);
        _delay_ms(500);      // Delay 500 ms
    }
}
