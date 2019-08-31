#include "main.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void blue1(){

}

void blue2(){

}

void red1(){

}

void red2(){

}

void skills(){

}

void autonomous() {
  switch(auton){
    case 0:
      blue1();
      break;
    case 1:
      blue2();
      break;
    case 2:
      red1();
      break;
    case 3:
      red2();
      break;
    case 4:
      skills();
      break;
    case 5:

      break;
    default:

      break;

  }
}
