/*
    1. Configure LED_PIN as output push-pull
*/

#ifndef __DEBUG_LED_H__
#define __DEBUG_LED_H__

//#define LED_PIN                 GPIOB, 5

// Onboard LED
void TurnLedOn(void);
void TurnLedOff(void);
void BlinkLed(void);

#endif