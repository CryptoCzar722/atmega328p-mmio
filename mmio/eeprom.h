#ifndef EEPROM_H_
#define EEPROM_H_
#include "stdint.h"
#include <util/delay.h>

enum eecr {
    eere = 0,
    eepe,
    eempe,
    eerie,
    eepm0,
    eepm1
};

void eeprom_write(uint16_t address, uint8_t data);
uint8_t eeprom_read(uint16_t address);

#endif
