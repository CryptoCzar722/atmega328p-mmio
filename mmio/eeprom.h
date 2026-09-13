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


void eeprom_write(uint16_t address, uint8_t data);
uint8_t eeprom_read(uint16_t address);
void eeprom_write_test(uint16_t address, uint8_t data);


#endif
