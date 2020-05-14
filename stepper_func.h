// STM8S103F3
#include "stm8s.h"

// cstd
#include <stdbool.h>

#ifndef __STEPPER_FUNC_H__
#define __STEPPER_FUNC_H__


// Coils enable/disable
void EnableA(void);
void DisableA(void);
void EnableB(void);
void DisableB(void);

// I sense
uint32_t GetCurrentA(void);
uint32_t GetCurrentB(void);


#endif