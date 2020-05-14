
#ifndef __TIMER_H__
#define __TIMER_H__


// Ticks
extern volatile uint32_t sys_tick;

// Init TIM4 as SysTick timer
void InitSysTick(void);
// Delay TIM2
void delay_ms(uint32_t ms);
void delay_us(uint16_t ms); // max 60000us


#endif