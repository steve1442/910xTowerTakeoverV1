#include "main.h"

extern pros::Controller controller;
#define LEFT_JOYSTICK pros::E_CONTROLLER_ANALOG_LEFT_Y
#define RIGHT_JOYSTICK pros::E_CONTROLLER_ANALOG_RIGHT_Y
#define INTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_L2
#define OUTTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_L1
#define LIFT_UP_BUTTON pros::E_CONTROLLER_DIGITAL_R2
#define LIFT_DOWN_BUTTON pros::E_CONTROLLER_DIGITAL_R1
#define ANGLER_TOGGLE_BUTTON pros::E_CONTROLLER_DIGITAL_A
#define HOLDER_TOGGLE_BUTTON pros::E_CONTROLLER_DIGITAL_B
#define SHIFT_KEY pros::E_CONTROLLER_DIGITAL_L2
std::int32_t controllerDigital(pros::controller_digital_e_t channel);
std::int32_t controllerAnalog(pros::controller_analog_e_t channel);

extern pros::ADIGyro gyro;

extern pros::ADIAnalogIn anglerPot;

extern pros::ADIEncoder leftEncoder;
extern pros::ADIEncoder rightEncoder;

void run();
void debugScreen();
void continuous();
void subsystemProcessingTask(void * ignore);

//MOTORS
extern pros::Motor transLeftDrive;
extern pros::Motor transLeftAngler;
extern pros::Motor transRightDrive;
extern pros::Motor transRightAngler;
extern pros::Motor lift;
extern pros::Motor leftIntake;
extern pros::Motor rightIntake;
extern pros::Motor holder;

#define GYRO_PORT 'F'
#define ANGLER_POT_PORT 'A'
#define LEFT_TOP_ENCODER_PORT 'B'
#define LEFT_BOTTOM_ENCODER_PORT 'C'
#define RIGHT_TOP_ENCODER_PORT 'D'
#define RIGHT_BOTTOM_ENCODER_PORT 'E'
