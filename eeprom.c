// STM8S103F3
#include "stm8s.h"

//user
#include "eeprom.h"

#define EEPROM_START_ADDRESS    0x004000ul
#define EEPROM_KEY1             0xAE
#define EEPROM_KEY2             0x56

// EEPROM variable address
uint8_t* default_value = (uint8_t*)EEPROM_START_ADDRESS;

// Local functions
// Enable EEPROM erasing and writing
void EnableEeprom(void);
// Disable EEPROM erasing and writing
void DisableEeprom(void);
// Wait while EEPROM erasing operation performing
void WaitEeprom(void);

// Set default rotate speed value into EEPROM for next power on
void SaveAsDefaultValue(uint8_t val)
{
    EnableEeprom();
    
    // Erase previous value
    *default_value = 0;
    WaitEeprom();
    
    // Write new value
    *default_value = val;
    
    DisableEeprom();
}
// Get previously saved value from EEPROM
uint8_t GetDefaultValue(void)
{
    return (*default_value);
}

// Enable EEPROM erasing and writing
void EnableEeprom(void)
{
    // writing enable key values
    FLASH->DUKR = EEPROM_KEY1;
    FLASH->DUKR = EEPROM_KEY2;
}
// Disable EEPROM erasing and writing
void DisableEeprom(void)
{
    FLASH->IAPSR &= ~FLASH_IAPSR_DUL;
}
// Wait while EEPROM erasing operation performing
void WaitEeprom(void)
{
    while ((FLASH->IAPSR & FLASH_IAPSR_EOP) == 0)
        ;
}

