#include "main.h"

void setIntake(int pwm){
  leftIntake = pwm;
  rightIntake = pwm;
}

void assignIntake(){
  if(INTAKE_BUTTON)
    setIntake(127);
  else if(OUTTAKE_BUTTON)
    setIntake(-127);
  else{
    setIntake(0);
    leftIntake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightIntake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }
}
