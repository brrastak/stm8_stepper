
// user
#include "init.h"
#include "main.h"
#include "gpio.h"


// Init interrupts
void InitInterrupt(void)
{
    EnableInterrupt();
}
void EnableInterrupt(void)
{
    asm("rim");     // interrupt enable
}
void DisableInterrupt(void)
{
    asm("sim");     // interrupt disable
}
// Init GPIO
void InitGpio(void)
{
    // Stepper control pins
    InitPinAsOpp(STEP_A_PIN);
    InitPinAsOpp(STEP_B_PIN);
    InitPinAsOpp(STEP_C_PIN);
    InitPinAsOpp(STEP_D_PIN);
    
    // Coils A and B enable
    InitPinAsOpp(EN_A_PIN);
    InitPinAsOpp(EN_B_PIN);
    
    // Current sense pins
    InitPinAsIf(A_SENSE_PIN);
    InitPinAsIf(B_SENSE_PIN);  
    
    // Onboard LED  
    InitPinAsOpp(LED_PIN);
    
    // I2C
    InitPinAsOd(I2C_SCL_PIN);
    InitPinAsOd(I2C_SDA_PIN);
    
    // Button (in encoder) pin
    InitPinAsIf(BTN_PIN);
    // Encoder pins
    InitPinAsIf(ENC_A_PIN);
    InitPinAsIf(ENC_B_PIN);
                
}

// Init clock
void InitRcc(void)
{
    // f_master = f_HSI (16MHz)
    CLK->CKDIVR = 0;
}

