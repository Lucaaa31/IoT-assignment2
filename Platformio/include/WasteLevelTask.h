#ifndef __WASTELEVEL__
#define __WASTELEVEL__

#include "Task.h"
#include "Costants.h"
#include "ContainerProp.h"
#include "LCDManager.h"

extern int currentState;

class WasteLevelTask: public Task {
public:
    WasteLevelTask(int pinTrig, int pinEcho, ContainerProp& container, LCDManager& manager);  
    void init(int period);  
    void tick();
private:
    int var;
    int readLevel();
    int pinTrig;
    int pinEcho;
    ContainerProp& container;
    LCDManager& lcdManager;
};

#endif
