// #define F_CPU 16000000UL // 16 MHz clock speed
#include <avr/io.h>
#include <util/delay.h>
//
#include "gpio.h"


int main(void) {
    gpio_open();

    while(1) {
        gpio_write();
        _delay_ms(500);      // Delay 500 ms
    }
}
