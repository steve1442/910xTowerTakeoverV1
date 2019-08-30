#include "main.h"



void changeConstants(Pid * pid, double kP, double kI, double kD){
  pid->kP = kP;
  pid->kI = kI;
  pid->kD = kD;
}

int PID(Pid * pid, double setPoint, double Sensor){
  // Calculate error
  pid->error = setPoint - Sensor;
  pid->errorTotal += pid->error;

    // Find proportional term
  double pTerm = pid->error * pid->kP;
    // Find integral term
  double iTerm = pid->kI * pid->errorTotal;
    // Find derivative term
  double dTerm = pid->kD * (pid->error - pid->errorLast);
  if (pid->error < pid->errorZone) {
    pid->errorTotal += pid->error;
  } else {
    pid->errorTotal = 0;
  }
    // Compute output
  double power = pTerm + iTerm + dTerm;
 pid->errorLast = pid->error;
    // return val
  return power;
}
