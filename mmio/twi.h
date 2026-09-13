#ifndef TWI_H_
#define TWI_H_
#include "gpio.h"
#include <stdint.h>

/**************************************************************************
Status codes
***************************************************************************/

#define TWI_START           0x08  // START condition transmitted
#define TWI_REP_START       0x10  // repeated START transmitted
#define TWI_MT_SLA_ACK      0x18  // SLA+W transmitted, ACK received
#define TWI_MT_SLA_NACK     0x20 // SLA+W transmitted, NACK received
#define TWI_MT_DATA_ACK     0x28 // data byte transmitted, ACK received
#define TWI_MT_DATA_NACK    0x30 // data byte transmitted, NACK received
#define TWI_MR_SLA_ACK      0x40
#define TWI_MR_DATA_NACK    0x58

/**************************************************************************
Memory bit fields
***************************************************************************/

enum twamr{
    twam0 = 1,
    twam1,
    twam2,
    twam3,
    twam4,
    twam5,
    twam6,
};

enum twcr{
    twie = 0,
    tempty,
    twen,
    twwc,
    twsto,
    twsta,
    twea,
    twint,
};


/**************************************************************************
Pin setup structures
***************************************************************************/

typedef struct {
    pin_data clock; //PC5
    pin_data data;  //PC4
}twi_pins;

/**************************************************************************
Memory address structures
***************************************************************************/


typedef struct{
    volatile uint8_t * twamr; // slave address mask register
    volatile uint8_t * twcr;  // control register
    volatile uint8_t * twdr;  // data register
    volatile uint8_t * twar;  // address register
    volatile uint8_t * twsr;  // status register
    volatile uint8_t * twbr;  // bitrate register
}TWI;

/**************************************************************************
Function calls
***************************************************************************/


void twi_open();
uint8_t twi_write(uint8_t address, uint8_t data);
uint8_t twi_read(uint8_t address, uint8_t * data_rd);
//
uint8_t twi_write_reg(uint8_t address, uint8_t reg, uint8_t data);
uint8_t twi_read_reg(uint8_t address, uint8_t reg, uint8_t *data);

#endif