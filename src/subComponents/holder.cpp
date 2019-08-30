#include "main.h"

Pid * holderPid;


void holderFunction(bool isOpen){
    /*if(isOpen){
      holder.tare_position();
    }*/
    holder = (isOpen) ? PID(holderPid, HOLDER_POS, holder.get_position()) : 10;
  }
