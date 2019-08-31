#include "main.h"



void changeConstants(PidProfile * pid, double kP, double kI, double kD){
  pid->kP = kP;
  pid->kI = kI;
  pid->kD = kD;
}

int PID(PidProfile * pid, double setPoint, double sensor){
  // Calculate error
  pid->error = setPoint - sensor;

    // Find proportional term
  double pTerm = pid->error * pid->kP;
    // Find derivative term
  double dTerm = pid->kD * (pid->error - pid->errorLast);
  if (fabs(pid->error) < pid->errorZone) {
    pid->errorTotal += pid->error;
  } else {
    pid->errorTotal = 0;
  }
  // Find integral term
double iTerm = pid->kI * pid->errorTotal;
    // Compute output
  double power = pTerm + iTerm + dTerm;
 pid->errorLast = pid->error;
    // return val
  return power;
}
