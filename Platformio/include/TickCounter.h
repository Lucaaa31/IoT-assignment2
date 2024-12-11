#ifndef __TICKCOUNTER__
#define __TICKCOUNTER__

#include "Arduino.h"


class TickCounter {
public:
    TickCounter();
    void startTimer(int time);
    void printRemaining();
    bool isTimeElapsed();
    void dec();
private:
    int tmpTime;
    int tick;
};

#endif
