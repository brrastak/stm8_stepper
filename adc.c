// STM8S103F3
#include "stm8s.h"

//user
#include "adc.h"
#include "main.h"

// Init ADC1
void InitAdc()
{
    // Disable shmitt triggers of analog inputs
    ADC1->TDRL |= (1 << CHANNEL_A);
    ADC1->TDRL |= (1 << CHANNEL_B);
    
    // Set right alignment of result
    ADC1->CR2 |= ADC1_CR2_ALIGN;
    
    // Enable ADC1
    ADC1->CR1 |= ADC1_CR1_ADON;
}
// Read ADC1
uint16_t ReadAdc(uint8_t channel)
{
    uint16_t resl, resh;
    
    // Setting channel to be converted
    ADC1->CSR &= ~ADC1_CSR_CH;
    ADC1->CSR |= (ADC1_CSR_CH & channel);
    
    // Start of convertion
    ADC1->CR1 |= ADC1_CR1_ADON;
    
    // Waiting for end of convertion
    while ((ADC1->CSR & ADC1_CSR_EOC) == 0)
        ;
    
    // Result must be right-aligned
    resl = ADC1->DRL;
    resh = ADC1->DRH;
    
    // Clear EOC flag
    ADC1->CSR &= ~ADC1_CSR_EOC;
    
    return ((resh << 8) + resl);
}

