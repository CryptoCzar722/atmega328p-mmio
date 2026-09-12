MCU = atmega328p
F_CPU = 16000000
PORT = /dev/cu.usbserial-14110
BAUD = 57600
PROGRAMMER = arduino

CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -Wall -g -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU)

TARGET = main
SRCS = main.c mmio/gpio.c mmio/uart.c mmio/twi.c drivers/mcp23017.c

all: $(TARGET).hex

$(TARGET).elf: $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET).elf $(SRCS)

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $(TARGET).elf $(TARGET).hex

upload: $(TARGET).hex
	avrdude -F -V -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$(TARGET).hex:i

monitor:
	screen /dev/cu.usbserial-14110

clean:
	rm -f $(TARGET).elf $(TARGET).hex
