
#ifndef __MAIN_H__
#define __MAIN_H__

// Ports and pins
// Stepper control pins
#define STEP_A_PIN              GPIOC, 7
#define STEP_B_PIN              GPIOC, 5
#define STEP_C_PIN              GPIOC, 6
#define STEP_D_PIN              GPIOC, 4
// Coils A and B enable
#define EN_A_PIN                GPIOD, 5    // coil A, C
#define EN_B_PIN                GPIOD, 4    // coil B, D
// Current sense pins
#define A_SENSE_PIN             GPIOD, 3    // coil A
#define B_SENSE_PIN             GPIOD, 2    // coil B
// Onboard LED                
#define LED_PIN                 GPIOB, 5
// I2C
#define I2C_SCL_PIN             GPIOB, 4
#define I2C_SDA_PIN             GPIOB, 5
// Button (in encoder) pin
#define BTN_PIN                 GPIOA, 3
// Encoder pins
#define ENC_A_PIN               GPIOA, 2
#define ENC_B_PIN               GPIOA, 1

// ADC channels
#define CHANNEL_A               4           // coil A
#define CHANNEL_B               3           // coil B

// ADC max value
#define ADC_MAX_VALUE           0x03fful    // 10 bits
// ADC reference voltage, mV
#define V_REF                   3300

// Current sensors resistirs value, mOhm
#define I_SENSE_RES_MOHM        220

// Current thresholds, mA
#define I_OFF_A                 800         // disable coil if >
#define I_OFF_B                 800         // disable coil if >


#endif
