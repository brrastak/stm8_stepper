// STM8S103F3
#include "stm8s.h"

// cstd
#include <stdbool.h>

//user
#include "i2c.h"
#include "init.h"

// Local variables
// Slave address
static uint8_t slave_addr;
// Data
static uint8_t* transmit_buf;
// Number of data
static int to_transmit = 0;
// Flags
static volatile bool transmitted = true;


// I2C interrupt
/*#pragma vector = 21 // I2C interrupt vector (number from datasheet + 2)
__interrupt void I2C_Handler()
{
    if ((I2C->SR1 & I2C_SR1_SB) != 0) {     // start bit sent
        
        (void)I2C->SR1;         // clear flag
        I2C->DR = slave_addr;   // send slave address
    }
    if ((I2C->SR1 & I2C_SR1_ADDR) != 0) {   // slave address sent
        
        (void)I2C->SR1;         // clear flags
        (void)I2C->SR3;
        
    }
    if ((I2C->SR1 & I2C_SR1_TXE) != 0) {    // send next byte
        
        if (to_transmit > 0) {  // send byte
            
            I2C->DR = transmit_buf[0];
            transmit_buf++;
            to_transmit--;
        }
        else                    // generate stop
            I2C->CR2 |= I2C_CR2_STOP;
    }
}*/

// Functions
void InitI2C(void)
{
    I2C->FREQR  = 16;       // f_master = 16MHz
    I2C->CCRL   = 160;      // 50kHz (16MHz/50kHz/2)
    I2C->TRISER = 17;       // t_rise max = 1000ns
    
    I2C->CR1 |= I2C_CR1_PE;             // peripheral enable
    /*I2C->ITR    =   I2C_ITR_ITEVTEN |   // event interrupt enable
                    I2C_ITR_ITBUFEN;    // buffer interrupt enable (for TXE event)*/
}
/*void TransmitI2C(uint8_t addr, uint8_t* buf, int num)
{
    slave_addr = addr;
    transmit_buf = buf;
    to_transmit = num;
    
    // Start generation
    I2C->CR2 |= I2C_CR2_START;
}*/
bool TransmittedI2C(void)
{
    
}
void WaitForTransmitI2C(void)
{
    
}
void TransmitI2C(uint8_t addr, uint8_t* buf, int num)
{
    slave_addr = addr;
    transmit_buf = buf;
    to_transmit = num;
    
    // Start generation
    I2C->CR2 |= I2C_CR2_START;
    
    DisableInterrupt();
    
    // Wait for start bit sending
    while ((I2C->SR1 & I2C_SR1_SB) == 0)
        ;
    (void)I2C->SR1;         // clear flag
    I2C->DR = slave_addr;   // send slave address
    
    // Wait for slave address sending
    while ((I2C->SR1 & I2C_SR1_ADDR) == 0)
        ;
    (void)I2C->SR1;         // clear flags
    (void)I2C->SR3;
      
    // Send data
    while (to_transmit > 0) {
        
        // Send data byte
        I2C->DR = transmit_buf[0];
        transmit_buf++;
        to_transmit--;
        
        // Wait for byte sending
        while ((I2C->SR1 & I2C_SR1_TXE) == 0)
            ;
    }
    // All data sent -> generate stop
    I2C->CR2 |= I2C_CR2_STOP;
    
    EnableInterrupt();
    
}

