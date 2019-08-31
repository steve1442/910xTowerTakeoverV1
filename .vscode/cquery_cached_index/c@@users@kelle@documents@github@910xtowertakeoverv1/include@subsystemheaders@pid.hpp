#include "main.h"

struct PidProfile
{
    double errorTotal;
    double errorZone;
    double error;
    double kP
          ,kI
          ,kD;
    double errorLast;
};

void changeConstants(PidProfile * pid, double kP, double kI, double kD);

int PID(PidProfile * pid, double setPoint, double Sensor);
