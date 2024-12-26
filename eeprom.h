#ifndef EEPROM_H
#define EEPROM_H

void write_internal_eeprom(unsigned char address, unsigned char data); //used to write data to eeprom
unsigned char read_internal_eeprom(unsigned char address);//used to read data from eeprom

#endif