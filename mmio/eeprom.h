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

typedef struct {
    volatile uint8_t * eecr;
    volatile uint8_t * eedr;
    volatile uint8_t * eearl;
    volatile uint8_t * eearh;
}eeprom;


void eeprom_write(uint8_t address, uint8_t data);
void eeprom_read(uint8_t address);


#endif
