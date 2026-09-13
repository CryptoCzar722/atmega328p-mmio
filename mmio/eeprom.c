#include "eeprom.h"
#include <avr/io.h>

eeprom mem = {
    .eecr  = (volatile uint8_t *)0x3F,
    .eedr  = (volatile uint8_t *)0x40,
    .eearl = (volatile uint8_t *)0x41,
    .eearh = (volatile uint8_t *)0x42,
};

void eeprom_write(uint16_t address, uint8_t data)
    {
    while(*mem.eecr & (1<<eepe));
    // must be direct MM to ensure getting written in 4 clk cycles
    *(volatile uint8_t *)0x41 = address & 0xFF;
    *(volatile uint8_t *)0x42 = address >> 8;
    *(volatile uint8_t *)0x40 = data;
    *(volatile uint8_t *)0x3F |= (1 << eempe);
    *(volatile uint8_t *)0x3F |= (1 << eepe);

    _delay_ms(1);
    }

uint8_t eeprom_read(uint16_t address)
    {
    while(*mem.eecr & (1<<eepe));
    
    *mem.eearh = address >> 8;
    *mem.eearl = address & 0xFF;

    *mem.eecr |= (1 << eere);
    _delay_ms(1);
    return *mem.eedr;
    
    }

void eeprom_write_test(uint16_t address, uint8_t data)
    {
    while (EECR & (1 << EEPE));
    EEARL = address & 0xFF;
    EEARH = address >> 8;
    EEDR = data;
    EECR |= (1 << EEMPE);
    EECR |= (1 << EEPE);
    }