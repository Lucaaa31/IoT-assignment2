#ifndef __GATETASK__
#define __GATETASK__

#include "Task.h"
#include "Button.h"
#include "Costants.h"
#include "Gate.h"
#include "ContainerProp.h"
#include "LCDManager.h"

class GateTask : public Task {
public:
    GateTask(int button1Pin, int button2Pin, ContainerProp& container, LCDManager& lcdManager, Gate& gate);  
    void init(int period);  
    void tick();
    void handleAvailableState();
    void handleOpenState();
    void handleNotAvaiableState();
private:
    ContainerProp& container;  
    LCDManager& lcdManager;
    Gate& gate;
    Button* open;
    Button* close;
    bool allarmOn;
};

#endif
