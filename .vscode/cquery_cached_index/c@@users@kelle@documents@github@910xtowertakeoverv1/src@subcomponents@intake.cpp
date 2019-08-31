#include "main.h"

void setIntake(int pwm){
  leftIntake = pwm;
  rightIntake = pwm;
}

void assignIntake(){
  if(controllerDigital(INTAKE_BUTTON)){
    setHolderMode(3);
    setIntake(127);
  }
  else if(controllerDigital(OUTTAKE_BUTTON)){
    setHolderMode(3);
    setIntake(-127);
  }
  else{
    setHolderMode(2);
  }
}
