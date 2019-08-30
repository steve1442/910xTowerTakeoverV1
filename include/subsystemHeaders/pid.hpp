#include "main.h"

struct Pid
{
    double errorTotal;
    double errorZone;
    double error;
    double kP
          ,kI
          ,kD;
    double errorLast;
};

void changeConstants(Pid * pid, double kP, double kI, double kD);

int PID(Pid * pid, double setPoint, double Sensor);
