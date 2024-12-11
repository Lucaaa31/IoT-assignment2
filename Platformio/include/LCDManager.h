#ifndef __LCDMANAGER__
#define __LCDMANAGER__

#include "Arduino.h"
#include "Costants.h"
#include "LiquidCrystal_I2C.h"

class LCDManager {
private:
    LiquidCrystal_I2C* lcd; 
    char currentMessage[33];
public:
    LCDManager();
    void setMessage(const char* msg);
    String getMessage();
    void sleep();
    void wakeUp();
};

#endif