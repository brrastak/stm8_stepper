
#ifndef __ADC_H__
#define __ADC_H__


// Init ADC1; should wait at least 7us after it before ADC using
void InitAdc(void);
// Read ADC1
uint16_t ReadAdc(uint8_t channel);


#endif