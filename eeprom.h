
#ifndef __EEPROM_H__
#define __EEPROM_H__


// Set default rotate speed value into EEPROM for next power on
void SaveAsDefaultValue(uint8_t);
// Get previously saved value from EEPROM
uint8_t GetDefaultValue(void);


#endif