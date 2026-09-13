#include "eeprom.h"

eeprom eepromMemory = {
    .eecr  = (volatile uint8_t *)0x3F,
    .eedr  = (volatile uint8_t *)0x40,
    .eearl = (volatile uint8_t *)0x41,
    .eearh = (volatile uint8_t *)0x42,
};

void eeprom_write(uint16_t address, uint8_t data)
    {
    while(*eepromMemory.eecr & (1<<eepe));

    *eepromMemory.eearl = address & 0xFF;
    *eepromMemory.eearh = address >> 8;
    *eepromMemory.eedr = data;
    //
    *eepromMemory.eecr |= (1 << eempe);
    *eepromMemory.eecr |= (1 << eepe);
    _delay_ms(1);
    }

void eeprom_read(uint8_t address)
    {
    while(*eepromMemory.eecr & (1<<eepe));

    *eepromMemory.eearl = address & 0xFF;
    *eepromMemory.eearh = address >> 8;
    
    *eepromMemory.eecr |= (1 << eere);
    _delay_ms(1);
    return *eepromMemory.eedr;
    
    }