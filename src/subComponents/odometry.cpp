#include "main.h"

pros::ADIEncoder encoder_left('A', 'B');
pros::ADIEncoder encoder_right('G', 'H');
pros::ADIEncoder encoder_side('C', 'D');

double x = 0.0;
double y = 0.0;
double a = 0.0;
double tickToInchRatio = 3.25/360;
double trackingWheelWidth = 4.0;
double prev_a = a;
double pi = 3.14159;
double left = encoder_left.get_value() * tickToInchRatio;
double right = encoder_right.get_value() * tickToInchRatio;
double side = encoder_side.get_value() * tickToInchRatio;
double delta_left = left;
double delta_right = right;
double delta_side = side;
double delta_x,delta_y;

void updatePos(){

  double theta = (right - left)/trackingWheelWidth;
  if(a == 0.0){
    delta_x += ((left + right)/2.0) * cos(a) + (side * sin(a));
    delta_y += ((left + right)/2.0) * sin(a) + (side * cos(a));
  }
  else{
    double s = (left + right)/2.0;

    double radius = s/theta;
    double side_radius = side/theta;

    double phi = (pi - theta)/2.0;
    // double d = (sin(theta) * radius)/sin(phi);
    double Dx = sin(theta) * radius;
    double Dy = ((sin(theta) * radius)/sin(phi)) * cos(phi);

    // double side_d = (sin(theta) * side_radius)/sin(phi);
    double side_Dx = ((sin(theta) * side_radius)/sin(phi)) * cos(phi);
    double side_Dy = sin(theta) * side_radius;

    double total_x = Dx + side_Dx;
    double total_y = Dy + side_Dy;

    delta_x = x * cos(prev_a) + total_y * sin(prev_a);
    delta_y = y * cos(prev_a) + total_x * sin(prev_a);
  }

  x += delta_x;
  y += delta_y;
  prev_a = a;
}
