#include "main.h"

pros::Motor transLeftDrive(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor transLeftAngler(2, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor transRightDrive(3, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor transRightAngler(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor lift(5, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor leftIntake(6, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightIntake(7, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor holder(8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::ADIAnalogIn anglerPot(ANGLER_POT_PORT);

std::int32_t controllerDigital(pros::controller_digital_e_t channel) {
  return controller.get_digital(channel);
}

std::int32_t controllerAnalog(pros::controller_analog_e_t channel) {
  return controller.get_analog(channel);
}

void subsystemProcessingTask(void * ignore){
  processTransmission();
  processLift();
  processHolder();
}
