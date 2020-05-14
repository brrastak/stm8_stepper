// cstd
#include <stdbool.h>

#ifndef __I2C_H__
#define __I2C_H__


void InitI2C(void);
void TransmitI2C(uint8_t addr, uint8_t* buf, int num);
bool TransmittedI2C(void);
void WaitForTransmitI2C(void);


#endif