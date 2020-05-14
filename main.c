// STM8S103F3
#include "stm8s.h"

// cstd
#include <stdbool.h>

// user
#include "main.h"
#include "init.h"
#include "timer.h"
#include "stepper_motor.h"
#include "stepper_func.h"
#include "debug_led.h"
#include "adc.h"
#include "i2c.h"
#include "display.h"
#include "button.h"
#include "encoder.h"
#include "eeprom.h"
#include "wdt.h"


// Print num and '%' at display
void PrintPercent(uint8_t num);
char disp_buf[4];


int main()
{
    InitRcc();
    InitGpio();
    InitAdc();
    InitSysTick();
    InitI2C();
    InitInterrupt();
    
    delay_ms(500);
    InitDisp();
    delay_ms(10);
    
    InitWdt();
   
    
    // Button (in encoder)
    btn_t Btn = {BTN_PIN, 0, 20, false, false, false};
    // Encoder
    enc_t Enc = {ENC_A_PIN, ENC_B_PIN, 0, 0, 0, 100, 2};

    // Should update display
    bool disp_update = true;
    // Stepper speed value (0% - 100%)
    uint8_t procent_value = GetDefaultValue();
    SetEncoderValue(&Enc, procent_value); 
    
    
    // Time counter for next stepper step
    uint32_t step_counter = sys_tick;
    // Led blink time counter
    uint32_t led_counter = sys_tick;
    // PWM time counters
    uint32_t a_pwm_counter = sys_tick;
    uint32_t b_pwm_counter = sys_tick;
    // Time counter for button and encoder check
    uint32_t btn_counter = sys_tick;
    
    // Coils current value
    uint32_t a_current, b_current;
    
    // Wait at least 7us after ADC init
    /*while (sys_tick - led_counter < 2)
        ;*/
    
    // Enable coils
    EnableA();
    EnableB();
    
    SetStepperControlMode(halfstep_mode, clockwise_dir);
    
    while (true) {
        
        ResetWdt();
        
        // Stepping
        if (sys_tick - step_counter > (800 / (procent_value+2) +2)) {

        	step_counter = sys_tick;
            DoNextStep();
        }
        
        // Current limiting
        a_current = GetCurrentA();
        b_current = GetCurrentB();
        if (a_current > I_OFF_A) {
            
            // Start count for switch off
            a_pwm_counter = sys_tick;
            DisableA();
        }
        if (b_current > I_OFF_B) {
            
            // Start count for switch off
            b_pwm_counter = sys_tick;
            DisableB();
        }
        
        
        // Turn on again after current limiting
        if (sys_tick - a_pwm_counter > 2) {
            
            a_pwm_counter = sys_tick;
            EnableA();
        }
        if (sys_tick - b_pwm_counter > 2) {
            
            b_pwm_counter = sys_tick;
            EnableB();
        }
        
        // Check button and encoder state
        if (sys_tick - btn_counter > 20) {  // every 1ms
            
            CheckBtn(&Btn);
            CheckEncoder(&Enc);
        }
        // Button press proceed
        if (WasPressed(&Btn)) {
            
            SaveAsDefaultValue(procent_value);
        }
        // Encoder rotation proceed
        if (GetEncoderValue(&Enc) != procent_value) {
            
            procent_value = GetEncoderValue(&Enc);
            disp_update = true;
        }
        // Update display
        if (disp_update == true) {
            
            // Switch off stepper
            DisableA();
            DisableB();
            
            // Print value
            PrintPercent(procent_value);
            disp_update = false;
        }
        
    }
    
}


// Print num and '%' at display
void PrintPercent(uint8_t num)
{   
    bool more_then_hundred;
    
    more_then_hundred = num > 99;
    if (more_then_hundred) {
        
        disp_buf[0] = '0' + num / 100;
        num %= 100;
    }
    else
        disp_buf[0] = ' ';
    if ((num > 9)|| more_then_hundred) {
        
        disp_buf[1] = '0' + num / 10;
        num %= 10;
    }
    else
        disp_buf[1] = ' ';
    disp_buf[2] = '0' + num;
    disp_buf[3] = '%';
    
    // Display
    MoveTo(6, 0);
    WriteString(disp_buf, 4);
}



