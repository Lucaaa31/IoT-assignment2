#ifndef __LEDTASK__
#define __LEDTASK__

#include "Arduino.h"
#include "Task.h"
#include "Led.h"
#include "Costants.h"
#include "ContainerProp.h"

extern int currentState;

class LedTask: public Task {
private:
    Light* greenLed;
    Light* redLed;
    ContainerProp& container;
public:
    LedTask(int pinGreen, int pinRed, ContainerProp& container);
    void init(int period);
    void tick();
};

#endif