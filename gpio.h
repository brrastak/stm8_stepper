// STM8S103F3
#include "stm8s.h"

// cstd
#include <stdbool.h>

#ifndef __GPIO_H__
#define __GPIO_H__


// Input floating/analog
void InitPinAsIf(GPIO_TypeDef* port, int pin);
// Output push-pull
void InitPinAsOpp(GPIO_TypeDef* port, int pin);
// Output open drain
void InitPinAsOd(GPIO_TypeDef* port, int pin);

bool GetPinState(GPIO_TypeDef* port, int pin);
void SetPin(GPIO_TypeDef* port, int pin);
void ResetPin(GPIO_TypeDef* port, int pin);
void SwitchPin(GPIO_TypeDef* port, int pin);


#endif
