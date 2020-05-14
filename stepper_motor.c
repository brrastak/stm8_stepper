
//user
#include "stepper_motor.h"
#include "main.h"
#include "gpio.h"

// Local types
// Coil A and B state
// 0: disable; 1, -1: two current directions
typedef struct
{
    int a;
    int b;
}
output_t;

// Local constants
// Step states for different modes
static const output_t wave_steps[4] =
{
    // A:   B:
    { 1,    0},
    { 0,    1},
    {-1,    0},
    { 0,   -1}
};
static const output_t fullstep_steps[4] =
{
    // A:   B:
    { 1,    1},
    {-1,    1},
    {-1,   -1},
    { 1,   -1}
};
static const output_t halfstep_steps[8] =
{
    // A:   B:
    { 1,    0},
    { 1,    1},
    { 0,    1},
    {-1,    1},
    {-1,    0},
    {-1,   -1},
    { 0,   -1},
    { 1,   -1}
};

// Local variables
// Current stepper control mode
static stepper_mode_t current_mode = fullstep_mode;
// Current stepper direction
static stepper_dir_t current_dir = clockwise_dir;
// Step counter
static int current_step = 0;

// Local function prototypes
// Set output state depending on current step
void SetOutput(const output_t * step_mode, int step);

// Set current control mode and direction
void SetStepperControlMode(stepper_mode_t new_mode, stepper_dir_t new_dir)
{
    current_mode = new_mode;
    current_dir = new_dir;
    ResetStep();
}
// Set outputs state depending on current control mode
void DoNextStep(void)
{
    int i;
    int max;
    
    // Max number of steps
    if (current_mode == halfstep_mode)
        max = 7;
    else
        max = 3;
    
    // Choose direction
    if (current_dir == clockwise_dir)
        i = current_step;
    else
        i = max - current_step;
    
    switch (current_mode)
    {
    case wave_mode:
        SetOutput(wave_steps, i);
        break;
    case fullstep_mode:
        SetOutput(fullstep_steps, i);
        break;
    case halfstep_mode:
        SetOutput(halfstep_steps, i);
        break;
    }
    
    current_step++;
    if (current_step > max)
        current_step = 0;
}
// Start stepping from the beginning
void ResetStep(void)
{
    current_step = 0;
}
// Set output state depending on current step
void SetOutput(const output_t * step_mode, int step)
{
    // coil A
    switch (step_mode[step].a)
    {
    case 0:
        ResetPin(STEP_A_PIN);
        ResetPin(STEP_C_PIN);
        break;
    case 1:
        SetPin(STEP_A_PIN);
        ResetPin(STEP_C_PIN);
        break;
    case -1:
        ResetPin(STEP_A_PIN);
        SetPin(STEP_C_PIN);
        break;
    }
    // coil B
    switch (step_mode[step].b)
    {
    case 0:
        ResetPin(STEP_B_PIN);
        ResetPin(STEP_D_PIN);
        break;
    case 1:
        SetPin(STEP_B_PIN);
        ResetPin(STEP_D_PIN);
        break;
    case -1:
        ResetPin(STEP_B_PIN);
        SetPin(STEP_D_PIN);
        break;
    }
    
}

