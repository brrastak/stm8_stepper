
//user
#include "gpio.h"


// Input floating/analog
void InitPinAsIf(GPIO_TypeDef* port, int pin)
{
    port->DDR &= ~(1 << pin);
    port->CR1 &= ~(1 << pin);
    port->CR2 &= ~(1 << pin);
}
// Output push-pull
void InitPinAsOpp(GPIO_TypeDef* port, int pin)
{
    port->DDR |= 1 << pin;
    port->CR1 |= 1 << pin;
}
// Output open drain
void InitPinAsOd(GPIO_TypeDef* port, int pin)
{
    port->DDR |= 1 << pin;
    port->CR1 &= ~(1 << pin);
}
bool GetPinState(GPIO_TypeDef* port, int pin)
{
    return ((port->IDR & (1 << pin)) != 0);
}
void SetPin(GPIO_TypeDef* port, int pin)
{
    port->ODR |= (1 << pin);
}
void ResetPin(GPIO_TypeDef* port, int pin)
{
    port->ODR &= ~(1 << pin);
}
void SwitchPin(GPIO_TypeDef* port, int pin)
{
    if (GetPinState(port, pin))
        ResetPin(port, pin);
    else
        SetPin(port, pin);
}

