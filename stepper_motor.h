/*
    Define and configure STEP_A_PIN, STEP_B_PIN, STEP_C_PIN, STEP_D_PIN
    Colours:
        A: black
        C: green
        (one coil)

        B: red
        D: blue
        (another coil)
*/


#ifndef __STEPPER_MOTOR_H__
#define __STEPPER_MOTOR_H__


// Types
// Stepper control mode
typedef enum
{
    wave_mode,
    fullstep_mode,
    halfstep_mode
}
stepper_mode_t;
typedef enum
{
    clockwise_dir,
    counter_clockwise_dir
}
stepper_dir_t;

// Functions
// Set current control mode and direction
void SetStepperControlMode(stepper_mode_t, stepper_dir_t);
// Set outputs state depending on current control mode
void DoNextStep(void);
// Start stepping from the beginning
void ResetStep(void);


#endif
