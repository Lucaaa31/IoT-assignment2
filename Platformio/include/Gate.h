#ifndef __GATE__
#define __GATE__

#include "Arduino.h"
#include "Servo.h"
#include "Costants.h"
#include "TickCounter.h"

class Gate {
private:
    Servo servo;
    int pinServo;
    int currentDir;
    void move(int dir);
    int currentState;
    TickCounter timer;
    int detachCounter;
public:
    Gate(int pinServo); 
    int getState();
    void openGate();
    void closeGate();
    void setState(int gateState);
    void emptyGate();
    bool isTimerElapsed();
    void checkServo();
};

#endif
