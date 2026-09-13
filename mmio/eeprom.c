#include "eeprom.h"
#include <avr/io.h>

#define eecr    *(volatile uint8_t *)0x3F
#define eedr    *(volatile uint8_t *)0x40
#define eearl   *(volatile uint8_t *)0x41
#define eearh   *(volatile uint8_t *)0x42

void eeprom_write(uint16_t address, uint8_t data)
    {
    while(eecr & (1<<eepe));

    eearl = address & 0xFF;
    eearh = address >> 8;
    eedr = data;
    eecr |= (1 << eempe);
    eecr |= (1 << eepe);

    _delay_ms(1);
    }

uint8_t eeprom_read(uint16_t address)
    {
    while(eecr & (1<<eepe));
    
    eearl = address & 0xFF;
    eearh = address >> 8;
    
    eecr |= (1 << eere);
    _delay_ms(1);
    return eedr;
    
    }
