#include "TickCounter.h"

TickCounter::TickCounter(){
    tmpTime = 10;
}


void TickCounter::startTimer(int tick){
    tmpTime = tick;
}

bool TickCounter::isTimeElapsed(){
    return tmpTime <= 0;
}

void TickCounter::dec(){
    tmpTime--;
}

void TickCounter::printRemaining(){
    //Serial.print("REMAINING");
    //Serial.println(tmpTime);
}

