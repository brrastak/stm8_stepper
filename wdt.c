// STM8S103F3
#include "stm8s.h"

//user
#include "wdt.h"

// Key register values
// Enable watchgog
#define KEY_ENABLE      0xCC
// Refresh watchdog
#define KEY_REFRESH     0xAA
// Access to control registers
#define KEY_ACCESS      0x55


// Init watchdog timer
void InitWdt(void)
{
    // Enable
    IWDG->KR = KEY_ENABLE;
    // Set refresh time = 22ms
    IWDG->KR = KEY_ACCESS;
    IWDG->PR = 4;           // f = 64kHz / 64 = 1kHz
    IWDG->RLR = 22;         // T = 22ms
    // Refresh
    IWDG->KR = KEY_REFRESH;
}
// Reset watchdog timer
void ResetWdt(void)
{
    IWDG->KR = KEY_REFRESH;
}

