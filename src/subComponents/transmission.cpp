#include "main.h"

int driveTransmissionLeft;
int driveTransmissionRight;
int anglerTransmission;

bool scoring;

PidProfile * anglerPidStructP;

int anglerPidPos;

void smartTransmission(){
	int leftM1 = driveTransmissionLeft;
	int leftM2 = anglerTransmission + leftM1;
	int rightM1 = driveTransmissionRight;
	int rightM2 = anglerTransmission + rightM1;

	if (abs(leftM2) > 127 || abs(rightM2) > 127){
		double scaler = (fabs(127.0/leftM2) < fabs(127.0/rightM2)) ? fabs(127.0/leftM2) : fabs(127.0/rightM2);
		transLeftDrive = leftM1 * scaler;
		transLeftAngler = leftM2 * scaler;
		transRightDrive = rightM1 * scaler;
		transRightAngler = rightM2 * scaler;
	}
	else{
		transLeftDrive = leftM1;
		transLeftAngler = leftM2;
		transRightDrive = rightM1;
		transRightAngler = rightM2;
	}
}

void setDrive(int left, int right){
  driveTransmissionLeft = (abs(left) > 127) ? 127 * (left/abs(left)) : left;
  driveTransmissionRight = (abs(right) > 127) ? 127 * (right/abs(right)) : right;
}

void setAngler(int pwm){
  anglerTransmission = (abs(pwm) > 127) ? 127 * (pwm/abs(pwm)) : pwm;
}

void anglerPid(){
  setAngler(PID(anglerPidStructP, anglerPidPos, anglerPot.get_value()));
}

void assignAngler(){
  if(controllerDigital(ANGLER_TOGGLE_BUTTON)){
    scoring = !scoring;
    while(controllerDigital(ANGLER_TOGGLE_BUTTON)){
      pros::delay(1);
    }
  }
  anglerPidPos = (scoring) ? ANGLER_SCORING_POS : ANGLER_INTAKING_POS;
}

void assignDrive(){
	setDrive((abs(controllerAnalog(LEFT_JOYSTICK)) < 10) ? 0 : controllerAnalog(LEFT_JOYSTICK)
					,(abs(controllerAnalog(RIGHT_JOYSTICK)) < 10) ? 0 : controllerAnalog(RIGHT_JOYSTICK));
}

void processTransmission(){
	anglerPid();
}
