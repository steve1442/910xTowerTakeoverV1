#include "main.h"

enum holderStates {
    CLOSED = 0,
    CLOSING = 1,
    OPENING = 2,
    OPEN = 3
};

int holderStates = OPEN;
int previousHolderPosition;
const int holderError = 5;

void setHolder(int pwm){
  holder = pwm;
}

void setHolderMode(int mode){
  holderStates = mode;
}

void assignHolder(){
  if(controllerDigital(HOLDER_TOGGLE_BUTTON)){
    holderStates = (holderStates == CLOSED || holderStates == CLOSING) ? CLOSING : OPENING;
    while(controllerDigital(HOLDER_TOGGLE_BUTTON)){
      pros::delay(1);
    }
  }
}

void processHolder(){
  if(holderStates == CLOSED || holderStates == CLOSING){
    if(holder.get_position() < previousHolderPosition + holderError || holder.get_position() > previousHolderPosition - holderError){
      holderStates = CLOSED;
    }
    else{
      holderStates = CLOSING;
    }
  }
  else if(holderStates == OPEN || holderStates == OPENING){
    if(holder.get_position() < previousHolderPosition + holderError || holder.get_position() > previousHolderPosition - holderError){
      holderStates = OPEN;
    }
    else{
      holderStates = OPENING;
    }
  }

  switch(holderStates){
    case CLOSED:
      setHolder(10);
      break;
    case CLOSING:
      setHolder(40);
      break;
    case OPENING:
      setHolder(-40);
      break;
    case OPEN:
      setHolder(-10);
      break;
    default:
      setHolder(0);
      break;
  }
}
