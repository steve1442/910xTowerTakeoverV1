#include "main.h"

int driveTransmissionLeft;
int driveTransmissionRight;
int anglerTransmission;

bool scoring = false;

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

void tareDrive() {
  leftEncoder.reset();
	rightEncoder.reset();
}

double avgEncoderUnits() {
  return ((leftEncoder.get_value() + rightEncoder.get_value())/2);
}

double driveAngle(){
	return ((leftEncoder.get_value() - rightEncoder.get_value()/ENCODER_WIDTH) * 180)/ PI;
}

//AUTONOMOUS FUNCTIONS
void translate(int units, int speed, bool resetGyro) {
  int reverse = abs(units) / units;
  if(resetGyro)
    gyro.reset();
  tareDrive();
  while(fabs(avgEncoderUnits()) < abs(units)) {
    setDrive(reverse * speed - gyro.get_value(), reverse * speed + gyro.get_value());
    pros::delay(5);
  }
  setDrive(reverse * -10, reverse * -10);
  pros::delay(75);
  setDrive(0, 0);
}

void translateAcc(int units, int maxSpeed, bool resetGyro) {
  int reverse = abs(units) / units;
  int accelUnits = 150;
  int decelUnits = 400;
  if(resetGyro)
    gyro.reset();
  tareDrive();
  int unitsTraveled, unitsLeft, baseVoltage, prevTraveled = 0, rampUp = 0;
  if(abs(units) >= accelUnits + decelUnits) {
    while(avgEncoderUnits() < abs(units)) {
      unitsTraveled = (int) avgEncoderUnits();
      unitsLeft = abs(units) - unitsTraveled;
      if(unitsTraveled < accelUnits)
        baseVoltage = (maxSpeed - 10) * sin(1.5708 * unitsTraveled / accelUnits) + 10;
      else if(unitsLeft < decelUnits)
        baseVoltage = (maxSpeed - 10) * sin(1.5708 * unitsLeft / decelUnits) + 10;
      else
        baseVoltage = maxSpeed;
      if(abs(unitsTraveled - prevTraveled) < 5)
        rampUp += 5;
      else
        rampUp = 0;
      baseVoltage += rampUp;
      pros::lcd::set_text(0, std::to_string(rampUp));
      pros::lcd::set_text(1, std::to_string(avgEncoderUnits()));
      setDrive(baseVoltage * reverse - gyro.get_value() * 0.5, baseVoltage * reverse + gyro.get_value() * 0.5);
      prevTraveled = unitsTraveled;
      pros::delay(5);
    }
    //setDrive(-5 * reverse, -5 * reverse);
    //pros::delay(50);
  }
  else {
    while(avgEncoderUnits() < abs(units)) {
      unitsTraveled = (int) avgEncoderUnits();
      unitsLeft = abs(units) - unitsTraveled;
      if(unitsTraveled < units * accelUnits / (accelUnits + decelUnits))
        baseVoltage = (maxSpeed - 10) * sin(1.5708 * unitsTraveled / accelUnits) + 10;
      else if(unitsLeft < units * decelUnits / (accelUnits + decelUnits))
        baseVoltage = (maxSpeed - 10) * sin(1.5708 * unitsLeft / decelUnits) + 10;
      setDrive(baseVoltage * reverse - gyro.get_value(), baseVoltage * reverse + gyro.get_value());
      pros::delay(5);
    }
    setDrive(-10 * reverse, -10 * reverse);
    pros::delay(50);
  }
  setDrive(0, 0);
}

void translateTime(int millis, int voltage, bool useGyro) {
  setDrive(voltage - (useGyro * gyro.get_value()), voltage + (useGyro * gyro.get_value()));
  pros::delay(millis);
}

void rotate(int degrees10, int maxSpeed) {
  int reverse = abs(degrees10) / degrees10;
  gyro.reset();
  while(fabs(gyro.get_value()) < abs(degrees10) - 100)
    setDrive(maxSpeed * reverse, -maxSpeed * reverse);
  setDrive(-10 * reverse, 10 * reverse);
  pros::delay(100);
  while(fabs(gyro.get_value()) > abs(degrees10) + 5 || fabs(gyro.get_value()) < abs(degrees10) - 5) {
    if(fabs(gyro.get_value()) > abs(degrees10) + 5)
      setDrive(0.5 * -maxSpeed * reverse, 0.5 * maxSpeed * reverse);
    else
      setDrive(0.5 * maxSpeed * reverse, 0.5 * -maxSpeed * reverse);
  }
  setDrive(5 * reverse, -5 * reverse);
  pros::delay(50);
  setDrive(0, 0);
}

void processTransmission(){
	anglerPid();
	smartTransmission();
}
