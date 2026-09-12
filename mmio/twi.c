#include "twi.h"

//page 225 stop/start conditions
// page 226
// page 622 memory map

twi_pins i2c_pins = {
    .clock = {.port = PORT_C, .pin = 5},
    .data  = {.port = PORT_C, .pin = 4},
};

TWI i2c = {
    .twamr = (volatile uint8_t *)0xBD,
    .twcr  = (volatile uint8_t *)0xBC,
    .twdr  = (volatile uint8_t *)0xBB,
    .twar  = (volatile uint8_t *)0xBA,
    .twsr  = (volatile uint8_t *)0xB9,
    .twbr  = (volatile uint8_t *)0xB8,
};

void twi_open()
    {
    gpio_pin_open(i2c_pins.clock.port, i2c_pins.clock.pin, 0, 1);
    gpio_pin_open(i2c_pins.data.port, i2c_pins.data.pin, 0, 1);

    *i2c.twcr = (1 << twen); // enable twi
    *i2c.twsr &= ~((1 << 1) | (1 << 0));  // prescaler = 1
    *i2c.twbr = 72; // 100kHz

    }

uint8_t twi_write_reg(uint8_t address, uint8_t reg, uint8_t data)
    {
    //Start condition
    *i2c.twcr = (1 << twint) | (1<<twsta) | (1<<twen); // enable twi
    while (!(*i2c.twcr & (1 << twint)));  // poll int for completion
    if ((*i2c.twsr & 0xF8) != TWI_START)
        {
        *i2c.twcr = (1 << twint) | (1 << twen) | (1 << twsto);
        return 1;
        }
    //push out slave address byte
    *i2c.twdr = (address << 1) | 0;
    *i2c.twcr = (1<<twint) | (1<<twen);
    while (!(*i2c.twcr & (1 << twint)));  // poll int for completion
    if ((*i2c.twsr & 0xF8) != TWI_MT_SLA_ACK)
        {
        *i2c.twcr = (1 << twint) | (1 << twen) | (1 << twsto);
        return 2;
        }
    *i2c.twdr = reg;
    *i2c.twcr = (1<<twint) | (1<<twen);
    while (!(*i2c.twcr & (1 << twint)));  // poll for completion
    if ((*i2c.twsr & 0xF8) != TWI_MT_DATA_ACK) 
        {
        *i2c.twcr = (1 << twint) | (1 << twen) | (1 << twsto);
        return 3;
        }
    *i2c.twdr = data;
    *i2c.twcr = (1<<twint) | (1<<twen);
    while (!(*i2c.twcr & (1 << twint)));  // poll for completion
    if ((*i2c.twsr & 0xF8) != TWI_MT_DATA_ACK) 
        {
        *i2c.twcr = (1 << twint) | (1 << twen) | (1 << twsto);
        return 4;
        }
    *i2c.twcr = (1<< twint) | (1<<twen) | (1<< twsto);
    return 0;
    }

uint8_t twi_read_reg(uint8_t address, uint8_t reg, uint8_t *data)
    {
    //Start condition
    *i2c.twcr = (1 << twint) | (1<<twsta) | (1<<twen); // enable twi
    while (!(*i2c.twcr & (1 << twint)));  // poll int for completion
    if ((*i2c.twsr & 0xF8) != TWI_START) 
        {
        *i2c.twcr = (1 << twint) | (1 << twen) | (1 << twsto);    
        return 1;
        }
    //push out slave address byte
    *i2c.twdr = (address << 1) | 0;
    *i2c.twcr = (1<<twint) | (1<<twen); // NACK
    while (!(*i2c.twcr & (1 << twint)));  // poll int for completion
    if ((*i2c.twsr & 0xF8) != TWI_MT_SLA_ACK)
        {
        *i2c.twcr = (1 << twint) | (1 << twen) | (1 << twsto);
        return 2;
        }
    //push out register address byte
    *i2c.twdr = reg;
    *i2c.twcr = (1<<twint) | (1<<twen); // NACK
    while (!(*i2c.twcr & (1 << twint)));  // poll int for completion
    if ((*i2c.twsr & 0xF8) != TWI_MT_DATA_ACK) 
        {
        *i2c.twcr = (1 << twint) | (1 << twen) | (1 << twsto);
        return 3;
        }

    *i2c.twcr = (1 << twint) | (1<<twsta) | (1<<twen); // enable twi
    while (!(*i2c.twcr & (1 << twint)));  // poll int for completion
    if ((*i2c.twsr & 0xF8) != TWI_REP_START) 
        {
        *i2c.twcr = (1 << twint) | (1 << twen) | (1 << twsto);
        return 4;
        }
    
    //push out slave address byte
    *i2c.twdr = (address << 1) | 1;
    *i2c.twcr = (1<<twint) | (1<<twen); // NACK
    while (!(*i2c.twcr & (1 << twint)));  // poll int for completion
    if ((*i2c.twsr & 0xF8) != TWI_MR_SLA_ACK) 
        {
        *i2c.twcr = (1 << twint) | (1 << twen) | (1 << twsto);
        return 5;
        }
    
    //pull out slave address byte
    *i2c.twcr = (1<<twint) | (1<<twen);
    while (!(*i2c.twcr & (1 << twint)));  // poll for completion
    if ((*i2c.twsr & 0xF8) != TWI_MR_DATA_NACK) 
        {
        *i2c.twcr = (1 << twint) | (1 << twen) | (1 << twsto);
        return 6;
        }
        
    *data = *i2c.twdr;
    *i2c.twcr = (1<< twint) | (1<<twen) | (1<< twsto);
    return 0;
    }

uint8_t twi_read(uint8_t address, uint8_t * data_rd)
    {
    //Start condition
    *i2c.twcr = (1 << twint) | (1<<twsta) | (1<<twen); // enable twi
    while (!(*i2c.twcr & (1 << twint)));  // poll int for completion
    //check error
    if ((*i2c.twsr & 0xF8) != TWI_START) return 1;
    //push out slave address byte
    *i2c.twdr = (address << 1) | 1;
    *i2c.twcr = (1<<twint) | (1<<twen); // NACK
    while (!(*i2c.twcr & (1 << twint)));  // poll int for completion
    //push out data byte
    if ((*i2c.twsr & 0xF8) != TWI_MT_SLA_ACK) return 2;
    *i2c.twcr = (1<<twint) | (1<<twen);
    while (!(*i2c.twcr & (1 << twint)));  // poll for completion
    if ((*i2c.twsr & 0xF8) != TWI_MT_DATA_ACK) return 3;
    //Read byte out
    *data_rd = *i2c.twdr;
    *i2c.twcr = (1<< twint) | (1<<twen) | (1<< twsto);
    return 0;
    }

uint8_t twi_write(uint8_t address, uint8_t data)
    {
    //Start condition
    *i2c.twcr = (1 << twint) | (1<<twsta) | (1<<twen); // enable twi
    while (!(*i2c.twcr & (1 << twint)));  // poll int for completion
    //check error
    if ((*i2c.twsr & 0xF8) != TWI_START) return 1;
    //push out slave address byte
    *i2c.twdr = (address << 1) | 0;
    *i2c.twcr = (1<<twint) | (1<<twen);
    while (!(*i2c.twcr & (1 << twint)));  // poll int for completion
    //push out data byte
    if ((*i2c.twsr & 0xF8) != TWI_MT_SLA_ACK) return 2;
    // (*i2c.twsr & 0xF8);
    *i2c.twdr = data;
    *i2c.twcr = (1<<twint) | (1<<twen);
    while (!(*i2c.twcr & (1 << twint)));  // poll for completion
    if ((*i2c.twsr & 0xF8) != TWI_MT_DATA_ACK) return 3;
    *i2c.twcr = (1<< twint) | (1<<twen) | (1<< twsto);
    return 0;
    }

// Returns 0 if a device ACKs its address, 1 otherwise (no data transferred)
uint8_t twi_probe(uint8_t address)
    {
    *i2c.twcr = (1 << twint) | (1 << twsta) | (1 << twen);
    while (!(*i2c.twcr & (1 << twint)));
    if ((*i2c.twsr & 0xF8) != TWI_START) return 1;

    *i2c.twdr = (address << 1) | 0;   // SLA+W
    *i2c.twcr = (1 << twint) | (1 << twen);
    while (!(*i2c.twcr & (1 << twint)));

    uint8_t status = *i2c.twsr & 0xF8;

    // Always send STOP to release the bus, whether ACK or NACK
    *i2c.twcr = (1 << twint) | (1 << twen) | (1 << twsto);

    return (status == TWI_MT_SLA_ACK) ? 0 : 1;  
    }

uint8_t twi_scan(void)
{
    uint8_t found = 0;
    for (uint8_t addr = 1; addr < 127; addr++)
    {
        if (twi_probe(addr) == 0)
        {
            found++;
            // e.g. uart_write(&addr, 1);  // or format/print it
        }
    }
    return found;
}
