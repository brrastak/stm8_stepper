
// cstd
#include <stdbool.h>

// user
#include "stepper_func.h"
#include "main.h"
#include "gpio.h"
#include "adc.h"


// Coils enable/disable
void EnableA()
{
    SetPin(EN_A_PIN);
}
void DisableA()
{
    ResetPin(EN_A_PIN);
}
void EnableB()
{
    SetPin(EN_B_PIN);
}
void DisableB()
{
    ResetPin(EN_B_PIN);
}

// I sense
uint32_t GetCurrentA()
{
    uint32_t res;
    
    // Get ADC value
    res = ReadAdc(CHANNEL_A);
    // Convert into voltage, mV
    res *= V_REF;
    res /= ADC_MAX_VALUE;
    // Calculate current, mA
    res *= 1000;
    res /= I_SENSE_RES_MOHM;
    
    return res;
}
uint32_t GetCurrentB()
{
    uint32_t res;
    
    // Get ADC value
    res = ReadAdc(CHANNEL_B);
    // Convert into voltage, mV
    res *= V_REF;
    res /= ADC_MAX_VALUE;
    // Calculate current, mA
    res *= 1000;
    res /= I_SENSE_RES_MOHM;
    
    return res;
}


