#include "main.h"

int liftPidPos[] = {0,500,1000, 1500};
int shifterPos;
PidProfile * liftVariables;

double averageLift(){
  
}

void assignLift(){
  if(controllerDigital(LIFT_UP_BUTTON)){
    shifterPos+=1;
    while(controllerDigital(LIFT_UP_BUTTON)){
      pros::delay(1);
    }
  }
  else if (controllerDigital(LIFT_DOWN_BUTTON)){
    shifterPos-=1;
    while(controllerDigital(LIFT_UP_BUTTON)){
      pros::delay(1);
    }
  }
  else{
    shifterPos=abs(shifterPos % 5);
  }
}

void processLift(){
  leftLift = PID(liftVariables, liftPidPos[shifterPos], leftLift.get_position());
  rightLift = PID(liftVariables, liftPidPos[shifterPos], leftLift.get_position());
}
