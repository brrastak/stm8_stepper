// STM8S103F3
#include "stm8s.h"

//user
#include "timer.h"

// Global variables
volatile uint32_t sys_tick = 0;

// Local functions
void _delay_ms(uint32_t ms); // max 500ms

// TIM2 update interrupt
#pragma vector = 15 // TIM2 interrupt vector
__interrupt void SysTick()
{
    if (TIM2->SR1 & TIM2_SR1_UIF) { // update
        sys_tick++;
    }
    TIM2->SR1 = 0;  // clear flags
    TIM2->SR2 = 0;
}

// Init TIM2 as SysTick timer
void InitSysTick()
{
    TIM2->CR1 = TIM2_CR1_ARPE;          // auto-load preload enable
    TIM2->PSCR = 4;                     // 1MHz : 16MHz/2^4
    TIM2->ARRH = 0;
    TIM2->ARRL = 50;                    // 20kHz
    TIM2->IER = TIM2_IER_UIE;           // update interrupt enable
    TIM2->EGR = TIM2_EGR_UG;            // update
    TIM2->SR1 &= ~TIM2_SR1_UIF;         // clear update flag
    TIM2->CR1 |= TIM2_CR1_CEN;          // start
    TIM2->SR1 &= ~TIM2_SR1_UIF;         // clear update flag one more time
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

void _delay_ms(uint32_t ms) // max 500ms
{
    uint32_t time = ms * 125; 
    
    TIM2->CR1 = TIM2_CR1_ARPE |         // auto-load preload enable
                TIM2_CR1_OPM;           // one-pulse mode
    TIM2->PSCR = 4;                     // 125kHz
    TIM2->ARRH = time >> 8;
    TIM2->ARRL = time;
    TIM2->EGR = TIM2_EGR_UG;            // update
    TIM2->SR1 &= ~TIM2_SR1_UIF;         // clear update flag
    TIM2->CR1 |= TIM2_CR1_CEN;          // start
    TIM2->SR1 &= ~TIM2_SR1_UIF;
    while (!(TIM2->SR1 & TIM2_SR1_UIF))
        ;
    TIM2->CR1 &= ~TIM2_CR1_CEN;         // counter disable
    TIM2->SR1 &= ~TIM2_SR1_UIF;         // clear update flag
}

