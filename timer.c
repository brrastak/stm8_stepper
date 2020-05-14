// STM8S103F3
#include "stm8s.h"

//user
#include "timer.h"
#include "debug_led.h"

// Global variables
volatile uint32_t sys_tick = 0;

// Local functions
void _delay_ms(uint16_t ms); // max 500ms

// TIM4 update interrupt
#pragma vector = 25 // TIM4 interrupt vector (number from datasheet + 2)
__interrupt void SysTick()
{
    if (TIM4->SR1 & TIM4_SR1_UIF) { // update
        sys_tick++;
    }
    TIM4->SR1 = 0;  // clear flags
}

// Init TIM4 as SysTick timer
void InitSysTick()
{
    TIM4->PSCR = 4;                     // 1MHz : 16MHz/2^4
    TIM4->ARR  = 50;                    // 20kHz
    TIM4->IER = TIM4_IER_UIE;           // update interrupt enable
    TIM4->EGR = TIM4_EGR_UG;            // update
    TIM4->SR1 &= ~TIM4_SR1_UIF;         // clear update flag
    TIM4->CR1 |= TIM4_CR1_CEN;          // start
    TIM4->SR1 &= ~TIM4_SR1_UIF;         // clear update flag
}
// Delay TIM2
void delay_ms(uint32_t ms)
{
    volatile uint32_t i;
    
    if (ms == 0) return;
    if (ms <= 500) {
        _delay_ms(ms);
        return;
    }
    for (i = (ms / 500); i > 0; i--)
        _delay_ms(500);
    if (ms % 500 == 0)
        return;
    _delay_ms(ms % 500);
}

void _delay_ms(uint16_t ms) // max 500ms
{
    uint16_t time = ms * 125; 
    
    TIM2->CR1 = TIM2_CR1_ARPE |         // auto-load preload enable
                TIM2_CR1_OPM;           // one-pulse mode
    TIM2->PSCR = 7;                     // 125kHz
    TIM2->ARRH = time >> 8;
    TIM2->ARRL = time & 0xff;
    TIM2->EGR = TIM2_EGR_UG;            // update
    TIM2->SR1 &= ~TIM2_SR1_UIF;         // clear update flag
    TIM2->CR1 |= TIM2_CR1_CEN;          // start
    TIM2->SR1 &= ~TIM2_SR1_UIF;
    while (!(TIM2->SR1 & TIM2_SR1_UIF))
        ;
    TIM2->CR1 &= ~TIM2_CR1_CEN;         // counter disable
    TIM2->SR1 &= ~TIM2_SR1_UIF;         // clear update flag
}


void delay_us(uint16_t us)  // max 60000us
{   
    TIM2->CR1 = TIM2_CR1_ARPE |         // auto-load preload enable
                TIM2_CR1_OPM;           // one-pulse mode
    TIM2->PSCR = 4;                     // 1MHz
    TIM2->ARRH = us >> 8;
    TIM2->ARRL = us & 0xff;
    TIM2->EGR = TIM2_EGR_UG;            // update
    TIM2->SR1 &= ~TIM2_SR1_UIF;         // clear update flag
    TIM2->CR1 |= TIM2_CR1_CEN;          // start
    TIM2->SR1 &= ~TIM2_SR1_UIF;
    while (!(TIM2->SR1 & TIM2_SR1_UIF))
        ;
    TIM2->CR1 &= ~TIM2_CR1_CEN;         // counter disable
    TIM2->SR1 &= ~TIM2_SR1_UIF;         // clear update flag
}
