#ifndef __PROXIMITYTASK__
#define __PROXIMITYTASK__
#include "Task.h"
#include "LCDManager.h"
#include "TickCounter.h"

class ProximityTask : public Task {
private:
    LCDManager lcdManager;
    int pirState; 
    int pinSensor;
    bool val;
    bool detectedStatus;
    volatile bool interruptFlag;
    TickCounter tickToSleep;
    void sleep();
public:
    ProximityTask(int pinSensor, LCDManager& lcdManager);
    void init(int period);
    void tick();
};

#endif