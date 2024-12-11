#ifndef __GATEBUTTON__
#define __GATEBUTTON__

#include "Button.h"

extern int currentState;

class GateButton: public Button {

public: 
  GateButton(int pin);
  bool isPressed();

private:
  int pin;
};

#endif
