#include "main.h"

void setIntake(int pwm){
  leftIntake = pwm;
  rightIntake = pwm;
}

void IntakeOpcontrol(){
  if(controllerDigital(INTAKE_BUTTON)){
    holderFunction(true);
    setIntake(127);
  }
  else if(controllerDigital(INTAKE_BUTTON)){
    holderFunction(false);
    setIntake(127);
  }
}
